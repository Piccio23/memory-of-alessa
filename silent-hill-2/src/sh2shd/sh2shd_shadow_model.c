#include "sh2_common.h"
#include "GFW/sh2_GsAllEnv.h"
#include "sh2shd/sh2shd_structs.h"
#include "Heap/utilheap.h"
#include "sh2shd/sh2shd_shadow_model.h"

void sh2shd_init_shadow(void) {
    int i;

    
    shadow_man.change_flag = 0;
    shadow_man.spot_char_num = 0;
    shadow_man.spot_bg_num = 0;
    shadow_man.self_num = 0;
    shadow_man.parallel_char_num = 0;
    shadow_man.parallel_bg_num = 0;
    shadow_man.point_char_num = 0;
    shadow_man.char_man_num = 0;
    shadow_man.outdoor_man_num = 0;
    
    shadow_man.enemy_num = 0;
    
    
    shadow_man.chr_shadow_switch = 1;
    shadow_man.bg_shadow_switch = 1;

    for (i = 0; i < SHADOW_CHAR_MAN_SIZE; i++)
        shadow_man.char_man[i] = NULL;

    for (i = 0; i < SHADOW_OUTDOOR_MAN_SIZE; i++)
        shadow_man.outdoor_man[i] = NULL;

    shadow_calcheap = utilHeapInit(&Shadow_Calcwork[1], 0x19000U);
    ASSERT_ON_LINE(shadow_calcheap, 2343);


    
    
    sh2shd_init_packet_buf(&shadow_man.kick_packet, Shadow_Kick_Packet);



    
    sh2shd_init_packet_buf(&shadow_man.reftag_pool, Shadow_REFtag_Packet);
    
    

    for (i = 0; i < SHADOW_OFF_WORK_CHAR_SIZE; i++) {
        int j;
    
        shadow_off_work_char[i].kind = 0;
        shadow_off_work_char[i].id = -1;
        for (j = 0; j < SHADOW_OFF_WORK_CHAR_OBJ_COUNT; j++)
            shadow_off_work_char[i].obj_id[j] = -1;
    }

    
    for (i = 0; i < SHADOW_OFF_WORK_BG_SIZE; i++) {
        int j;

        
        shadow_off_work_bg[i].map_id = -1;
        for (j = 0; j < SHADOW_OFF_WORK_BG_OBJ_COUNT; j++)
            shadow_off_work_bg[i].obj_id[j] = -1;
    }
 
    
    shadow_micro_init(&shadow_micro_frame[0], &shGs_AllEnv);
    shadow_micro_init(&shadow_micro_frame[1], &shGs_AllEnv);
    shadow_micro_init(shadow_micro_frame_parallel, &shGs_AllEnv);
    shadow_micro_init(&shadow_micro_frame_point, &shGs_AllEnv);
    shadow_micro_init(&shadow_micro_frame_parallel[1], &shGs_AllEnv);
    shadow_micro_init(&shadow_micro_frame_parallel[2], &shGs_AllEnv);
    
    jms_added_flag = 0;
}

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_reset_shadow);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_add_char);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_Draw_ShadowChar);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_add_map);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_exe_shadow);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_renew_shadow_man);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_chara_reftag_pool_and_kick_packet_for_spot);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_bg_reftag_pool_and_kick_packet_for_spot);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_chara_reftag_pool_and_kick_packet_for_point);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_chara_reftag_pool_and_kick_packet_for_self);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_chara_reftag_pool_and_kick_packet_for_parallel);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", make_bg_reftag_pool_and_kick_packet_for_parallel);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", get_spot_camera_angle);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", get_distance_from_light_to_chara);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_exe_drop_shadow);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_renew_drop_shadow_man);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_make_stencil_drop_shadow_plane);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_make_drop_shadow_plane);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_reset_shadow_off_work);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_add_map_to_shadow_off_work);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_off_obj);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_add_char_to_shadow_off_work);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_off_char_obj);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_off_char_all_parts);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_bg_shadow_off);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", check_self_spot);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", check_self_para);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_del_jms_upper_body);

INCLUDE_ASM("asm/nonmatchings/sh2shd/sh2shd_shadow_model", sh2shd_del_jms_head);
