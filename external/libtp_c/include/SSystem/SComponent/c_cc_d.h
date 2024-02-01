#ifndef C_CC_D_H
#define C_CC_D_H

#include "c_m3d_g_aab.h"
#include "c_m3d_g_cps.h"
#include "c_m3d_g_cyl.h"
#include "c_m3d_g_sph.h"
#include "c_m3d_g_tri.h"
#include "../../f_op/f_op_actor.h"

enum CcG_Tg_HitMark {
    CcG_Tg_UNK_MARK_6 = 6,
    CcG_Tg_UNK_MARK_8 = 8,
};

enum cCcD_ObjAtType {
    /* 0x00000002 */ AT_TYPE_NORMAL_SWORD = (1 << 1),  // wooden or ordon
    /* 0x00000004 */ AT_TYPE_HORSE = (1 << 2),
    /* 0x00000008 */ AT_TYPE_THROW_OBJ = (1 << 3),
    /* 0x00000010 */ AT_TYPE_SHIELD_ATTACK = (1 << 4),
    /* 0x00000020 */ AT_TYPE_BOMB = (1 << 5),
    /* 0x00000040 */ AT_TYPE_40 = (1 << 6),
    /* 0x00000080 */ AT_TYPE_SLINGSHOT = (1 << 7),
    /* 0x00000200 */ AT_TYPE_LANTERN_SWING = (1 << 9),
    /* 0x00000400 */ AT_TYPE_CSTATUE_SWING = (1 << 10),
    /* 0x00000800 */ AT_TYPE_800 = (1 << 11),
    /* 0x00001000 */ AT_TYPE_1000 = (1 << 12),
    /* 0x00002000 */ AT_TYPE_ARROW = (1 << 13),
    /* 0x00004000 */ AT_TYPE_HOOKSHOT = (1 << 14),
    /* 0x00010000 */ AT_TYPE_BOOMERANG = (1 << 16),
    /* 0x00040000 */ AT_TYPE_40000 = (1 << 18),
    /* 0x00080000 */ AT_TYPE_SPINNER = (1 << 19),
    /* 0x00100000 */ AT_TYPE_CSTATUE_BOSS_SWING = (1 << 20),
    /* 0x00200000 */ AT_TYPE_HEAVY_BOOTS = (1 << 21),
    /* 0x00400000 */ AT_TYPE_IRON_BALL = (1 << 22),
    /* 0x00800000 */ AT_TYPE_COPY_ROD = (1 << 23),
    /* 0x01000000 */ AT_TYPE_1000000 = (1 << 24),
    /* 0x04000000 */ AT_TYPE_MASTER_SWORD = (1 << 26),
    /* 0x08000000 */ AT_TYPE_MIDNA_LOCK = (1 << 27),
    /* 0x10000000 */ AT_TYPE_10000000 = (1 << 28),
    /* 0x40000000 */ AT_TYPE_WOLF_CUT_TURN = (1 << 30),
    /* 0x80000000 */ AT_TYPE_WOLF_ATTACK = (1 << 31),
    /* 0xD8000000 */ AT_TYPE_UNK = 0xD8000000
};

class cCcD_ShapeAttr {
public:
    /* 0x00 */ cM3dGAab mAab;
    /* 0x1C */ void* vtable;
};

class cCcD_CpsAttr : public cCcD_ShapeAttr, public cM3dGCps {
public:
};

class cCcD_SphAttr : public cCcD_ShapeAttr, public cM3dGSph {
public:
};  // Size = 0x30

class cCcD_CylAttr : public cCcD_ShapeAttr, public cM3dGCyl {
public:
};  // Size = 0x34

class cCcD_TriAttr {};

class cCcD_DivideInfo {
public:
    /* 0x00 */ u32 mXDivInfo;
    /* 0x04 */ u32 mYDivInfo;
    /* 0x08 */ u32 mZDivInfo;
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
    /* 0x00 */ cXyz mXyz;
    /* 0x0C */ fopAc_ac_c* mActor;
    /* 0x10 */ int mApid;
    /* 0x14 */ u8 mWeight;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 mTg;
    /* 0x18 */ void* vtable;

    u8 GetWeightUc() const { return mWeight; }
    void SetWeight(u8 weight) { mWeight = weight; }
    fopAc_ac_c* GetAc() { return mActor; }
    fopAc_ac_c* GetActor() const { return mActor; }
    void SetActor(void* ac) { mActor = (fopAc_ac_c*)ac; }
    cXyz* GetCCMoveP() { return &mXyz; }
    unsigned int GetApid() const { return mApid; }
};  // Size = 0x1C

