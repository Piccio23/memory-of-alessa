#include "common.h"

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6D680_apart_00);

void func_01F6D680_apart_00(void);

int func_001DE5B0(void (*cb)(void), int arg, int flag);

int func_01F6D7B0_apart_00(int arg0) {
    return func_001DE5B0(func_01F6D680_apart_00, arg0, 1);
}

typedef int s32;
typedef float f32;

extern void func_001C2290(s32, s32, f32);

void func_01F6D7D0_apart_00(void* arg0) {
    char* base;
    char* temp_v1;
    s32 temp_a0;
    s32 temp_a1;
    s32 addr;

    base = (char*)arg0;

    temp_a1 = *(s32*)(base + 0x1A8);

    addr = temp_a1 * 0xC;
    addr += (s32)base;
    temp_v1 = (char*)addr;

    temp_a0 = *(s32*)(temp_v1 + 0x1BC);

    if ((temp_a0 != 0) &&
        !(*(f32*)(base + 0x1B4) < *(f32*)(temp_v1 + 0x1C0))) {

        func_001C2290(
            temp_a0,
            temp_a1,
            *(f32*)(temp_v1 + 0x1C4)
        );

        *(s32*)(base + 0x1A8) =
            *(s32*)(base + 0x1A8) + 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6D840_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6D920_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6DB90_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6DDA0_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6DEB0_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6DF30_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6DFB0_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E050_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E060_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E770_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E7A0_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E800_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6E9A0_apart_00);

INCLUDE_ASM("asm/nonmatchings/Event/apart_00", func_01F6EB70_apart_00);
