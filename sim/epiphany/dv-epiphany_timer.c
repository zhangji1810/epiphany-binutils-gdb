/*  This file is part of the program GDB, the GNU debugger.

    Copyright (C) 2014 Adapteva
    Contributed by Ola Jeppsson

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    */

#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

#include "sim-main.h"
#include "hw-main.h"
#include "hw-device.h"
#include "sim-types.h"
#include "epiphany-sim.h"
#include "epiphany-desc.h"

#include "cpu.h"

#if WITH_EMESH_SIM
#include "esim/esim.h"
#else
#error "I need WITH_EMESH_SIM. Enable with --enable-emesh-sim"
#endif

/* DEVICE


   epiphany_timer - epiphany timer implementation


   DESCRIPTION


   Implements ctimer0 and ctimer1.


   PROPERTIES

   none

   PORTS

   none
   @todo investigate which ports are needed

   */

enum epiphany_timer_event_t {
  EVENT_OFF,
  EVENT_CLK,
  EVENT_IDLE,
  EVENT_CHAINED, /* For chaining ctimer0 and ctimer1 */
  EVENT_IALU_VALID,
  EVENT_FPU_VALID,
  EVENT_DUAL_ISSUE,
  EVENT_E1_STALLS,
  EVENT_RA_STALLS,
  EVENT_RSVD2,
  EVENT_LOC_FETCH_STALL,
  EVENT_LOC_LOAD_STALL,
  EVENT_EXT_FETCH_STALL,
  EVENT_EXT_LOAD_STALL,
  EVENT_MESH_TRAFFIC0,
  EVENT_MESH_TRAFFIC1,
};

union epiphany_config {
  uint32_t reg;
  struct {
    unsigned rmode:1;
    unsigned ien:1;
    unsigned oen:1;
    unsigned uen:1;
    unsigned ctimer0cfg:4;
    unsigned ctimer1cfg:4;
    unsigned ctrlmode:4;
    unsigned _rsvd1:1;
    unsigned arithmode:3;
    unsigned _rsvd2:2;
    unsigned lpmode:1;
    unsigned _rsvd3:3;
    unsigned timerwrap:1;
    unsigned _rsvd4:5;
  } __attribute__((packed));
} __attribute__((packed));

union epiphany_timer_regs {
  uint64_t chained;
  ulong    chainedul; /* silly work around for cast inside macro warning */
  struct {
    uint32_t timer0;
    uint32_t timer1;
  } __attribute__((packed));
} __attribute__((packed));

struct epiphany_timer {
  struct hw_event *handler;

  /* cache config values */
  unsigned timer0_cfg;
  unsigned timer1_cfg;
  bool timerwrap;
};

static bool
chained_p (struct epiphany_timer *timer)
{
  return timer->timer1_cfg == EVENT_CHAINED;
}

static bool
might_tick_p (struct epiphany_timer *timer)
{
  switch (timer->timer0_cfg)
  {
  case EVENT_CLK:
  case EVENT_IDLE:
    return true;
  }
  switch (timer->timer1_cfg)
  {
  case EVENT_CLK:
  case EVENT_IDLE:
    return true;
  }
  return false;
}

static void epiphany_timer_hw_event_callback (struct hw *me, void *data);

static void
epiphany_timer_reschedule (struct hw *me, unsigned delay)
{
  struct epiphany_timer *timer = (struct epiphany_timer *) hw_data (me);
  if (timer->handler)
    {
      hw_event_queue_deschedule (me, timer->handler);
      timer->handler = NULL;
    }
  if (!delay)
    return;

  timer->handler = hw_event_queue_schedule (me, delay,
					    epiphany_timer_hw_event_callback,
					    timer);
}

static union epiphany_timer_regs *get_regs (struct hw *me);

static void
emit_interrupt (struct hw *me, unsigned timer)
{
  SIM_CPU *current_cpu = STATE_CPU (hw_system (me), 0);
  uint32_t ilatst_val;

  assert (current_cpu);
  assert (timer == 0 || timer == 1);

  HW_TRACE ((me, "raising interrupt for ctimer%u", timer));

  epiphanybf_h_all_registers_set (current_cpu, H_REG_SCR_ILATST,
				  1 << (H_INTERRUPT_TIMER0 + timer));
}

