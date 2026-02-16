#include "common.h"

extern int func_00199C70(int arg0);
extern void func_0016CA40(int arg0);

extern u32 D_1D31674[3];

void func_01F6D680_heaven_00(void)
{
    if (func_00199C70(0x6) != 0)
    {
        D_1D31674[2] = (D_1D31674[2] | 0x8000000);
    }
}

void func_01F6D6C0_heaven_00(void)
{
    if ((D_1D31674[2] >> 0x1B) & 1)
    {
        func_0016CA40(0xD);
    }
}
