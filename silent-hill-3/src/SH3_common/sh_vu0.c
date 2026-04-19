#include "common.h"
#include "SH3_common/sh_vu0.h"

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shAngleRegulate);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shAtanV);

asm float shAtan2(register float y, register float x) {
     mfc1       t6, f12
     mfc1       t7, f13
     por        t5, zero, ra
     pcpyld     t7, t6, t7
     jal        shAtan_asm
     qmtc2      t7, vf4
     qmfc2      t7, vf4
     jr         t5
     mtc1       t7, f0
}

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shAtan_asm);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", sh_ecossin);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shSinF);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shCosF);

asm void shSinCosV(register float* out, register float* in) {
	por     t5,zero,ra
	jal     sh_ecossin
	nop     
	vaddx.z vf4z,vf0z,vf4x
	vaddy.x vf4x,vf0x,vf4y
	vsub.yw vf4yw,vf0yw,vf0yw
	jr      t5
	sqc2    vf4,0(a0)
}

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shSinCosV_Scale);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shRotVectorY);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shRotMatrixX);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shRotMatrixY);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shRotMatrixZ);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", sh_mulmatrix);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shRandI);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shRandF);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shRandF_asm);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shRandV_Scale);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shRandV_asm);

asm float shSway1f(float, float) {
	por     t4,zero,ra
	jal     shSway1f_asm
	nop     
	jr      t4
	mov.s   f0,f4
}

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shSway1f_asm);

asm void shCreateNormal(register float* out, register float* vx, register float* vy, register float* fz) {
	lqc2    	vf5, 0(a1)
	lqc2    	vf6, 0(a3)
	lqc2    	vf7, 0(a2)
	vsub.xyzw 	vf6xyzw, vf6xyzw, vf5xyzw
	vsub.xyzw 	vf7xyzw, vf7xyzw, vf5xyzw
	vopmula.xyz ACCxyz, vf6xyz, vf7xyz
	vopmsub.xyz vf4xyz, vf7xyz, vf6xyz
	vmul.xyz 	vf5xyz, vf4xyz, vf4xyz
	vaddy.x 	vf5x, vf5x, vf5y
	vaddz.x 	vf5x, vf5x, vf5z
	vrsqrt  	Q, vf0w, vf5x
	vsub.w  	vf4w, vf4w, vf4w
	vwaitq  
	vmulq.xyz   vf4xyz, vf4xyz, Q
	jr      	ra
	sqc2    	vf4, 0(a0)
}

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shSetMiniMaxN);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shQzero);

INCLUDE_ASM("asm/nonmatchings/SH3_common/sh_vu0", shFill);

asm void shMulMatrix(register float (* m0)[4], register float (* m1)[4], register float (* m2)[4]) {
	lqc2         vf1, 0(a1)
	lqc2         vf2, 0x10(a1)
	lqc2         vf3, 0x20(a1)
	lqc2         vf4, 0x30(a1)
	lqc2         vf5, 0(a2)
	vmulax.xyzw  ACCxyzw, vf1xyzw, vf5x
	vmadday.xyzw ACCxyzw, vf2xyzw, vf5y
	vmaddaz.xyzw ACCxyzw, vf3xyzw, vf5z
	vmaddw.xyzw  vf5xyzw, vf4xyzw, vf5w
	lqc2         vf6, 0x10(a2)
	vmulax.xyzw  ACCxyzw, vf1xyzw, vf6x
	vmadday.xyzw ACCxyzw, vf2xyzw, vf6y
	vmaddaz.xyzw ACCxyzw, vf3xyzw, vf6z
	vmaddw.xyzw  vf6xyzw, vf4xyzw, vf6w
	lqc2         vf7, 0x20(a2)
	vmulax.xyzw  ACCxyzw, vf1xyzw, vf7x
	vmadday.xyzw ACCxyzw, vf2xyzw, vf7y
	vmaddaz.xyzw ACCxyzw, vf3xyzw, vf7z
	vmaddw.xyzw  vf7xyzw, vf4xyzw, vf7w
	lqc2         vf8, 0x30(a2)
	vmulax.xyzw  ACCxyzw, vf1xyzw, vf8x
	vmadday.xyzw ACCxyzw, vf2xyzw, vf8y
	vmaddaz.xyzw ACCxyzw, vf3xyzw, vf8z
	vmaddw.xyzw  vf8xyzw, vf4xyzw, vf8w
	sqc2         vf5, 0(a0)
	sqc2         vf6, 0x10(a0)
	sqc2         vf7, 0x20(a0)
	sqc2         vf8, 0x30(a0)
	jr           ra
	nop
}
