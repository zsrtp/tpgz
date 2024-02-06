#ifndef C_MATH_H
#define C_MATH_H

#include "../../dolphin/types.h"
#include "addrs.h"

struct RNG {
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r02;
    s32 r12;
    s32 r22;
};

#define tp_rng (*(RNG*)(tp_rng_addr))

#endif /* C_MATH_H */
