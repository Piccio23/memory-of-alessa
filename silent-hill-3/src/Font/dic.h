#ifndef FONT_DIC_H
#define FONT_DIC_H

#include "common.h"

#define DICTIONARY_INVALID 0x7FFF

#define DICTIONARY_INVALID    0x7FFF
#define SJIS_82_DIGIT_MIN     0x4F
#define SJIS_82_DIGIT_MAX     0x58
#define SJIS_82_UPPER_MIN     0x60
#define SJIS_82_UPPER_MAX     0x79
#define SJIS_82_LOWER_MIN     0x81
#define SJIS_82_LOWER_MAX     0x9A
#define SJIS_82_HIRA_MIN      0x9F
#define SJIS_82_HIRA_MAX      0xF2

#define IS_VALID_SJIS_82(c) ( \
    ((c) >= SJIS_82_DIGIT_MIN) && \
    ((c) < SJIS_82_DIGIT_MAX + 1 || (c) > SJIS_82_UPPER_MIN - 1) && \
    ((c) < SJIS_82_UPPER_MAX + 1 || (c) > SJIS_82_LOWER_MIN - 1) && \
    ((c) < SJIS_82_LOWER_MAX + 1 || (c) > SJIS_82_HIRA_MIN - 1) && \
    ((c) < SJIS_82_HIRA_MAX) \
)

#endif