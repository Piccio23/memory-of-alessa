#ifndef FOG_H
#define FOG_H

#include "common.h"

typedef struct FOG_ASM_DATA2_NEW {
    // total size: 0x70
    float center_x; // offset 0x0, size 0x4
    float center_y; // offset 0x4, size 0x4
    float part_size_proj; // offset 0x8, size 0x4
    float center_w; // offset 0xC, size 0x4
    float screen_width; // offset 0x10, size 0x4
    float screen_height; // offset 0x14, size 0x4
    float pad1; // offset 0x18, size 0x4
    float w_width; // offset 0x1C, size 0x4
    float part_size; // offset 0x20, size 0x4
    float pixel_aspect; // offset 0x24, size 0x4
    float part_size_proj2; // offset 0x28, size 0x4
    float r_part_size; // offset 0x2C, size 0x4
    float tex_sth; // offset 0x30, size 0x4
    float floor_y; // offset 0x34, size 0x4
    float tex_move_speed; // offset 0x38, size 0x4
    float n128; // offset 0x3C, size 0x4
    float near_w; // offset 0x40, size 0x4
    float near_w2; // offset 0x44, size 0x4
    float r_near_w2; // offset 0x48, size 0x4
    float nr_128; // offset 0x4C, size 0x4
    int light_max; // offset 0x50, size 0x4
    float light_rate; // offset 0x54, size 0x4
    int light_under; // offset 0x58, size 0x4
    float r_light_under; // offset 0x5C, size 0x4
    float d_rate; // offset 0x60, size 0x4
    float d_under; // offset 0x64, size 0x4
    float d_rate2; // offset 0x68, size 0x4
    float proj; // offset 0x6C, size 0x4
} SH3_FOG_ASM_DATA2;

/* some of these funcs may not exist in sh3, delete the missing ones */

void fogInit(void);

void fog_set_defpacket(void);

void fogSetEnvironment(FOG_ENV_DATA* edata);

void fogInitScreen(void);

void fogInitWind(void);

void fogChangeWind(int wind);

void fogInitParticle(void);

void fog_init_part_sub(FOG_PART_DATA* pd);

void fog_part_newpos(FOG_PART_DATA* pd);

void fogResetWall(void);

void fogSetWall(void* Vector);

void fogResetObj(void);

void fogSetObj(u_long ID, void* Center, float Size);

void fogMoveObj(u_long ID, void* Center);

void fogSetObj2(u_long ID, void* Center, float Size);

void fogEraseObj(u_long ID);

void fogSetObjSize(u_long ID, float Size);

FOG_OBJ_DATA* fogGetObj(u_long ID);

void fogMoveParticle(void);

void fog_load_objdata(void);

void fog_set_stay(void);

void fog_part_wall(void);

void fog_part_grid(void);

void fog_part_obj(void);

void fog_part_obj2(void);

void fog_part_alp(void);

void fog_part_clamp(void);

void fogMakePacket(void);

void fog_view_screen_fog(void);

void fogSetColor(u_char r, u_char g, u_char b, u_char a);

void fogSetPartNum(int PartNum);

void fogSetProjection(float Projection);

void fogSetFloorY(float FloorY);

void fogSetWorldScreenM(void* WorldScreenM);

void fogSetWorldViewM(void* WorldViewM);

void fogSetWorldPosV(void* WorldPosV);

void fogSetStayPos(void* WorldPosV);

void fogResetStayPos(void);

void fogSetStayPoint(void* StayPoint);

void fogResetStayPoint(void);

void fogSetCameraPosV(void* CameraPosV);

void fogSetLocalPosV(void);

void fogSetSpeedLevel(float SpeedLevel);

u_long* fogTex0Adr(void);

#endif // FOG_H
