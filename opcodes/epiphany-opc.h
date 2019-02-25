/* DO NOT EDIT!  -*- buffer-read-only: t -*- vi:set ro:  */
/* Instruction opcode header for epiphany.

THIS FILE IS MACHINE GENERATED WITH CGEN.

Copyright (C) 1996-2019 Free Software Foundation, Inc.

This file is part of the GNU Binutils and/or GDB, the GNU debugger.

   This file is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.

*/

#ifndef EPIPHANY_OPC_H
#define EPIPHANY_OPC_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- opc.h */

/* enumerate relaxation types for gas. */
typedef enum epiphany_relax_types
{
  EPIPHANY_RELAX_NONE=0,
  EPIPHANY_RELAX_NEED_RELAXING,

  EPIPHANY_RELAX_BRANCH_SHORT,	/* Fits into +127..-128 */
  EPIPHANY_RELAX_BRANCH_LONG,	/* b/bl/b<cond> +-2*16 */

  EPIPHANY_RELAX_ARITH_SIMM3,	/* add/sub -7..3 */
  EPIPHANY_RELAX_ARITH_SIMM11,	/* add/sub -2**11-1 .. 2**10-1 */

  EPIPHANY_RELAX_MOV_IMM8,		/* mov r,imm8 */
  EPIPHANY_RELAX_MOV_IMM16,	/* mov r,imm16 */

  EPIPHANY_RELAX_LDST_IMM3,	/* (ldr|str)* r,[r,disp3] */
  EPIPHANY_RELAX_LDST_IMM11	/* (ldr|str)* r,[r,disp11] */

} EPIPHANY_RELAX_TYPES;

/* Override disassembly hashing... */

/* Can only depend on instruction having 4 decode bits which gets us to the
   major groups of 16/32 instructions. */
#undef CGEN_DIS_HASH_SIZE
#if 1

/* hash code on the 4 LSBs */
#define CGEN_DIS_HASH_SIZE 16

#define CGEN_DIS_HASH(buf, value) ((*buf) & 0xf)
#else
#define CGEN_DIS_HASH_SIZE 1
#define CGEN_DIS_HASH(buf, value) 0
#endif

extern const char * parse_shortregs (CGEN_CPU_DESC cd,
				     const char ** strp,
				     CGEN_KEYWORD * keywords,
				     long * valuep);

extern const char * parse_dword_shortregs (CGEN_CPU_DESC cd,
					   const char ** strp,
					   CGEN_KEYWORD * keywords,
					   long * valuep);

extern const char * parse_branch_addr (CGEN_CPU_DESC cd,
				       const char ** strp,
				       int opindex,
				       int opinfo,
				       enum cgen_parse_operand_result * resultp,
				       bfd_vma *valuep);

extern const char * parse_dword_regs (CGEN_CPU_DESC cd,
				      const char ** strp,
				      CGEN_KEYWORD * keywords,
				      long * valuep);

/* Allows reason codes to be output when assembler errors occur.  */
#define CGEN_VERBOSE_ASSEMBLER_ERRORS