static bool
should_tick_p (unsigned cfg, SIM_CPU *current_cpu)
{
  switch (cfg)
    {
    case EVENT_IDLE:
      return !epiphany_cpu_is_active (current_cpu);
    case EVENT_CLK:
      /* ???: What about low powered state? */
      return true;
    default:
      return false;
    }
  return false;
}

static void
epiphany_timer_hw_event_callback (struct hw *me, void *data)
{
  struct epiphany_timer *timer = (struct epiphany_timer *) data;
  union epiphany_timer_regs *regs = get_regs (me);
  SIM_CPU *current_cpu = STATE_CPU (hw_system (me), 0);

  timer->handler = NULL;

  if (should_tick_p (timer->timer0_cfg, current_cpu))
    {
      if (chained_p (timer))
	{
	  regs->chained -= (regs->chained || timer->timerwrap) ? 1 : 0;
	  HW_TRACE ((me, "ctimer01=%#llx (chained)", regs->chainedul));
	  if (regs->chained == 0)
	    emit_interrupt(me, 0);
	}
      else
	{
	  regs->timer0 -= (regs->timer0 || timer->timerwrap) ? 1 : 0;
	  HW_TRACE ((me, "ctimer0=%#x", regs->timer0));
	  if (regs->timer0 == 0)
	    emit_interrupt (me, 0);
	}
    }

  if (should_tick_p (timer->timer1_cfg, current_cpu))
    {
      regs->timer1 -= (regs->timer1 || timer->timerwrap) ? 1 : 0;
      HW_TRACE ((me, "ctimer1=%#x", regs->timer1));
      if (regs->timer1 == 0)
	emit_interrupt(me, 1);
    }

  if (might_tick_p (timer))
    epiphany_timer_reschedule (me, 1);

  return;
}


/* Finish off the partially created hw device.  Attach our local
   callbacks.  Wire up our port names etc */

static hw_port_event_method epiphany_timer_port_event;

static const struct hw_port_descriptor epiphany_timer_ports[] = {
  { "di", 0, 0, output_port, }, /* Timer Interrupt */
  { NULL, 0, 0, 0, },
};

static void
epiphany_timer_finish (struct hw *me)
{
  struct hw *parent = hw_parent (me);
  struct epiphany_timer *timer;

  HW_TRACE ((me, "epiphany_timer_finish"));

  timer = HW_ZALLOC (me, struct epiphany_timer);

  set_hw_data (me, timer);
  set_hw_ports (me, epiphany_timer_ports);
  set_hw_port_event (me, epiphany_timer_port_event);
}

static void
epiphany_timer_port_event (struct hw *me,
			   int my_port,
			   struct hw *source,
			   int source_port,
			   int level)
{
  struct epiphany_timer *timer = hw_data (me);
  hw_abort (me, "epiphany_timer_port_event: not implemented");
}

const struct hw_descriptor dv_epiphany_timer_descriptor[] = {
  { "epiphany_timer", epiphany_timer_finish, },
  { NULL },
};

static union epiphany_timer_regs *
get_regs (struct hw *me)
{
  uint32_t *ptr;
  struct epiphany_timer *timer = hw_data (me);
  SIM_CPU *current_cpu = STATE_CPU (hw_system (me), 0);

  assert (current_cpu);
  assert (timer);

  ptr = &(CPU (h_all_registers[H_REG_SCR_CTIMER0]));

  return (union epiphany_timer_regs *) ptr;
}

void
epiphany_timer_set_cfg (struct hw *me, uint32_t val)
{
  struct epiphany_timer *timer = hw_data (me);
  union epiphany_config config = { .reg = val };

  timer->timer0_cfg = config.ctimer0cfg;
  timer->timer1_cfg = config.ctimer1cfg;
  timer->timerwrap  = config.timerwrap;

  HW_TRACE ((me,
	     "new configuration: timer0_cfg=%#x timer1_cfg=%#x timerwrap=%u",
	     timer->timer0_cfg, timer->timer1_cfg, timer->timerwrap));

  epiphany_timer_reschedule (me, might_tick_p (timer) ? 1 : 0);
}

bool epiphany_timer_active_p (struct hw *me)
{
  struct epiphany_timer *timer = hw_data (me);
  /* union epiphany_timer_regs *regs = get_regs (me); */

  /* ???: Is this enough, or do we also need to check the regs? */
  return timer->handler != NULL;
}
