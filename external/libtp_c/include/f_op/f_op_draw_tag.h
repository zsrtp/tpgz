#ifndef F_F_OP_DRAW_TAG
#define F_F_OP_DRAW_TAG

#include <stdint.h>
#include "../dolphin/mtx/vec.h"
#include "../addrs.h"

// add lists$2216 later
struct MatrixPtr {
    uint8_t _p0[0x9C];   // 0x0000
    Vec target;          // 0x009C
    Vec pos;             // 0x00A8
    uint8_t _p1[0x134];  // 0x00B4
    uint16_t camera6;    // 0x01E8 // Seems related to the pitch
    uint8_t _p2[0x25C];  // 0x01EC
    float camera7;       // 0x0448
};

struct MatrixInfo {
    MatrixPtr* matrix_info;
};

extern MatrixInfo matrixInfo;

#endif