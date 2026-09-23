#include "LoadBg/loadbg_map.h"
#include "DBG/verbose.h"
#include "GFW/sh2gfw_read_process.h"

static loadBgTEX_Ctrl lbMAP_Ctrl = {0};

static int _loadBgMAP_Delete(int slot);
static int _loadBgMAP_Regist(int slot, int mapid, void* addr, int size);
static int _loadBgMAP_Replace(int slot, int mapid, void* addr, int size);
static int loadBgTEX_AreaInit(int init);
static int loadBgTEX_RoomInit(int init);
static int loadBgMAP_BlockInit(int slot, int init);

static int _loadBgMAP_Delete(int slot) {
    void* addr;   
    
    ASSERT_ON_LINE(0<=slot && slot<LBM_TEX_SLOTS+LBM_MAP_SLOTS, 28);
    addr = lbMAP_Ctrl.addr[slot];
    lbMAP_Ctrl.mapid[slot] = 0;
    lbMAP_Ctrl.addr[slot] = NULL;
    lbMAP_Ctrl.size[slot] = 0;
    if (addr == NULL) {
        return 0;
    }
    switch (slot) {
        case 0: return loadBgTEX_AreaInit(0);
        case 1: return loadBgTEX_RoomInit(0);
        default: return loadBgMAP_BlockInit(slot - 2, 0);
    }


}

static int _loadBgMAP_Regist(int slot, int mapid, void* addr, int size) {
    ASSERT_ON_LINE(0<=slot && slot<LBM_TEX_SLOTS+LBM_MAP_SLOTS, 47);
    if ((mapid == lbMAP_Ctrl.mapid[slot]) &&
        (lbMAP_Ctrl.addr[slot] == addr) &&
        (lbMAP_Ctrl.size[slot] == size)) {
        
        return 0;
    }
    lbMAP_Ctrl.mapid[slot] = mapid;
    lbMAP_Ctrl.addr[slot] = addr;
    lbMAP_Ctrl.size[slot] = size;
    switch (slot) {
        case 0: return loadBgTEX_AreaInit(1);
        case 1: return loadBgTEX_RoomInit(1);
        default: return loadBgMAP_BlockInit(slot - 2, 1);
    }


}

static int _loadBgMAP_Replace(int slot, int mapid, void* addr, int size) {
    int ret = 0;
    if (((mapid != lbMAP_Ctrl.mapid[slot]) ||
         (lbMAP_Ctrl.addr[slot] != addr) ||
         (lbMAP_Ctrl.size[slot] != size)) ) {
        
        
        if (_loadBgMAP_Delete(slot))
            ret++;
    }
    
    if ((mapid != 0)) {
        
        if (_loadBgMAP_Regist(slot, mapid, addr, size)) ret += 2;        
    }
    return ret;
}

int loadBgTEX_Replace(int slot, int mapid, void* addr, int size) {
    int ret; 
    ret = _loadBgMAP_Replace(slot, mapid, addr, size);
    switch (ret) {
        
    case 1:                
        verbose(1, "- map(%c)\n", (slot != 0) ? 0x54 : 0x47);
        break;
        
    case 2:        
        verbose(1, " +map(%c):0x%08x(@0x%08x+0x%08x)\n", (slot != 0) ? 0x54 : 0x47, mapid, addr, size);
        
        break;

        
    case 3:        
        verbose(1, "-+map(%c):0x%08x(@0x%08x+0x%08x)\n", (slot != 0) ? 0x54 : 0x47, mapid, addr, size);
        break;
    }
    
    return ret;
}

int loadBgMAP_Replace(int slot, int mapid, void* addr, int size) {
    int ret;
    ret = _loadBgMAP_Replace(slot + 2, mapid, addr, size);
    switch (ret) {
    
    case 1:
        verbose(1, "- map(%d)\n", slot);
        break;
    
    case 2:
        verbose(1, " +map(%d):0x%08x(@0x%08x+0x%08x)\n", slot, mapid, addr, size);
        break;

        
    case 3:
        verbose(1, "-+map(%d):0x%08x(@0x%08x+0x%08x)\n", slot, mapid, addr, size);
        break;
    }
    return ret;
}

void loadBgMAP_AllClear(void) {
    int i;  
    for (i = 0; i < LBM_MAP_SLOTS; i++) {
        loadBgMAP_Replace(i, 0, NULL, 0);
    }
}

static int loadBgTEX_AreaInit(int init) {
    int mapid;
    void* addr;  
    int size;


    addr = lbMAP_Ctrl.addr[0];   
    if (init != 0) {
        
        mapid = lbMAP_Ctrl.mapid[0];
        size = lbMAP_Ctrl.size[0];
        if ((mapid != 0) && (addr != NULL)) {
            if (size > 0x40000) { // @todo: add define
                sh2gfw_Set_GB_Tex(addr);
                verbose(1, "loadbg_map.c:165> GB tex: registed\n");
            } else {
                printf("loadbg_map.c:167> GB tex: probably, illegal size(%d)!!\n", size);                
            }
        } else {
            printf("loadbg_map.c:170> GB tex: not exist!!\n");
        }
    } else {
        
        
        
        sh2gfw_Delete_GB_Tex();
        verbose(1, "loadbg_map.c:177> GB tex: removed\n");
    }
    
    return 1;
}

static int loadBgTEX_RoomInit(int init) {
    int mapid;
    void* addr; 
    int size;

    addr = lbMAP_Ctrl.addr[1];   
    if (init != 0) {
        
        mapid = lbMAP_Ctrl.mapid[1];
        size = lbMAP_Ctrl.size[1];
        if ((mapid != 0) && (addr != NULL)) {
            if (size > 0x40000) {
                sh2gfw_Set_TR_Tex(addr);
                verbose(1, "loadbg_map.c:197> TR tex: registed\n");
            } else {
                printf("loadbg_map.c:199> TR tex: probably, illegal size(%d)!!\n", size);
            }
        } else {
            printf("loadbg_map.c:202> TR tex: not exist!!\n");
        }
    } else {
        
        
        
        sh2gfw_Delete_TR_Tex();
        verbose(1, "loadbg_map.c:209> TR tex: removed\n");
    }
        
    return 1;
}

static int loadBgMAP_BlockInit(int slot, int init) {
    int mapid;
    void* addr;
    int size;

    addr = lbMAP_Ctrl.addr[slot + 2];
    if (init != 0) {
        
        mapid = lbMAP_Ctrl.mapid[slot + 2];
        size = lbMAP_Ctrl.size[slot + 2];
        if ((mapid != 0) && (addr != NULL) && (size > 0)) {
            sh2gfw_Set_BlockLocal(slot, addr, mapid);
            verbose(1, "loadbg_map.c:228> Block(0x%08x): registed\n", mapid);
        } else {
            printf("loadbg_map.c:230> Block(0x%08x): not exist!!\n", mapid);
        }
        return 1;
    }
    
    
    
    verbose(1, "loadbg_map.c:237> Block(0x%08x): removed\n", mapid); // did they make a mistake? mapid could not be initialized 
    sh2gfw_Delete_BlockLocal(slot);
    
    
    return 1;
}
