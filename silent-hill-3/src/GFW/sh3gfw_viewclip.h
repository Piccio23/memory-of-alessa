#ifndef SH3GFW_VIEWCLIP_H
#define SH3GFW_VIEWCLIP_H

#include "common.h"

/* ========= not from here ========= */
// likely loads Env_ctl camera params into arg0
extern void func_001B3F00(float* arg0);

// likely sets Env_ctl camera params from arg0
extern void func_001B3E80(float* arg0);

// likely gets VbScreenInfo.scr_z
extern float func_001B4100(void);
// gets an Env_ctl camera param
extern float func_001B4110(void);

/* Env_ctl.objclip_mat (0xB0) */
extern sceVu0FMATRIX D_01D970D0;

#endif // SH3GFW_VIEWCLIP_H