class cCcD_Obj;
class cCcD_ObjCommonBase {
public:
    /* 0x00 */ u32 mSPrm;
    /* 0x04 */ u32 mRPrm;
    /* 0x08 */ cCcD_Obj* mHitObj;
    /* 0x0C */ void* vtable;

    void SetSPrm(u32 sprm) { mSPrm = sprm; }
    s32 getSPrm() const { return mSPrm; }
    void setRPrm(s32 rprm) { mRPrm = rprm; }
    s32 getRPrm() const { return mRPrm; }
    cCcD_Obj* GetHitObj() { return mHitObj; }
    u32 MskSPrm(u32 mask) const { return mSPrm & mask; }
    u32 MskRPrm(u32 mask) { return mRPrm & mask; }
    void OnSPrmBit(u32 flag) { mSPrm |= flag; }
    void OffSPrmBit(u32 flag) { mSPrm &= ~flag; }
};

static_assert(sizeof(cCcD_ObjCommonBase) == 0x10);

class cCcD_ObjAt : public cCcD_ObjCommonBase {
public:
    int GetType() const { return mType; }
    u32 GetGrp() const { return MskSPrm(0x1E); }
    bool ChkSet() const { return MskSPrm(1); }
    u8 GetAtp() const { return mAtp; }
    u32 MskType(u32 msk) const { return mType & msk; }
    void SetType(u32 type) { mType = type; }
    void SetAtp(int atp) { mAtp = atp; }
    void ClrSet() { OffSPrmBit(1); }
    u32 ChkHit() { return MskRPrm(1); }

    void ClrHit() {
        mRPrm &= ~1;
        mHitObj = NULL;
    }

    /* 0x10 */ int mType;
    /* 0x14 */ u8 mAtp;
};

static_assert(sizeof(cCcD_ObjAt) == 0x18);

class cCcD_ObjTg : public cCcD_ObjCommonBase {
public:
    int GetType() const { return mType; }
    void SetType(u32 type) { mType = type; }
    u32 GetGrp() const { return MskSPrm(0x1E); }
    bool ChkSet() const { return MskSPrm(1); }
    void ClrSet() { OffSPrmBit(1); }
    u32 ChkHit() { return MskRPrm(1); }

    void ClrHit() {
        mRPrm &= ~1;
        mHitObj = NULL;
    }

    /* 0x10 */ int mType;
};

static_assert(sizeof(cCcD_ObjTg) == 0x14);

class cCcD_ObjCo : public cCcD_ObjCommonBase {
public:
    u32 GetGrp() const { return MskSPrm(0x1E); }
    bool ChkSet() const { return MskSPrm(1); }
    u32 GetVsGrp() const { return MskSPrm(0x70); }
    u32 GetIGrp() const { return MskSPrm(0xE); }
    u32 ChkNoCrr() const { return MskSPrm(0x100); }
    u32 ChkSph3DCrr() const { return MskSPrm(0x80); }
    void ClrSet() { OffSPrmBit(1); }
    u32 ChkHit() { return MskRPrm(1); }

    void ClrHit() {
        mRPrm &= ~1;
        mHitObj = NULL;
    }
};

static_assert(sizeof(cCcD_ObjCo) == 0x10);

class cCcD_ObjHitInf {
public:
    /* 0x000 */ cCcD_ObjAt mObjAt;
    /* 0x018 */ cCcD_ObjTg mObjTg;
    /* 0x02C */ cCcD_ObjCo mObjCo;
    /* 0x03C */ void* vtable;

