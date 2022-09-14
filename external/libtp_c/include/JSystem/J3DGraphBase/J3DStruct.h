#ifndef J3DSTRUCT_H
#define J3DSTRUCT_H

#include "../../dolphin/gx/GXTexture.h"
#include "../../dolphin/mtx/vec.h"

class J3DLightInfo {
public:
    /* 0x00 */ Vec mLightPosition;
    /* 0x0C */ Vec mLightDirection;
    /* 0x18 */ _GXColor mColor;
    /* 0x1C */ float mA0;
    /* 0x20 */ float mA1;
    /* 0x24 */ float mA2;
    /* 0x28 */ float mK0;
    /* 0x2C */ float mK1;
    /* 0x30 */ float mK2;
};  // Size = 0x34

class J3DLightObj {
public:
    /* 0x00 */ J3DLightInfo mInfo;
    /* 0x34 */ uint8_t field_0x34[64];
};  // Size = 0x74

#endif /* J3DSTRUCT_H */
