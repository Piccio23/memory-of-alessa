#include "sh2_common.h"
#include "GFW/sh2_GsAllEnv.h"
#include "sh2shd/sh2shd_structs.h"
#include "Heap/utilheap.h"
#include "sh2shd/sh2shd_shadow_model.h"

static void sh2shd_renew_shadow_man(CAMERA_DAT* cam, int glb_coord, int map_id);
static void make_chara_reftag_pool_and_kick_packet_for_spot(void);
static void make_bg_reftag_pool_and_kick_packet_for_spot(float spot_cam_angle);
static void make_chara_reftag_pool_and_kick_packet_for_point(void);
static void make_chara_reftag_pool_and_kick_packet_for_self(void);
static void make_chara_reftag_pool_and_kick_packet_for_parallel(void);
static void make_bg_reftag_pool_and_kick_packet_for_parallel(void);
static float get_spot_camera_angle(float* cam_pos, float* light_pos, float* light_dir, float* light_param);

extern u_int Shadow_micro_code[];
extern u_int Shadow_micro_code_parallel[];

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

Q_WORDDATA* sh2shd_exe_shadow(CAMERA_DAT* cam) {
    int i; // r4
    sceVu0FVECTOR cam_pos; // r29+0x40
    float spot_cam_angle_bg; // r20
    int map_id; // r29+0x58
    int glb_coord; // r29+0x5C
    int demo_no; // r16
    int count; // r2

    demo_no = DramaDemoNumber();

















    
    if (shadow_man.change_flag == 0)
        return NULL;

    
    if (shadow_man.chr_shadow_switch == 0) {
    
        if (shadow_man.bg_shadow_switch == 0)
            return NULL;
        if (shadow_man.outdoor_man_num == 0)
            return NULL;
        
        shadow_man.spot_char_num = 0;
        shadow_man.self_num = 0;
        shadow_man.parallel_char_num = 0;
        shadow_man.point_char_num = 0;
    }
    else if (shadow_man.bg_shadow_switch == 0) {
        
        if (shadow_man.chr_shadow_switch == 0)
            return NULL;
        if (shadow_man.char_man_num == 0)
            return NULL;

        shadow_man.spot_bg_num = 0;
        shadow_man.parallel_bg_num = 0;
    }

    
    get_map_id(&glb_coord, &map_id);
    
    
    
    if (demo_no != 0)
        sh2shd_demo_shadow_off(demo_no);
    else
        sh2shd_shadow_off(glb_coord, map_id);
    
    
    
    
    
    
    
    
    
    
    
    vwGetViewPosition(&cam_pos);
    
    
    
    
    if (shadow_man.change_flag == 1) {
    
        
        sh2shd_reset_packet_buf(&shadow_man.reftag_pool);
        sh2shd_reset_packet_buf(&shadow_man.kick_packet);
        
        
        if (shadow_man.spot_char_num > 0) {
        
            
            shadow_micro_init(shadow_micro_frame, &shGs_AllEnv);
            shadow_add_micro2kick_packet(shadow_micro_frame, &shadow_man.kick_packet, &Shadow_micro_code);
        
            
            
            make_chara_reftag_pool_and_kick_packet_for_spot();
        }
        
        
        if (shadow_man.spot_bg_num > 0) {
        
            
            
            for (i = 0; i < 4; i++) {
                if (shadow_man.outdoor_man[i] != NULL) break;
            }
            
            
            
            spot_cam_angle_bg = get_spot_camera_angle(cam_pos, shadow_man.outdoor_man[i]->light_pos, shadow_man.outdoor_man[i]->light_dir, shadow_man.outdoor_man[i]->light_param);
            
            
            
            
            
            shadow_micro_init(&shadow_micro_frame[1], &shGs_AllEnv);
            shadow_add_micro2kick_packet(&shadow_micro_frame[1], &shadow_man.kick_packet, Shadow_micro_code);
            





            
            make_bg_reftag_pool_and_kick_packet_for_spot(spot_cam_angle_bg);
        }
        
        
        
        
        
        if (shadow_man.self_num > 0) {
        
            shadow_micro_init(&shadow_micro_frame_parallel[0], &shGs_AllEnv);
            shadow_add_micro2kick_packet(&shadow_micro_frame_parallel[0], &shadow_man.kick_packet, Shadow_micro_code_parallel);
            
            
            make_chara_reftag_pool_and_kick_packet_for_self();
        }
        
        
        
        
        if (shadow_man.point_char_num > 0) {
        
            
            shadow_micro_init(&shadow_micro_frame_point, &shGs_AllEnv);
            shadow_add_micro2kick_packet(&shadow_micro_frame_point, &shadow_man.kick_packet, Shadow_micro_code);
            
            
            
            make_chara_reftag_pool_and_kick_packet_for_point();
        }
        
        
        
        
        
        
        if (shadow_man.parallel_char_num > 0) {
        
            
            shadow_micro_init(&shadow_micro_frame_parallel[1], &shGs_AllEnv);
            shadow_add_micro2kick_packet(&shadow_micro_frame_parallel[1], &shadow_man.kick_packet, Shadow_micro_code_parallel);
            
            
            
            make_chara_reftag_pool_and_kick_packet_for_parallel();
        }
        
        
        
        if (shadow_man.parallel_bg_num > 0) {
        
            
            shadow_micro_init(&shadow_micro_frame_parallel[2], &shGs_AllEnv);
            shadow_add_micro2kick_packet(&shadow_micro_frame_parallel[2], &shadow_man.kick_packet, Shadow_micro_code_parallel);
            
            
            make_bg_reftag_pool_and_kick_packet_for_parallel();
        }
        
        
        shadow_man.change_flag = 0;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    sh2shd_renew_shadow_man(cam, glb_coord, map_id);
    
    return shadow_man.kick_packet.head;
}

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
