#include "sh2_common.h"
#include "Chacter/character.h"
#include "Event/event.h"
#include "Event/event_sub.h"
#include "Event/stage/stg_tgs_trial.h"
#include "SH2_common/sh2dt.h"
#include "Event/picture.h"
#include "Event/event_sub.h"

static int EvProgBoxWithKeyCursor(void);
static int EvProgBoxWithKeyLayer(void);
static int EvProgBoxWithKeyOpen(int alp /* r16 */);

extern /* static */ float cyl_alp; // size: 0x4, address: 0x11EA360
extern /* static */ short tex[9][4][4]; // @ 0x00355FD0
extern /* static */ short pos[9][4][2]; // @ 0x003560F0

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgTrialStartSet);

int EvProgGetHospitalMap(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgGetNeedle);

#line 329
static int EvProgGuruguruNumber(void) {
    PicDraw_Data pic; // r29+0x30
    int no; // r2
    int i; // r16






























    switch (ev_p_step) {
        case 0:
            SCNowPlayableEventSwitch(sh2jms.player, 1);
            if (GET_GAME_FLAG(6, 0)) SET_EV_STEP(2, 0)
            else SET_EV_STEP(10, 0);
            break;

        case 10:
            if (EvSubMessage(3))
                if (ev_cancel) {
                    ev_prog_flag_set = 0;
                    SET_EV_STEP(13, 0);
                } else SET_EV_STEP(2, 0);
            break;

        case 2:
            if (EvSubFileLoadAndFadeOut(
                    NULL,
                    data_pic_hsp_p_boxnumber_tex,
                    data_pic_hsp_p_boxnumber_2_tex))
                SET_EV_STEP(8, 0);
            break;

        case 8:
        case 7:
        case 4:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            PictureLoadImage((sh2gfw_AREA_HEAD* ) layer_adr, 2, -1, -1);
            
            shQzero(&pic.ap, 0x44);
            
            picture_set_ap(&pic, layer_adr);
            pic.otp = 3;
            picture_set_alpha(&pic, 0x80);
            for (i = 0; i < 4; i++) {
                no = game_flag.guruguru[i];
                
                
                
                picture_set_bounds(&pic,
                                   pos[no][i],
                                   tex[no][i]);
                picture_set_tex_coords(&pic, tex[no][i]);
                PictureDraw(&pic);
            }
            if (ev_p_step == 7) EvSubPictureFilter();
            EvSubPictureEnd();
            if (ev_p_step == 8) {
                if (shPadTrigger(0, key_config.enter))
                    SET_EV_STEP(7, 0);
            } else
                if (ev_p_step == 7) {
                    if (EvSubMessage(4))
    
                        SET_EV_STEP(4, 0);
                } else 
                    if (ScreenEffectFadeCheck()) {
                    
                        SET_EV_STEP(13, 0);
                    }
            break;
        
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            return 1;
    }
    return 0;
}

#line 437
int EvProgLouiseTakecare(void) {
    switch (ev_p_step) {
        case 0:
            if (GET_BIT(game_flag.flag[5], 31)) SET_EV_STEP(12, 0)
            else SET_EV_STEP(11, 0);
            SCNowPlayableEventSwitch(sh2jms.player, 1);
            break;
        
        case 11:
            if (EvSubMessage(3)) {
                if (ev_cancel) {
                    ev_prog_flag_set = 0;
                    SET_EV_STEP(13, 0);
                } else SET_EV_STEP(12, 0);
            }
            break;

        case 12:
            if (EvSubMessage(9))
                SET_EV_STEP(13, 0);
            break;

        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            return 1;
    }
    return 0;
}

