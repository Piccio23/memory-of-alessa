#include "dic.h"

INCLUDE_ASM("asm/nonmatchings/Font/dic", dicSetStr);

INCLUDE_ASM("asm/nonmatchings/Font/dic", dicTransCode);

INCLUDE_ASM("asm/nonmatchings/Font/dic", dicCodeAsc);

INCLUDE_ASM("asm/nonmatchings/Font/dic", dicCode81);

u_short dicCode82(u_char c) {
    if (!IS_VALID_SJIS_82(c))
        return DICTIONARY_INVALID;

    if (c <= SJIS_82_DIGIT_MAX)        // 0x4F–0x58, ０–９
        return c + 0x123;
    if (c <= SJIS_82_UPPER_MAX)        // 0x60–0x79, Ａ–Ｚ
        return c + 0x11C;
    if (c <= SJIS_82_LOWER_MAX)        // 0x81–0x9A, ａ–ｚ
        return c + 0x115;
    return c + 0x111;                  // 0x9F–0xF1, ぁ–ん
}

INCLUDE_ASM("asm/nonmatchings/Font/dic", dicCode83);

INCLUDE_ASM("asm/nonmatchings/Font/dic", dicCode84);

INCLUDE_ASM("asm/nonmatchings/Font/dic", dicCode87);
