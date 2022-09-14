#ifndef D_CC_D_CC_D_H
#define D_CC_D_CC_D_H

#include "../../SSystem/SComponent/c_cc_d.h"

struct dCcD_SrcTri {};

struct dCcD_SrcSph {};

struct dCcD_SrcGObjTg {};

struct dCcD_SrcGObjInf {};

struct dCcD_SrcGObjAt {};

struct dCcD_SrcGAtTgCoCommonBase {};

struct dCcD_SrcCyl {};

struct dCcD_SrcCps {};

class dCcD_GStts : cCcD_GStts {
public:
    /* 0x04 */ uint8_t mAt;
    /* 0x05 */ uint8_t mTg;
    /* 0x06 */ uint8_t mRoomId;
    /* 0x08 */ uint16_t field_0x08;
    /* 0x0C */ int mAtApid;
    /* 0x10 */ int mAtOldApid;
    /* 0x14 */ int mTgApid;
    /* 0x18 */ int mTgOldApid;
    /* 0x1C */ int field_0x1C;
};  // Size = 0x20

class dCcD_Stts : cCcD_Stts {
public:
    /* 0x1C */ dCcD_GStts mGStts;
};  // Size = 0x3C

class dCcD_GAtTgCoCommonBase {
public:
    /* 0x00 */ void* mBase;  // type dCcD_SrcGAtTgCoCommonBase*
    /* 0x04 */ uint32_t mRPrm;
    /* 0x08 */ uint32_t field_0x08;
    /* 0x0C */ uint32_t field_0x0C;
    /* 0x10 */ fopAc_ac_c* mAc;
    /* 0x14 */ int8_t mEffCounter;
    /* 0x15 */ uint8_t field_0x15[3];
    /* 0x18 */ void* vtable;
};  // Size = 0x1C

class dCcD_GObjAt : dCcD_GAtTgCoCommonBase {
public:
    /* 0x1C */ uint8_t mSe;
    /* 0x1D */ uint8_t mMtrl;
    /* 0x1E */ uint8_t mHitMark;
    /* 0x1F */ uint8_t mSpl;
    /* 0x20 */ cXyz mHitPos;
    /* 0x2C */ cXyz mVec;
    /* 0x38 */ cXyz mRVec;
};  // Size = 0x44
class dCcD_GObjTg : dCcD_GAtTgCoCommonBase {
public:
    /* 0x1C */ uint8_t mSe;
    /* 0x1D */ uint8_t mMtrl;
    /* 0x1E */ uint8_t mHitMark;
    /* 0x1F */ uint8_t mSpl;
    /* 0x20 */ cXyz mVec;
    /* 0x2C */ cXyz mRVec;
    /* 0x38 */ cXyz mHitPos;
    /* 0x44 */ int16_t* mShieldFrontRangeYAngle;
    /* 0x48 */ int16_t mShieldRange;
};  // Size = 0x4A ?
class dCcD_GObjCo : dCcD_GAtTgCoCommonBase {
public:
private:
};  // Size = 0x1C ?

class dCcD_GObjInf : cCcD_GObjInf {
public:
    /* 0x058 */ dCcD_GObjAt mGObjAt;
    /* 0x09C */ dCcD_GObjTg mGObjTg;
    /* 0x0E8 */ dCcD_GObjCo mGObjCo;
};  // Size = 0x104

class dCcD_Cyl : dCcD_GObjInf {
public:
    /* 0x104 */ cCcD_CylAttr mCylAttr;
};  // Size = 0x13C

class dCcD_Sph : dCcD_GObjInf {
public:
    /* 0x104 */ cCcD_SphAttr mSphAttr;
};  // Size = 0x138

class dCcD_Cps : dCcD_GObjInf {
public:
    /* 0x104 */ cCcD_CpsAttr mCpsAttr;
};  // Size = 0x144

class dCcD_Tri {
public:
};

#endif /* D_CC_D_CC_D_H */