#ifdef NON_MATCHING
#line 474
static int EvProgBoxWithKey(void) {
    switch (ev_p_step) {
        case 0:
            if (GET_GAME_FLAG(6, 5)) cyl_alp = 0.0f;
            else cyl_alp = 1.0f;
            SCNowPlayableEventSwitch(sh2jms.player, 1);
            ev_cursor_y = 0.0f;
            ev_cursor_x = 0.0f;
            SET_EV_STEP(2, 0);
            break;


        
        case 2:
            if (EvSubFileLoadAndFadeOut(NULL, &data_pic_hsp_p_box_tex, &data_pic_hsp_pboxkey01_tex)) {
                if (GET_GAME_FLAG(6, 2)) {
                    SET_EV_STEP(9, 0);
                    SeCall(0x4DBA, 1.0f, 0);
                } else SET_EV_STEP(10, 0);
            }
            break;
        
        case 9:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureFilter();
            EvProgBoxWithKeyLayer();
            EvSubPictureEnd();
            
            if (EvSubItemUse0(0x20, 0x17, 0, 0, 0, 0)) {
                SET_GAME_FLAG(6, 1);
                if (GET_GAME_FLAG(6, 5)) SET_EV_STEP(12, 0)
                else SET_EV_STEP(10, 0);
            }
            break;

        
        case 10:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureFilter();
            EvProgBoxWithKeyLayer();
            EvSubPictureEnd();
            if (EvSubMessage(0xA)) {
                ev_cursor_x = 0.0f;
                ev_cursor_y = 0.0f;
                SET_EV_STEP(7, 0);
            }
            break;
        case 7:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvProgBoxWithKeyLayer();
            EvProgBoxWithKeyCursor();
            EvSubPictureCursor(0);
            EvSubPictureEnd();
            if ((game_flag.guruguru[0] == game_flag.cylinder[0]) &&
                (game_flag.guruguru[1] == game_flag.cylinder[1]) &&
                (game_flag.guruguru[2] == game_flag.cylinder[2]) &&
                (game_flag.guruguru[3] == game_flag.cylinder[3])) {
                SET_GAME_FLAG(6, 5);
                SeCall(0x4A46, 1.0f, 0);
                SET_EV_STEP(14, 0);
            } else if (shPadTrigger(0, key_config.cancel)) {
                
                SET_EV_STEP(4, 0);
            }
            break;

        case 14:            
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvProgBoxWithKeyLayer();
            EvSubPictureCursor(0);
            EvSubPictureEnd();
            cyl_alp -= 0.5f * shGetDT();
            if (cyl_alp <= 0.0f) {
                if (GET_GAME_FLAG(6, 1)) SET_EV_STEP(12, 0)
                else SET_EV_STEP(16, 0);
            }
            break;
        
        case 16:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureEnd();
            if ((shPadTrigger(0, key_config.enter)) || (shPadTrigger(0, key_config.cancel))) {
                SET_EV_STEP(4, 0);
            }
            break;
        
        case 12:
            if (EvSubFileLoadAndFadeOut(NULL, &data_pic_hsp_p_hair_tex, &data_pic_hsp_p_hair_hair_tex)) {
                ev_timer = 0.0f;
                SET_EV_STEP(15, 0);
            }
            break;
        
        case 15:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvProgBoxWithKeyOpen(0x80);
            EvSubPictureEnd();
            if ((shPadTrigger(0, key_config.enter)) || (shPadTrigger(0, key_config.cancel))) {
                SET_EV_STEP(17, 0);
            }
            break;
        
        case 17:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvProgBoxWithKeyOpen(0x80);
            EvSubPictureFilter();
            EvSubPictureEnd();
            if (EvSubMessage(7)) {
                SET_EV_STEP(8, 0);
            }
            break;
        
        case 8:
            ev_timer += shGetDT();
            if (ev_timer > 2.0f) {
                ev_timer = 2.0f;
                SET_EV_STEP(18, 0);
            }
            EvSubPictureStart();
            EvSubPictureDisplayOnly();

            EvProgBoxWithKeyOpen(0x80 - (int) ((128.0f * ev_timer) / 2.0f));
            EvSubPictureEnd();
            break;
        
        case 18:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            EvSubPictureFilter();
            EvSubPictureEnd();
            if (EvSubItemGet(0x32, 0x18)) {
                SET_EV_STEP(4, 0);
                SET_GAME_FLAG(5, 11);
            }
            break;
        
        case 4:
            EvSubPictureStart();
            EvSubPictureDisplayOnly();
            
            if (!GET_GAME_FLAG(5, 11) && !GET_GAME_FLAG(6, 5)) {
                EvProgBoxWithKeyLayer();
            }
            
            EvSubPictureEnd();
            if (ScreenEffectFadeCheck()) {
                SET_EV_STEP(13, 0);
            }
            break;
    
        case 13:
            SCNowPlayableEventSwitch(sh2jms.player, 0);
            UNSET_GAME_FLAG(6, 2);
            return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgBoxWithKey);
#endif

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgBoxWithKeyLayer);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgBoxWithKeyCursor);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgBoxWithKeyOpen);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgEmptyBox);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgOnlyNeedle);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgOnlyHair);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgInShowerDrain);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgFishKey);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgDoctorMemo1st);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgDoctorMemo2nd);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgUseElevatorKey);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgElevatorButton);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgElevatorButtonCheck);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgElevatorButtonLight);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvProgTrialEnd);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvRoomInit);

INCLUDE_ASM("asm/nonmatchings/Event/stage/stg_tgs_trial", EvAllTimeFunc);