    cCcD_ObjAt& GetObjAt() { return mObjAt; }
    cCcD_ObjTg& GetObjTg() { return mObjTg; }
    cCcD_ObjCo& GetObjCo() { return mObjCo; }
    u32 GetTgGrp() const { return mObjTg.GetGrp(); }
    u32 GetAtGrp() const { return mObjAt.GetGrp(); }
    u32 GetCoGrp() const { return mObjCo.GetGrp(); }
    int GetTgType() const { return mObjTg.GetType(); }
    u32 GetAtType() const { return mObjAt.GetType(); }
    bool ChkTgSet() const { return mObjTg.ChkSet(); }
    bool ChkAtSet() const { return mObjAt.ChkSet(); }
    bool ChkCoSet() const { return mObjCo.ChkSet(); }
    u32 ChkCoSameActorHit() const { return mObjCo.MskSPrm(0x400); }
    u32 GetCoVsGrp() const { return mObjCo.GetVsGrp(); }
    u32 GetCoIGrp() const { return mObjCo.GetIGrp(); }
    u8 GetAtAtp() const { return mObjAt.GetAtp(); }
    u32 ChkAtNoTgHitInfSet() const { return mObjAt.MskSPrm(0x20); }
    u32 ChkTgNoAtHitInfSet() const { return mObjTg.MskSPrm(0x20); }
    u32 ChkCoNoCoHitInfSet() const { return mObjCo.MskSPrm(0x200); }
    bool ChkTgNoSlingHitInfSet() const { return mObjTg.MskSPrm(0x40); }
    bool ChkAtType(u32 type) const { return mObjAt.MskType(type); }
    u32 ChkCoNoCrr() const { return mObjCo.ChkNoCrr(); }
    u32 ChkCoSph3DCrr() const { return mObjCo.ChkSph3DCrr(); }
    void OnAtSPrmBit(u32 flag) { mObjAt.OnSPrmBit(flag); }
    void OffAtSPrmBit(u32 flag) { mObjAt.OffSPrmBit(flag); }
    void OffTgSPrmBit(u32 flag) { mObjTg.OffSPrmBit(flag); }
    void OffCoSPrmBit(u32 flag) { mObjCo.OffSPrmBit(flag); }
    void SetAtType(u32 type) { mObjAt.SetType(type); }
    void OnAtSetBit() { mObjAt.OnSPrmBit(1); }
    u32 MskTgSPrm(u32 mask) const { return mObjTg.MskSPrm(mask); }
    void SetAtAtp(int atp) { mObjAt.SetAtp(atp); }
    void OffCoSetBit() { mObjCo.ClrSet(); }
    void SetTgType(u32 type) { mObjTg.SetType(type); }
    void OnTgSPrmBit(u32 flag) { mObjTg.OnSPrmBit(flag); }
    void OffAtSetBit() { mObjAt.ClrSet(); }
    void OnTgSetBit() { mObjTg.OnSPrmBit(1); }
    void OffTgSetBit() { mObjTg.ClrSet(); }
    void OnCoSetBit() { mObjCo.OnSPrmBit(1); }
    void OffAtVsPlayerBit() { mObjAt.OffSPrmBit(0xC); }
    void OnAtVsPlayerBit() { mObjAt.OnSPrmBit(0xC); }
    void OnCoSPrmBit(u32 flag) { mObjCo.OnSPrmBit(flag); }
    void SetAtSprm(u32 prm) { mObjAt.SetSPrm(prm); }
    void SetTgSPrm(u32 prm) { mObjTg.SetSPrm(prm); }
    void SetCoSPrm(u32 prm) { mObjCo.SetSPrm(prm); }
    void ClrAtHit() { mObjAt.ClrHit(); }
    void ClrTgHit() { mObjTg.ClrHit(); }
    void ClrCoHit() { mObjCo.ClrHit(); }
    u32 ChkAtHit() { return mObjAt.ChkHit(); }
    u32 ChkTgHit() { return mObjTg.ChkHit(); }
    u32 ChkCoHit() { return mObjCo.ChkHit(); }
    cCcD_Obj* GetAtHitObj() { return mObjAt.GetHitObj(); }
    cCcD_Obj* GetTgHitObj() { return mObjTg.GetHitObj(); }
    cCcD_Obj* GetCoHitObj() { return mObjCo.GetHitObj(); }
};  // Size = 0x40

static_assert(sizeof(cCcD_ObjHitInf) == 0x40);

class cCcD_Obj : public cCcD_ObjHitInf {
public:
    cCcD_Stts* GetStts() { return mStts; }
    void SetStts(cCcD_Stts* stts) { mStts = stts; }
    cCcD_DivideInfo& GetDivideInfo() { return mDivideInfo; }
    cCcD_DivideInfo* GetPDivideInfo() { return &mDivideInfo; }
    int ChkBsRevHit() const { return mFlags & 2; }

    /* 0x040 */ int mFlags;
    /* 0x044 */ cCcD_Stts* mStts;
    /* 0x048 */ cCcD_DivideInfo mDivideInfo;
};  // Size = 0x58

static_assert(sizeof(cCcD_Obj) == 0x58);

class cCcD_GObjInf : public cCcD_Obj {
public:
    void ClrAtHit() { mObjAt.ClrHit(); }
    void ClrTgHit() { mObjTg.ClrHit(); }
    void ClrCoHit() { mObjCo.ClrHit(); }
};

static_assert(sizeof(cCcD_GObjInf) == 0x58);

#endif /* C_CC_D_H */
