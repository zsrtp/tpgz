#ifndef C_BG_S_POLY_INFO_H
#define C_BG_S_POLY_INFO_H

#include "../../dolphin/types.h"

class cBgS_PolyInfo {
public:
    /* 0x00 */ u16 mPolyIndex;
    /* 0x02 */ u16 unk_0x02;
    /* 0x04 */ void* unk_0x04;
    /* 0x08 */ u32 unk_0x08;
    /* 0x0C */ void* vtable;
};

#endif /* C_BG_S_POLY_INFO_H */
