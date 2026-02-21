#ifndef EE_REGS_H
#define EE_REGS_H

#define T0_COUNT ((volatile u32 *)(0x10000000))

#define D0_CHCR         ((volatile u_int *)(0x10008000))
#define D0_MADR         ((volatile u_int *)(0x10008010))
#define D0_QWC          ((volatile u_int *)(0x10008020))
#define D0_TADR         ((volatile u_int *)(0x10008030))
#define D0_ASR0         ((volatile u_int *)(0x10008040))
#define D0_ASR1         ((volatile u_int *)(0x10008050))

/* VU0 */
#define VU0_MICRO       ((volatile u_long *)(0x11000000))
#define VU0_MEM         ((volatile u_long128 *)(0x11004000))

/* VU1 */
#define VU1_MICRO       ((volatile u_long *)(0x11008000))
#define VU1_MEM         ((volatile u_long128 *)(0x1100c000))

//
// Bitfield Structure
//
typedef struct {
	unsigned DIR: 1;	// Direction
	unsigned p0 : 1;
	unsigned MOD: 2;	// Mode
	unsigned ASP: 2;	// Address stack pointer
	unsigned TTE: 1;	// Tag trasfer enable
	unsigned TIE: 1;	// Tag interrupt enable
	unsigned STR: 1;	// start
	unsigned p1 : 7;
	unsigned TAG:16;	// DMAtag
} tD_CHCR;

#endif EE_REGS_H

