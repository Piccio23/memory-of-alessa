#ifndef SH2GFW_READ_PROCESS_H
#define SH2GFW_READ_PROCESS_H

#include "sh2_common.h"



void sh2gfw_Set_TrTex(void* pT);
int sh2gfw_LoadSet_SemiTransTEX(int mapid, void* fl);
void sh2gfw_LOAD_AREADATA_ID(u_int stage);

// int sh2gfw_Process_AREAtoMAN(add args);

u_int sh2gfw_process_AreaDATA(u_int map_id);

// void sh2gfw_Free_BlockLocalTex(struct sh2gfw_ALLTEXSYNC_MAN* pATSM, struct sh2gfw_BLOCK_MAN* pB_man);

void sh2gfw_AllClear_TrMAN(void);

// u_int sh2gfw_process_blockLOCAL_main(add args);

void sh2gfw_Set_GB_Tex(void* addr);
void sh2gfw_Delete_GB_Tex(void);
void sh2gfw_Set_TR_Tex(void* addr);
void sh2gfw_Delete_TR_Tex(void);
void sh2gfw_Set_BlockLocal(int slot, void* addr, int mapid);
void sh2gfw_Delete_BlockLocal(int slot);

#endif // SH2GFW_READ_PROCESS_H
