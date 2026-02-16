#include "common.h"

#define FONT_STREAM_BUFFER_SIZE 0x4000
struct FONT_DATA {
    // total size: 0x215B0
    u32 tex_head[12]; // size 0x30
    u32 clut_head[12]; // size 0x30
    u32 clut[8]; // size 0x20
    u8 texbuf[131072]; // size 0x20000
    u64 tex0; // size 0x4
    int fonttype; // size 0x4
    u32 rgb_u; // size 0x4
    u32 rgb_d; // size 0x4
    u32 rgb_s[4]; // size 0x10
    u32 alpha; // size 0x4
    u32 alpha_base; // size 0x4
    u32 flag; // size 0x4
    u16 x; // size 0x2
    u16 y; // size 0x2
    u16 wide_w; // size 0x2
    u16 wide_h; // size 0x2
    u16 right_x; // size 0x2
    u16 right_y; // size 0x2
    u16 wm; // size 0x2
    u16 hm; // size 0x2
    s16 unk20C0; // size 0x2
    s16 wait_count; // size 0x2
    s16 wait_type; // size 0x2
    s16 page_sound; // size 0x2
    u16 code[400]; // size 0x320
    s16 upper[400]; // size 0x320
    s16 lower[400]; // size 0x320
    s16 top; // size 0x2
    s16 bottom; // size 0x2
    s16 st_num; // size 0x2
    s16 w_st_num; // size 0x2
    s16 prl_count; // size 0x2
    s16 preload; // size 0x2
    s16 shadow_max; // size 0x2
    s16 shadow_now; // size 0x2
    u16 sel_xl; // size 0x2
    u16 sel_xr; // size 0x2
    u16 sel_yu[4]; // size 0x8
    u16 sel_yd[4]; // size 0x8
    s16 sel_max; // size 0x2
    s16 sel_now; // size 0x2
    u16 mes_v[10][64]; // size 0x500
    u16 * unk20F50; // size 0x2
    u16 * mes_str_now; // size 0x4
    u16 * mes_str; // size 0x4
    u16 * prl_str; // size 0x4
    struct FONT_STREAM_DATA * stream; // size 0x4
    struct WFONT_STREAM_DATA * w_stream; // size 0x4
    struct MFONT_STREAM_DATA * m_stream; // size 0x4
    u16 stream_max; // size 0x2
    u16 w_stream_max; // size 0x2
    u16 m_stream_max; // size 0x2
    u16 m_code[256]; // size 0x200
    s16 m_upper[256]; // size 0x200
    s16 m_lower[256]; // size 0x200
    s16 m_top; // size 0x2
    s16 m_bottom; // size 0x2
    s16 m_st_num; // size 0x2
    int m_base_x; // size 0x4
    int m_base_y; // size 0x4
    int m_base_z; // size 0x4
    u32 m_rgba; // size 0x4
    int m_sx; // size 0x4
    int m_sy; // size 0x4
    int m_w; // size 0x4
    int m_h; // size 0x4
    int m_x; // size 0x4
    int m_y; // size 0x4
    float bar_blink; // size 0x4
    u64 * pCur; // size 0x4
    int base_x; // size 0x4
    int base_y; // size 0x4
    int base_z; // size 0x4
};

typedef struct WFONT_STREAM_DATA {
    // total size: 0x18
    /* 0x00 */ u16 x; // size 0x2
    /* 0x02 */ u16 y; // size 0x2
    /* 0x04 */ u16 vw; // size 0x2
    /* 0x06 */ u16 vh; // size 0x2
    /* 0x08 */ u16 u; // size 0x2
    /* 0x0A */ u16 v; // size 0x2
    /* 0x0C */ u32 rgb_u; // size 0x4
    /* 0x10 */ u32 rgb_d; // size 0x4
    /* 0x14 */ u16 w; // size 0x2
    /* 0x16 */ u16 h; // size 0x2
} WFONT_STREAM_DATA;

typedef struct MFONT_STREAM_DATA {
    // total size: 0x8
    /* 0x0 */ u16 x; // size 0x2
    /* 0x2 */ u16 y; // size 0x2
    /* 0x4 */ u16 u; // size 0x2
    /* 0x6 */ u16 v; // size 0x2
} MFONT_STREAM_DATA;

typedef struct FONT_STREAM_DATA
{
	u16 x;
	u16 y;
	u16 w;
	u16 h;
	u16 u;
	u16 v;
	u32 rgb_u;
	u32 rgb_d;
} FONT_STREAM_DATA;

struct FONT_DATA font;
extern void fontSetColor(int num);
extern void fontSetStreamMax(u16 s_max, u16 ws_max, u16 ms_max);
extern u8 D_01D08FA0[16];
extern short D_003585A8[20][2];
extern short D_003585AA[20][2];
extern u64 font_dma_data[34];
extern char D_01D08FB0[FONT_STREAM_BUFFER_SIZE];
extern void SeCall(float arg0, float arg1, long arg2);
int fontLoad(u16 code);
void fontClear();
void fontSetStreamMax(u16 s_max, u16 ws_max, u16 ms_max);
u16 fontPrintStrMain(u16** pstr, int flag);
void fontSet(u16 code, u16 x, u16 y);
void fontSetBlankBox(int x0, int x1, int y);
void fontSetLine(int x, int w, int y);
void fontSetColorDirect(u8 r, u8 g, u8 b, u8 alp);
void fontSetAlpha(u8 alp);
void fontBarBlink();
void *fontTexLoad(int texadr, int clutadr);
void fontPushButton();
void fontPushButton2();
void fontSelectUp();
void fontSelectDown();
u16 *fontGetMesAdr(u16 *str, u16 num);
void fontMessage(u16 *str);
void fontNextMessage();
int fontGetStatus();
void fontWide(u16 w, u16 h);
void fontAllCenterOn();
void fontAllCenterOff();
void fontShadowOff();
void fontCrushOn();
void fontCrushOff();