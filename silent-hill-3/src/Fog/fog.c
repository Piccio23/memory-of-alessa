#include "common.h"
#include "Fog/fog.h"

extern FOG_WORK fwork;
extern FOG_PACK_WORK pwork;

extern /* static */ FOG_ASM_DATA1 fog_asm_data1;
extern /* static */ FOG_ASM_DATA2 fog_asm_data2;
extern /* static */ FOG_ASM_DATA_P fog_asm_data_p;
extern /* static */ FOG_ASM_DATA3 fog_asm_data3;

void fogInit(void) {
    shQzero(&fwork, sizeof fwork);
    func_001E6B90();
    fog_asm_data_p.packet = UNCACHED(&pwork);
    fogSetColor(0x80, 0x80, 0x80, 0x80);
    func_001EB090();
    func_001E74F0();
}


INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001E6B90);

void fogSetEnvironment(FOG_ENV_DATA* edata) {
    float d; // r1
    float m; // r20
    u_char f; // r16
    u_char f2; // r17
    char Double; // r2
    int old; // r2

    if (edata == fwork.EnvNow) {
        if ((fwork.WindTimer -= shGetDF()) <= 0) {
            fogChangeWind(fwork.WindDef);
        }
        return;
    }
    fwork.EnvNow = edata;
    if (!edata) {
        fwork.PartNum = 0;
        fwork.EnvNow = NULL;
        return;
    }
    f = edata->Flag;
    m = edata->MaxPos;
    f2 = 0;
    if (edata->MaxPos > 2000.0f + fwork.MaxPos) f2 = 1;
    fwork.MaxPos = m;
    fog_asm_data1.maxpos = m;

    fog_asm_data1.maxpos_x2 = 2.0f * m;
    fog_asm_data1.screendiv = 4.0f / m;
    fog_asm_data1.r_maxpos = 2.0f / m;
    fog_asm_data3.maxpos = m;
    d = edata->PartSize;
    fwork.PartSize = d;
    fog_asm_data1.part_size = d;
    fog_asm_data1.wall_range = 10.0f + d;
    fog_asm_data2.part_size = d;
    fog_asm_data2.r_part_size = 1.0f / d;
    d = edata->EscapeRange;
    fwork.EscapeRange = d;
    fog_asm_data1.escape_range = d;
    fog_asm_data1.r_escape_range = 1.0f / d;
    d = edata->FloorY;
    fwork.FloorY = d;
    fog_asm_data2.floor_y = d;
    fwork.WaterY = edata->WaterY;
    
    old = fwork.WindDef;
    fwork.WindDef = edata->WindDef;
    if (fwork.WindDef != old) {
        fogChangeWind(fwork.WindDef);
    }
    if (f & 1) {
        fwork.LimitY = edata->LimitY;
        fwork.LimitY2 = edata->LimitY - edata->LimitHeight;
        fog_asm_data1.r_height = 1.0f / edata->LimitHeight;
    } else {
        fwork.LimitY = -MAX_FLOAT;
    }
    Double = edata->Double;
    fwork.Double = Double;
    if (1 < Double) {
        d = (1 << (Double - 1));
        fog_asm_data3.r_double = 1.0f / d;
    } else {
        d = 1.0f;
        fog_asm_data3.r_double = 1.0f;
    }
    fog_asm_data1.double_rate = 1 << Double;
    d = m / d;
    fog_asm_data1.higher_y = Double < 2 ? m : d;
    fog_asm_data1.lower_y = Double == 0 ? m : 0.0f;
    fog_asm_data1.y_max = Double == 0 ? 2.0f * m : d;
    fog_asm_data1.higher_y2 = 2.0f * (Double < 2 ? m : d);
    fwork.Alpha = edata->Alpha;
    d = edata->Alpha;
    fog_asm_data1.alpha = d;
    fog_asm_data1.minus_alpha = -d / 32.0f;
    fwork.GridRate = edata->GridRate;
    fogSetPartNum(edata->PartNum);
    fwork.Flag = (fwork.Flag & 0xff00) | f;
    if (f2) fogInitParticle();
}

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001E74F0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001E7520);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogChangeWind);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogInitParticle);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_init_part_sub);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_newpos);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogResetWall);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetWall);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogResetObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001E8470);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogGetObj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogMoveParticle);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_load_objdata);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_set_stay);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_wall);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001E91E0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_obj);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_obj2);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_alp);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_part_clamp);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogMakePacket);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fog_view_screen_fog);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetColor);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetPartNum);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetProjection);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA580);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA5C0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA5E0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA610);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetWorldPosV);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA670);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA6A0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA6C0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA6D0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetLocalPosV);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA980);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA9A0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA9C0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EA9E0);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", fogSetSpeedLevel);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EAA10);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EAA60);

INCLUDE_ASM("asm/nonmatchings/Fog/fog", func_001EAA80);
