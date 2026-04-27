#include "Effect2/hh_class_object_execute.h"
#include "Effect2/hh_effect_object_def.h"
#include "Effect2/hh_class_manager.h"
#include "Event/stg_name.h"
#include "Chacter/character.h"
#include "common.h"

static void Prefix_Operation(void);

static void Suffix_Operation(void);

static void Debug_Functions(void);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", Prefix_Operation);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", Suffix_Operation);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", Debug_Functions);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", HH_Class_Object_Initialize);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", HH_Class_Object_Execute);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", HH_Class_Object_Packet_Kick);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", HH_Effect_Object_Blood_Pool_Impact_Post);

void HH_Effect_Object_Blood_Splash_Impact_Post(float* Location, float* Direction, u_int Scp_Address, u_int Impact_Kind) {
    
    int room_name = RoomNameJms(); // r2
    ImpactQueue_Element descriptor; // r29+0x50
    SubCharacter* pSubChar; // r2

    switch (room_name) {
        case 7:
        case 33:
            descriptor.Class_Descriptor = 7;
            break;
        default:
            descriptor.Class_Descriptor = 5;
            break;
    }

    
    descriptor.hInstance = 0;
    descriptor.pResultHandle_Address = 0;
    
    
    pSubChar = (SubCharacter*) Scp_Address;
    sceVu0CopyVector(&descriptor.Option.Vector[0], &pSubChar->pos);
    descriptor.Option.Vector[0][1] = Location[1];
    descriptor.Option.Int_Value[0] = Scp_Address;
    if (Impact_Kind != 0) {
        float _Direction[4]; // r29+0x90

        
        sceVu0ScaleVectorXYZ(&_Direction, Direction, 5.0f);
        _Direction[0] *= -1.0f;
        _Direction[2] *= -1.0f;
        sceVu0CopyVector(&descriptor.Option.Vector[1], _Direction);
    } else {
        float _Direction[4]; // r29+0xA0
        
        
        sceVu0Normalize(_Direction, Direction);
        sceVu0ScaleVectorXYZ(_Direction, _Direction, 2000.0f);
        sceVu0CopyVector(&descriptor.Option.Vector[1], _Direction);
    }
    ImpactDescriptor_Post(HH_Effect_Object_Infomeation_Get(), &descriptor);
}


INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", HH_Effect_Object_Ground_Impact_Post);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", HH_Effect_Object_Ground_Impact_Post_forEnemy);

INCLUDE_ASM("asm/nonmatchings/Effect2/hh_class_object_execute", HH_Effect_Object_WaterSplash_Impact_Post);
