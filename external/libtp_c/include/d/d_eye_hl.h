#ifndef D_D_EYE_HL_H
#define D_D_EYE_HL_H

#include "../JSystem/JUtility/JUTTexture.h"

class dEyeHL_c;

class dEyeHL_mng_c {
public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ ResTIMG* field_0x04;
    /* 0x08 */ u16 field_0x08;
    /* 0x0A */ u8 field_0x0a[2];
    /* 0x0C */ dEyeHL_mng_c* field_0x0c;
    /* 0x10 */ dEyeHL_mng_c* field_0x10;
};

class dEyeHL_c : public dEyeHL_mng_c {
public:
};

#endif /* D_D_EYE_HL_H */
