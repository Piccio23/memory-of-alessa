#include "LoadBg/loadbg_kg2.h"
#include "DBG/verbose.h"
#include "sh2shd/sh2shd_structs.h"

static loadBgKG2_Ctrl lbKG2_Ctrl = {0};

static int _loadBgKG2_Delete(int slot);
static int _loadBgKG2_Regist(int slot, int mapid, void* addr, int size);
static int _loadBgKG2_Replace(int slot, int mapid, void* addr, int size);

static int _loadBgKG2_Delete(int slot) {
    void* addr;
    ASSERT_ON_LINE(0<=slot && slot<LBM_KG2_SLOTS, 23);
    addr = lbKG2_Ctrl.addr[slot];
    lbKG2_Ctrl.mapid[slot] = 0;
    lbKG2_Ctrl.addr[slot] = NULL;
    lbKG2_Ctrl.size[slot] = 0;
    return (addr != NULL);  
}

INCLUDE_ASM("asm/nonmatchings/LoadBg/loadbg_kg2", _loadBgKG2_Regist);

static int _loadBgKG2_Replace(int slot, int mapid, void* addr, int size) {
    int ret = 0; 
    if (((mapid != lbKG2_Ctrl.mapid[slot]) ||
         (lbKG2_Ctrl.addr[slot] != addr) ||
         (lbKG2_Ctrl.size[slot] != size))) {
        
        if (_loadBgKG2_Delete(slot)) ret++;
    }
    if ((mapid != 0) && (addr != NULL) && (size > 0)) {
         if (_loadBgKG2_Regist(slot, mapid, addr, size)) ret += 2;
    }
    return ret;
}

int loadBgKG2_Replace(int slot, int mapid, void* addr, int size) {
    int ret;
    ret = _loadBgKG2_Replace(slot, mapid, addr, size);
    switch (ret) {
    case 1:
        // VERBOSE_ON_LINE(91, 1, "- cld(%d)\n", slot);
        verbose(1, "- kg2(%d)\n", slot);
        break;
    case 2:
        //VERBOSE_ON_LINE(94, 1, " +cld(%d):0x%08x(@0x%08x+0x%08x)\n", slot, mapid, addr, size);
        verbose(1, " +kg2(%d):0x%08x(@0x%08x+0x%08x)\n", slot, mapid, addr, size);
        break;
    case 3:
        //VERBOSE_ON_LINE(97, 1, "-+cld(%d):0x%08x(@0x%08x+0x%08x)\n", slot, mapid, addr, size);
        verbose(1, "-+kg2(%d):0x%08x(@0x%08x+0x%08x)\n", slot, mapid, addr, size);
        break;
    }
    return ret;
}

void** loadBgKG2_GetLoadedDataAddrList(void) {
    int i;
    int j;   
    void* addr;

    j = 0;
    for (i = 0; i < LBM_KG2_SLOTS; i++) {
        addr = lbKG2_Ctrl.addr[i];
        if (addr != NULL) lbKG2_Ctrl.list[j++] = addr;        
    }
    lbKG2_Ctrl.list[j] = NULL;

    return lbKG2_Ctrl.list;
}
