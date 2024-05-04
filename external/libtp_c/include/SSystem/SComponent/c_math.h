#ifndef C_MATH_H
#define C_MATH_H

#include "../../dolphin/types.h"
#include "libtp_c/include/addrs.h"
#include "libtp_c/include/defines.h"
#include "libtp_c/include/JSystem/JMATrigonometric.h"

struct RNG {
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r02;
    s32 r12;
    s32 r22;
};

#define tp_rng (*(RNG*)(tp_rng_addr))

inline f32 cM_ssin(s16 x) {
    return JMASSin(x);
}

inline f32 cM_scos(s16 x) {
    return JMASCos(x);
}

#endif /* C_MATH_H */
