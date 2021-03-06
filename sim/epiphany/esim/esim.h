/* Epiphany eMesh functional simulator
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef __emesh_h__
#define __emesh_h__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/** @todo We use standard errnos now but we need more specific, e.g. EALIGN */

#define ES_OK 0

/* Only support homogeneous configurations for now */
/*! ESIM cluster configuration */
typedef struct es_cluster_cfg_ {
    unsigned row_base;                /*!< Row of upper leftmost core      */
    unsigned col_base;                /*!< Col of upper leftmost core      */
    unsigned rows;                    /*!< Number of rows                  */
    unsigned cols;                    /*!< Number of cols                  */
    size_t   core_mem_region;         /*!< Core memory region size         */
    size_t   core_phys_mem;           /*!< Size of core SRAM               */
    unsigned ext_ram_node;            /*!< Let this be rank '0' for now    */
    uint64_t ext_ram_base;            /*!< core_mem_region must be divisor */
    uint64_t ext_ram_size;            /*!< Size of external memory         */

    /*! @privatesection */
    /* Keep your grubby little mitts off of these plz :) */
    /* Filled in by es_fill_in_internal_cfg_values() */
    unsigned cores;                   /*!< Total number of cores           */
    unsigned nodes;                   /*!< Number of simulation nodes.
                                        Computed by es_net_init if networking
                                        is enabled */
    unsigned cores_per_node;          /*!< Cores per node
                                        Computed by es_net_init if networking
                                        is enabled */
    unsigned rows_per_node;           /*!< Rows per node                   */
    unsigned cols_per_node;           /*!< Columns per node                */

    unsigned ext_ram_rank;            /*!< Rank of process w. ext ram      */
} es_cluster_cfg;

typedef struct es_state_ es_state;

/* API functions */

/* For core simulator processes */
int es_init(es_state **esim, es_cluster_cfg cluster, unsigned coreid,
	    const char *session_name);
void es_fini(es_state *esim);

/* Get access to eMesh simulator address space */
int es_client_connect(es_state **esim, const char *session_name);
void es_client_disconnect(es_state *esim, bool stop);
/* Get raw pointer to external RAM, which is needed for e-hal's SHM interface.
 * WARNING: This function might be removed from the client API in the future.
 */
volatile void *es_client_get_raw_pointer (es_state *esim, uint64_t addr,
					  uint64_t size);

int es_mem_store (es_state *esim, uint64_t addr, uint64_t size,
		  const void *src);
int es_mem_load (es_state *esim, uint64_t addr, uint64_t size, void *dst);

int es_mem_atomic_store (es_state *esim, int ctrlmode, uint64_t addr,
			 uint64_t size, const void *src);
int es_mem_atomic_load (es_state *esim, int ctrlmode, uint64_t addr,
		        uint64_t size, void *dst);

int es_wand (es_state *esim);

int es_send_interrupt (es_state *esim, unsigned coreid, unsigned irq);

void es_wait_run(es_state *esim);
void es_wait_exit(es_state *esim);

int es_valid_coreid(const es_state *esim, unsigned coreid);
int es_initialized(const es_state* esim);

unsigned es_get_coreid(const es_state *esim);

void *es_set_cpu_state(es_state *esim, void* cpu, size_t size);
size_t es_get_core_mem_region_size(const es_state *esim);
size_t es_get_core_phys_mem_size(const es_state *esim);
/* Get copy of cluster configuration */
void es_get_cluster_cfg(const es_state *esim, es_cluster_cfg *cfg);

void es_dump_config(const es_state *esim);


#endif /* __emesh_h__ */
