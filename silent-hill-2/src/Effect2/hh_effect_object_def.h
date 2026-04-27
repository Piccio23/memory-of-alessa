#ifndef HH_EFFECT_OBJECT_DEF_H
#define HH_EFFECT_OBJECT_DEF_H

#include "common.h"
#include "Effect2/hh_class_manager.h"

void HH_Effect_Object_Impact_Post(ImpactQueue_Element* pElement);

void HH_Effect_Object_DesignateClassInstance_Clear(u_int Class_Descriptor);

void HH_Effect_Object_DesignateHandleInstance_Clear(u_int hInstance);

Object_Group_Infomeation* HH_Effect_Object_Infomeation_Get(void);

void HH_Effect_Object_Manager(void);

u_int HH_Effect_Object_MemoryBlock_Allocate(void);

void HH_Effect_Object_AutoPost(void);

#endif // HH_EFFECT_OBJECT_DEF_H
