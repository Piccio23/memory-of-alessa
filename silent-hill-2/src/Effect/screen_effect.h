#ifndef SCREEN_EFFECT_H
#define SCREEN_EFFECT_H

#include "common.h"

// total size: 0x10
typedef struct ScreenEffect_Parameter {
    // Members
    int fade_status; // offset 0x0, size 0x4
    int fade_type; // offset 0x4, size 0x4
    float fade_timer_now; // offset 0x8, size 0x4
    float fade_timer_max; // offset 0xC, size 0x4
} ScreenEffect_Parameter;

ScreenEffect_Parameter scr_efct; // size: 0x10, address: 0x11B67C0

void ScreenEffectInit(void);
void ScreenEffectManager(void);
void ScreenEffectFadeStart(int type /* r2 */, float time /* r29+0x10 */);
int ScreenEffectFadeCheck(void);
void ScreenEffectFadeStop(void);

#endif // SCREEN_EFFECT_H
