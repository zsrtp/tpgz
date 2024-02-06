#ifndef D_CC_D_CC_MASS_S_H
#define D_CC_D_CC_MASS_S_H

#include "../../SSystem/SComponent/c_cc_d.h"

typedef void (*dCcMassS_ObjCallback)(fopAc_ac_c*, cXyz*, u32);

class dCcMassS_Obj {
public:
    /* 0x00 */ cCcD_Obj* mpObj;
    /* 0x04 */ u8 mPriority;
    /* 0x08 */ dCcMassS_ObjCallback mpCallback;
    /* 0x0C */ cCcD_DivideInfo mDivideInfo;
    /* 0x1C */ void* vtable;
};  // Size = 0x20

static_assert(sizeof(dCcMassS_Obj) == 0x20);

class dCcMassS_Mng {
public:
    /* 0x0000 */ cCcD_DivideArea mDivideArea;
    /* 0x0040 */ s32 mMassObjCount;
    /* 0x0044 */ dCcMassS_Obj mMassObjs[10];
    /* 0x0184 */ s32 mMassAreaCount;
    /* 0x0188 */ dCcMassS_Obj mMassAreas[2];
    /* 0x01C8 */ cCcD_CylAttr mCylAttr;
    /* 0x0200 */ u8 field_0x200;
    /* 0x0200 */ u8 field_0x201;
    /* 0x0202 */ u8 field_0x202;
    /* 0x0203 */ u8 mResultCam;
    /* 0x0204 */ Vec mCamTopPos;
    /* 0x0210 */ f32 mCamTopDist;
    /* 0x0214 */ Vec mCamBottomPos;
    /* 0x0220 */ f32 mCamBottomDist;
    /* 0x0224 */ cCcD_CpsAttr mCpsAttr;
    /* 0x0264 */ cCcD_DivideInfo mDivideInfo;
    /* 0x0274 */ void* vtable;
};

static_assert(sizeof(dCcMassS_Mng) == 0x278);

#endif /* D_CC_D_CC_MASS_S_H */
