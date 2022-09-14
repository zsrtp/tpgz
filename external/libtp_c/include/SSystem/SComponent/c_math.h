#ifndef C_MATH_H
#define C_MATH_H

#include <stdint.h>
#include "addrs.h"

struct RNG {
    int32_t r0;
    int32_t r1;
    int32_t r2;
    int32_t r02;
    int32_t r12;
    int32_t r22;
};

#define tp_rng (*(RNG*)(tp_rng_addr))

#endif /* C_MATH_H */
