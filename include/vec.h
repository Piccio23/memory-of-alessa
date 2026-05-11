#ifndef SILENT_VEC_H
#define SILENT_VEC_H

/**
 * miscellaneous vector functions. all of the vector functions in common.h may
 * eventually be moved here
 */

static inline float vec_normalize(float* out, float* in) {
    asm("lqc2 vf4, 0(%0)\n\
        vmul.xyz vf5, vf4, vf4\n\
        vaddy.x vf5, vf5, vf5y\n\
        vaddz.x vf5, vf5, vf5z\n\
        vrsqrt Q, vf0w, vf5x\n\
        vwaitq\n\
        vmulq.xyz vf4, vf4, Q\n\
        sqc2 vf4, 0(%1)"
    : "=r"(out), "+r"(in));
}

static inline float vec_cross_product(float* v, float* w, float* out) {
    asm("lqc2 vf5, 0(%0)\n\
        lqc2 vf6, 0(%1)\n\
        vsub.w vf4, vf0, vf0\n\
        vopmula.xyz ACC, vf5, vf6\n\
        vopmsub.xyz vf4, vf6, vf5\n\
        sqc2 vf4, 0(%2)"
    : "+r"(v), "+r"(w), "=r"(out));
}

static inline void vec_copy_reverse(void* src, void* dst) {
    asm ("\
         lq t7, 0(%1)\n\
         sq t7, 0(%0)"
    : "+r"(dst), "+r"(src) :: "t7");
}

static inline void vec_copy_vu0(void* dst, void* src) {
    asm ("\
         lqc2 vf4, 0(%1)\n\
         vmove.w vf4, vf0\n\
         sqc2 vf4, 0(%0)"
    : "+r"(dst), "+r"(src));
}

static inline float vec3_length(void* v) {
    float d;
    asm("lwc1    %1,0(%0)\n\
        lwc1     f8,4(%0)\n\
        lwc1     f9,8(%0)\n\
        mula.s   %1,%1;\
        madda.s  f8,f8\n\
        madd.s   %1,f9,f9\n\
        sqrt.s   %1, %1"
    : "+r"(v), "+f"(d) :: "f8", "f9");
    return d;
}

static inline float float_abs(float x) {
    asm("abs.s %0, %0" : "+f"(x)); return x;
}

inline void vec_sub_reverse(void* y, void* x, void* out) {
    asm ("\
        lqc2 vf4, 0(%0)\n\
        lqc2 vf5, 0(%1)\n\
        vsub.xyzw vf4, vf4, vf5\n\
        sqc2 vf4, 0(%2)"
    : "+r"(x), "+r"(y), "+r"(out));
}

#endif // SILENT_VEC_H
