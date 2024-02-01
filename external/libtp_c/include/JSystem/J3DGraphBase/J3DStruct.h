#ifndef J3DSTRUCT_H
#define J3DSTRUCT_H

#include "../../dolphin/gx/GXTexture.h"
#include "../../dolphin/mtx/vec.h"

class J3DLightInfo {
public:
    /* 0x00 */ Vec mLightPosition;
    /* 0x0C */ Vec mLightDirection;
    /* 0x18 */ _GXColor mColor;
    /* 0x1C */ f32 mA0;
    /* 0x20 */ f32 mA1;
    /* 0x24 */ f32 mA2;
    /* 0x28 */ f32 mK0;
    /* 0x2C */ f32 mK1;
    /* 0x30 */ f32 mK2;
};  // Size = 0x34

class J3DLightObj {
public:
    /* 0x00 */ J3DLightInfo mInfo;
    /* 0x34 */ u8 field_0x34[64];
};  // Size = 0x74

#endif /* J3DSTRUCT_H */
