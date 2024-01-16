#ifndef C_CC_D_H
#define C_CC_D_H

#include "c_m3d_g_aab.h"
#include "c_m3d_g_cps.h"
#include "c_m3d_g_cyl.h"
#include "c_m3d_g_sph.h"
#include "c_m3d_g_tri.h"
#include "../../f_op/f_op_actor.h"

class cCcD_ShapeAttr {
public:
    /* 0x00 */ cM3dGAab mAab;
    /* 0x1C */ void* vtable;
};

class cCcD_CpsAttr {
public:
    /* 0x00 */ cCcD_ShapeAttr cccd_shapeattr;
    /* 0x20 */ cM3dGCps mCps;
};

class cCcD_SphAttr {
public:
    /* 0x00 */ cCcD_ShapeAttr cccd_shapeattr;
    /* 0x20 */ cM3dGSph mSph;
};  // Size = 0x30

class cCcD_CylAttr {
public:
    /* 0x00 */ cCcD_ShapeAttr cccd_shapeattr;
    /* 0x20 */ cM3dGCyl mCyl;
};  // Size = 0x34

class cCcD_TriAttr {};

class cCcD_DivideInfo {
public:
    /* 0x00 */ u32 field_0x0;
    /* 0x04 */ u32 field_0x4;
    /* 0x08 */ u32 field_0x8;
    /* 0x0C */ void* vtable;
};

class cCcD_DivideArea : public cM3dGAab {
public:
    /* 0x1C */ bool mXDiffIsZero;
    /* 0x20 */ f32 mScaledXDiff;
    /* 0x24 */ f32 mInvScaledXDiff;
    /* 0x28 */ bool mYDiffIsZero;
    /* 0x2C */ f32 mScaledYDiff;
    /* 0x30 */ f32 mInvScaledYDiff;
    /* 0x34 */ bool mZDiffIsZero;
    /* 0x38 */ f32 mScaledZDiff;
    /* 0x3C */ f32 mInvScaledZDiff;
};  // Size = 0x40

static_assert(sizeof(cCcD_DivideArea) == 0x40);

struct cCcD_SrcObjTg {};

struct cCcD_SrcObjHitInf {};

struct cCcD_SrcObjAt {};

struct cCcD_SrcObj {};

class cCcD_GStts {
public:
    /* 0x00 */ void* vtable;
};  // Size = 0x4

class cCcD_Stts {
public:
    /* 0x00 */ cXyz field_0x00;
    /* 0x0C */ fopAc_ac_c* mActor;
    /* 0x10 */ int mApid;
    /* 0x14 */ u8 mWeight;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 mTg;
    /* 0x18 */ void* vtable;
};  // Size = 0x1C

class cCcD_ObjCommonBase {
public:
    /* 0x00 */ int mSPrm;
    /* 0x04 */ int mRPrm;
    /* 0x08 */ void* mHitObj;  // cCcD_Obj* type
    /* 0x0C */ void* vtable;
};

class cCcD_Obj;
#pragma pack(push, 1)
class cCcD_ObjAt : cCcD_ObjCommonBase {
public:
    /* 0x10 */ int mType;
    /* 0x14 */ u8 mAtp;
};
#pragma pack(pop)

class cCcD_ObjTg : cCcD_ObjCommonBase {
public:
    /* 0x10 */ int mType;
};

class cCcD_ObjCo : cCcD_ObjCommonBase {
public:
};

class cCcD_ObjHitInf {
public:
    /* 0x000 */ cCcD_ObjAt mObjAt;
    /* 0x015 */ u8 field_0x15[3];  // padding?
    /* 0x018 */ cCcD_ObjTg mObjTg;
    /* 0x02C */ cCcD_ObjCo mObjCo;
    /* 0x03C */ void* vtable;
};  // Size = 0x40

class cCcD_Obj : cCcD_ObjHitInf {
public:
    /* 0x040 */ int field_0x40;
    /* 0x044 */ cCcD_Stts* mStts;
    /* 0x048 */ cCcD_DivideInfo mDivideInfo;
};  // Size = 0x58

class cCcD_GObjInf : cCcD_Obj {
public:
};

#endif /* C_CC_D_H */
