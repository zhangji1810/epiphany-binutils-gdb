#as:
#objdump: -dr
#name: i860 ldst03 (ld.b)

.*: +file format .*

Disassembly of section \.text:

00000000 <\.text>:
   0:	00 00 00 04 	ld.b	0\(%r0\),%r0
   4:	01 00 3f 04 	ld.b	1\(%r1\),%r31
   8:	02 00 5e 04 	ld.b	2\(%sp\),%r30
   c:	01 02 7d 04 	ld.b	513\(%fp\),%r29
  10:	04 04 9c 04 	ld.b	1028\(%r4\),%r28
  14:	fa 0f bb 04 	ld.b	4090\(%r5\),%r27
  18:	fe 1f da 04 	ld.b	8190\(%r6\),%r26
  1c:	01 40 f9 04 	ld.b	16385\(%r7\),%r25
  20:	07 7d f9 04 	ld.b	32007\(%r7\),%r25
  24:	ff 7f f9 04 	ld.b	32767\(%r7\),%r25
  28:	00 80 f9 04 	ld.b	-32768\(%r7\),%r25
  2c:	01 80 f9 04 	ld.b	-32767\(%r7\),%r25
  30:	01 c0 18 05 	ld.b	-16383\(%r8\),%r24
  34:	5b e0 37 05 	ld.b	-8101\(%r9\),%r23
  38:	05 f0 56 05 	ld.b	-4091\(%r10\),%r22
  3c:	01 fc 75 05 	ld.b	-1023\(%r11\),%r21
  40:	03 fe 94 05 	ld.b	-509\(%r12\),%r20
  44:	e9 ff b3 05 	ld.b	-23\(%r13\),%r19
  48:	ff ff d2 05 	ld.b	-1\(%r14\),%r18
  4c:	00 28 00 00 	ld.b	%r5\(%r0\),%r0
  50:	00 30 3f 00 	ld.b	%r6\(%r1\),%r31
  54:	00 38 5e 00 	ld.b	%r7\(%sp\),%r30
  58:	00 40 7d 00 	ld.b	%r8\(%fp\),%r29
  5c:	00 48 9c 00 	ld.b	%r9\(%r4\),%r28
  60:	00 00 bb 00 	ld.b	%r0\(%r5\),%r27
  64:	00 08 da 00 	ld.b	%r1\(%r6\),%r26
  68:	00 60 f9 00 	ld.b	%r12\(%r7\),%r25
  6c:	00 68 18 01 	ld.b	%r13\(%r8\),%r24
  70:	00 70 37 01 	ld.b	%r14\(%r9\),%r23
  74:	00 78 56 01 	ld.b	%r15\(%r10\),%r22
  78:	00 80 75 01 	ld.b	%r16\(%r11\),%r21
  7c:	00 88 94 01 	ld.b	%r17\(%r12\),%r20
  80:	00 e0 b3 01 	ld.b	%r28\(%r13\),%r19
  84:	00 f8 d2 01 	ld.b	%r31\(%r14\),%r18