/* -- opc.c */
/* Enum declaration for epiphany instruction types.  */
typedef enum cgen_insn_type {
  EPIPHANY_INSN_INVALID, EPIPHANY_INSN_BEQ16, EPIPHANY_INSN_BEQ, EPIPHANY_INSN_BNE16
 , EPIPHANY_INSN_BNE, EPIPHANY_INSN_BGTU16, EPIPHANY_INSN_BGTU, EPIPHANY_INSN_BGTEU16
 , EPIPHANY_INSN_BGTEU, EPIPHANY_INSN_BLTEU16, EPIPHANY_INSN_BLTEU, EPIPHANY_INSN_BLTU16
 , EPIPHANY_INSN_BLTU, EPIPHANY_INSN_BGT16, EPIPHANY_INSN_BGT, EPIPHANY_INSN_BGTE16
 , EPIPHANY_INSN_BGTE, EPIPHANY_INSN_BLT16, EPIPHANY_INSN_BLT, EPIPHANY_INSN_BLTE16
 , EPIPHANY_INSN_BLTE, EPIPHANY_INSN_BBEQ16, EPIPHANY_INSN_BBEQ, EPIPHANY_INSN_BBNE16
 , EPIPHANY_INSN_BBNE, EPIPHANY_INSN_BBLT16, EPIPHANY_INSN_BBLT, EPIPHANY_INSN_BBLTE16
 , EPIPHANY_INSN_BBLTE, EPIPHANY_INSN_B16, EPIPHANY_INSN_B, EPIPHANY_INSN_BL16
 , EPIPHANY_INSN_BL, EPIPHANY_INSN_JR16, EPIPHANY_INSN_RTS, EPIPHANY_INSN_JR
 , EPIPHANY_INSN_JALR16, EPIPHANY_INSN_JALR, EPIPHANY_INSN_LDRBX16_S, EPIPHANY_INSN_LDRBX_L
 , EPIPHANY_INSN_LDRBP16_S, EPIPHANY_INSN_LDRBP_L, EPIPHANY_INSN_LDRBD16_S, EPIPHANY_INSN_LDRBD_L
 , EPIPHANY_INSN_LDRBDPM_L, EPIPHANY_INSN_LDRHX16_S, EPIPHANY_INSN_LDRHX_L, EPIPHANY_INSN_LDRHP16_S
 , EPIPHANY_INSN_LDRHP_L, EPIPHANY_INSN_LDRHD16_S, EPIPHANY_INSN_LDRHD_L, EPIPHANY_INSN_LDRHDPM_L
 , EPIPHANY_INSN_LDRX16_S, EPIPHANY_INSN_LDRX_L, EPIPHANY_INSN_LDRP16_S, EPIPHANY_INSN_LDRP_L
 , EPIPHANY_INSN_LDRD16_S, EPIPHANY_INSN_LDRD_L, EPIPHANY_INSN_LDRDPM_L, EPIPHANY_INSN_LDRDX16_S
 , EPIPHANY_INSN_LDRDX_L, EPIPHANY_INSN_LDRDP16_S, EPIPHANY_INSN_LDRDP_L, EPIPHANY_INSN_LDRDD16_S
 , EPIPHANY_INSN_LDRDD_L, EPIPHANY_INSN_LDRDDPM_L, EPIPHANY_INSN_TESTSETT, EPIPHANY_INSN_STRBX16
 , EPIPHANY_INSN_STRBX, EPIPHANY_INSN_STRBP16, EPIPHANY_INSN_STRBP, EPIPHANY_INSN_STRBD16
 , EPIPHANY_INSN_STRBD, EPIPHANY_INSN_STRBDPM, EPIPHANY_INSN_STRHX16, EPIPHANY_INSN_STRHX
 , EPIPHANY_INSN_STRHP16, EPIPHANY_INSN_STRHP, EPIPHANY_INSN_STRHD16, EPIPHANY_INSN_STRHD
 , EPIPHANY_INSN_STRHDPM, EPIPHANY_INSN_STRX16, EPIPHANY_INSN_STRX, EPIPHANY_INSN_STRP16
 , EPIPHANY_INSN_STRP, EPIPHANY_INSN_STRD16, EPIPHANY_INSN_STRD, EPIPHANY_INSN_STRDPM
 , EPIPHANY_INSN_STRDX16, EPIPHANY_INSN_STRDX, EPIPHANY_INSN_STRDP16, EPIPHANY_INSN_STRDP
 , EPIPHANY_INSN_STRDD16, EPIPHANY_INSN_STRDD, EPIPHANY_INSN_STRDDPM, EPIPHANY_INSN_CMOV16EQ
 , EPIPHANY_INSN_CMOVEQ, EPIPHANY_INSN_CMOV16NE, EPIPHANY_INSN_CMOVNE, EPIPHANY_INSN_CMOV16GTU
 , EPIPHANY_INSN_CMOVGTU, EPIPHANY_INSN_CMOV16GTEU, EPIPHANY_INSN_CMOVGTEU, EPIPHANY_INSN_CMOV16LTEU
 , EPIPHANY_INSN_CMOVLTEU, EPIPHANY_INSN_CMOV16LTU, EPIPHANY_INSN_CMOVLTU, EPIPHANY_INSN_CMOV16GT
 , EPIPHANY_INSN_CMOVGT, EPIPHANY_INSN_CMOV16GTE, EPIPHANY_INSN_CMOVGTE, EPIPHANY_INSN_CMOV16LT
 , EPIPHANY_INSN_CMOVLT, EPIPHANY_INSN_CMOV16LTE, EPIPHANY_INSN_CMOVLTE, EPIPHANY_INSN_CMOV16B
 , EPIPHANY_INSN_CMOVB, EPIPHANY_INSN_CMOV16BEQ, EPIPHANY_INSN_CMOVBEQ, EPIPHANY_INSN_CMOV16BNE
 , EPIPHANY_INSN_CMOVBNE, EPIPHANY_INSN_CMOV16BLT, EPIPHANY_INSN_CMOVBLT, EPIPHANY_INSN_CMOV16BLTE
 , EPIPHANY_INSN_CMOVBLTE, EPIPHANY_INSN_MOVTS16, EPIPHANY_INSN_MOVTS6, EPIPHANY_INSN_MOVTSDMA
 , EPIPHANY_INSN_MOVTSMEM, EPIPHANY_INSN_MOVTSMESH, EPIPHANY_INSN_MODE, EPIPHANY_INSN_MOVFS16
 , EPIPHANY_INSN_MOVFS6, EPIPHANY_INSN_MOVFSDMA, EPIPHANY_INSN_MOVFSMEM, EPIPHANY_INSN_MOVFSMESH
 , EPIPHANY_INSN_NOP, EPIPHANY_INSN_SNOP, EPIPHANY_INSN_UNIMPL, EPIPHANY_INSN_IDLE
 , EPIPHANY_INSN_BKPT, EPIPHANY_INSN_MBKPT, EPIPHANY_INSN_RTI, EPIPHANY_INSN_WAND
 , EPIPHANY_INSN_SYNC, EPIPHANY_INSN_GIEN, EPIPHANY_INSN_GIDIS, EPIPHANY_INSN_SWI_NUM
 , EPIPHANY_INSN_SWI, EPIPHANY_INSN_TRAP16, EPIPHANY_INSN_ADD16, EPIPHANY_INSN_ADD
 , EPIPHANY_INSN_SUB16, EPIPHANY_INSN_SUB, EPIPHANY_INSN_AND16, EPIPHANY_INSN_AND
 , EPIPHANY_INSN_ORR16, EPIPHANY_INSN_ORR, EPIPHANY_INSN_EOR16, EPIPHANY_INSN_EOR
 , EPIPHANY_INSN_ADDI16, EPIPHANY_INSN_ADDI, EPIPHANY_INSN_SUBI16, EPIPHANY_INSN_SUBI
 , EPIPHANY_INSN_ASR16, EPIPHANY_INSN_ASR, EPIPHANY_INSN_LSR16, EPIPHANY_INSN_LSR
 , EPIPHANY_INSN_LSL16, EPIPHANY_INSN_LSL, EPIPHANY_INSN_LSRI16, EPIPHANY_INSN_LSRI32
 , EPIPHANY_INSN_LSLI16, EPIPHANY_INSN_LSLI32, EPIPHANY_INSN_ASRI16, EPIPHANY_INSN_ASRI32
 , EPIPHANY_INSN_ADD64, EPIPHANY_INSN_SUB64, EPIPHANY_INSN_AND64, EPIPHANY_INSN_ORR64
 , EPIPHANY_INSN_EOR64, EPIPHANY_INSN_ASR64, EPIPHANY_INSN_LSR64, EPIPHANY_INSN_LSL64
 , EPIPHANY_INSN_BITR16, EPIPHANY_INSN_BITR, EPIPHANY_INSN_MOV8, EPIPHANY_INSN_MOV16
 , EPIPHANY_INSN_MOVT, EPIPHANY_INSN_F_ADDF16, EPIPHANY_INSN_F_ADDF32, EPIPHANY_INSN_F_SUBF16
 , EPIPHANY_INSN_F_SUBF32, EPIPHANY_INSN_F_MULF16, EPIPHANY_INSN_F_MULF32, EPIPHANY_INSN_F_MADDF16
 , EPIPHANY_INSN_F_MADDF32, EPIPHANY_INSN_F_MSUBF16, EPIPHANY_INSN_F_MSUBF32, EPIPHANY_INSN_F_ABSF16
 , EPIPHANY_INSN_F_ABSF32, EPIPHANY_INSN_F_LOATF16, EPIPHANY_INSN_F_LOATF32, EPIPHANY_INSN_F_IXF16
 , EPIPHANY_INSN_F_IXF32, EPIPHANY_INSN_FMAX
} CGEN_INSN_TYPE;

