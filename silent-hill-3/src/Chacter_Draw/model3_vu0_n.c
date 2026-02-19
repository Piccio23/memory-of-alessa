#include "common.h"
#include "eestruct.h"
#include "model3_vu0_n.h"

void InitTriangleNormal(TriangleNormal* p) {
    int qwc = 12;
    p->dmatag.u64[0] = 0x2000000C; // 12 quadwords
    p->dmatag.u32[2] = 0;
    p->dmatag.u32[3] = 0x5000000C; // payload?

    p->n_giftag.u64[0] = SCE_GIF_SET_TAG(
        1,
        1,
        1,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_TRI, 1, 1, 1, 1, 0, 0, 0, 0),
        SCE_GIF_PACKED,
        11
    );
    p->n_giftag.u64[1] =
        GIF_REG(SCE_GIF_PACKED_AD, 0)  |
        GIF_REG(SCE_GIF_PACKED_AD, 1)  |
        GIF_REG(SCE_GS_ST,         2)  |
        GIF_REG(SCE_GS_RGBAQ,      3)  |
        GIF_REG(SCE_GS_XYZF2,      4)  |
        GIF_REG(SCE_GS_ST,         5)  |
        GIF_REG(SCE_GS_RGBAQ,      6)  |
        GIF_REG(SCE_GS_XYZF2,      7)  |
        GIF_REG(SCE_GS_ST,         8)  |
        GIF_REG(SCE_GS_RGBAQ,      9)  |
        GIF_REG(SCE_GS_XYZF2,      10) |
        GIF_REG(SCE_GS_PRIM,       11);
    p->n_tex0.s64[1] = 6;
    p->n_clamp.s64[1] = 8;
}

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D3DB0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D3EA0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D3FA0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4090);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D40F0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D41F0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D44F0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4760);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4BD0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4C80);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4CA0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4CD0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4D30);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4D40);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D4FD0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", SortTriangleNormalEnviron);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D55F0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D5910);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D5C50);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D6000);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D6110);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", DrawPart0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", DrawParts0);

INCLUDE_ASM("asm/nonmatchings/Chacter_Draw/model3_vu0_n", func_001D67E0);
