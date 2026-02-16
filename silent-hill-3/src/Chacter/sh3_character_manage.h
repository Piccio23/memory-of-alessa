#ifndef SH3_CHARACTER_MANAGE_H
#define SH3_CHARACTER_MANAGE_H

#include "common.h"
#include "Chacter/character.h"

extern s16 id_counter;

int shCharacter_Manage_Delete(u16 kind, u16 id);
int shCharacter_Manage_Init();

// deletion func?
void func_0012F4E0();

/* maybe externs */
extern void func_0022EBD0(void *, int);
extern void func_0025BE20(u32 kind, u32 id);
extern void func_0022E9D0();

/* externs */
extern void *sh3gfw_Get_pMD(u16 unknown);
extern void SCSetModel(SubCharacterDisp *scp, int model, int anime);

/**
 * character for deletion. part of shCharacterAll?
 */
extern SubCharacter *D_003DAD54;
extern SubCharacter *D_003DAD58; // head

#endif