/* Index of `invalid' insn place holder.  */
#define CGEN_INSN_INVALID EPIPHANY_INSN_INVALID

/* Total number of insns in table.  */
#define MAX_INSNS ((int) EPIPHANY_INSN_FMAX + 1)

/* This struct records data prior to insertion or after extraction.  */
struct cgen_fields
{
  int length;
  long f_nil;
  long f_anyof;
  long f_opc;
  long f_opc_4_1;
  long f_opc_6_3;
  long f_opc_8_5;
  long f_opc_19_4;
  long f_opc_9_6;
  long f_opc_21_6;
  long f_condcode;
  long f_secondary_ccs;
  long f_shift;
  long f_wordsize;
  long f_store;
  long f_opc_8_1;
  long f_opc_31_32;
  long f_simm8;
  long f_simm24;
  long f_sdisp3;
  long f_disp3;
  long f_disp8;
  long f_imm8;
  long f_imm_27_8;
  long f_addsubx;
  long f_subd;
  long f_pm;
  long f_rm;
  long f_rn;
  long f_rd;
  long f_rm_x;
  long f_rn_x;
  long f_rd_x;
  long f_dc_9_1;
  long f_sn;
  long f_sd;
  long f_sn_x;
  long f_sd_x;
  long f_dc_7_4;
  long f_trap_swi_9_1;
  long f_gien_gidis_9_1;
  long f_mode4_l;
  long f_mode4_h;
  long f_ctrlmode5;
  long f_atomic;
  long f_dc_15_3;
  long f_dc_15_7;
  long f_dc_15_6;
  long f_trap_num;
  long f_dc_20_1;
  long f_dc_21_1;
  long f_dc_21_2;
  long f_dc_22_3;
  long f_dc_22_2;
  long f_dc_22_1;
  long f_dc_25_6;
  long f_dc_25_4;
  long f_dc_25_2;
  long f_dc_25_1;
  long f_dc_28_1;
  long f_dc_31_3;
  long f_dc_31_2;
  long f_disp11;
  long f_sdisp11;
  long f_imm16;
  long f_mode4;
  long f_rd6;
  long f_rn6;
  long f_rm6;
  long f_sd6;
  long f_sn6;
};

#define CGEN_INIT_PARSE(od) \
{\
}
#define CGEN_INIT_INSERT(od) \
{\
}
#define CGEN_INIT_EXTRACT(od) \
{\
}
#define CGEN_INIT_PRINT(od) \
{\
}


   #ifdef __cplusplus
   }
   #endif

#endif /* EPIPHANY_OPC_H */
