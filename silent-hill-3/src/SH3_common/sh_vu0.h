#ifndef SH_VU0_H
#define SH_VU0_H

float sh_ecossin(float);

float shAtan_asm(float);

float shSway1f(float, float);

float shSway1f_asm(float, float);

void shMulMatrix(float (* m0)[4], float (* m1)[4], float (* m2)[4]);

#endif // SH_VU0_H
