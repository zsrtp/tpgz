#ifndef C_BG_S_POLY_INFO_H
#define C_BG_S_POLY_INFO_H

#include <stdint.h>

class cBgS_PolyInfo {
public:
    /* 0x00 */ uint16_t mPolyIndex;
    /* 0x02 */ uint16_t unk_0x02;
    /* 0x04 */ void* unk_0x04;
    /* 0x08 */ uint32_t unk_0x08;
    /* 0x0C */ void* vtable;
};

#endif /* C_BG_S_POLY_INFO_H */
