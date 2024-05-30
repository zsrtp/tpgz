#ifndef D_CC_D_CC_D_H
#define D_CC_D_CC_D_H

#include "../../SSystem/SComponent/c_cc_d.h"
#include "../../defines.h"

LIBTP_DEFINE_FUNC(ClrTgHit__12dCcD_GObjInfFv, dCcD_GObjInf__ClrTgHit_void_,
                  void, dCcD_GObjInf__ClrTgHit, (void* addr))

LIBTP_DEFINE_FUNC(ResetTgHit__12dCcD_GObjInfFv, dCcD_GObjInf__ResetTgHit_void_,
                  void, dCcD_GObjInf__ResetTgHit, (void* addr))

enum dCcD_hitSe {
    /* 0  */ dCcD_SE_NONE,
    /* 1  */ dCcD_SE_SWORD,
    /* 2  */ dCcD_SE_SHIELD_ATTACK,
    /* 3  */ dCcD_SE_WOLF_KICK,
    /* 4  */ dCcD_SE_WOLF_BITE,
    /* 5  */ dCcD_SE_WOOD,
    /* 6  */ dCcD_SE_HAMMER,
    /* 7  */ dCcD_SE_ARROW_STICK,
    /* 8  */ dCcD_SE_HOOKSHOT_STICK,
    /* 9  */ dCcD_SE_METAL,
    /* 10 */ dCcD_SE_STONE,
    /* 11 */ dCcD_SE_HARD_BODY,
    /* 12 */ dCcD_SE_SOFT_BODY,
    /* 13 */ dCcD_SE_13,
    /* 14 */ dCcD_SE_SWORD_STAB,
    /* 15 */ dCcD_SE_15,
    /* 16 */ dCcD_SE_SWORD_RUN,
    /* 17 */ dCcD_SE_17,
    /* 18 */ dCcD_SE_THROW_OBJ,
    /* 19 */ dCcD_SE_SPINNER,
    /* 20 */ dCcD_SE_COPYROD,
    /* 21 */ dCcD_SE_STATUE_HAMMER,
    /* 22 */ dCcD_SE_PACHINKO,
    /* 23 */ dCcD_SE_23,
};

enum dCcG_At_Spl {
    /* 0x0 */ dCcG_At_Spl_UNK_0,
    /* 0x1 */ dCcG_At_Spl_UNK_1,
};

enum dCcG_Tg_Spl {
    /* 0x0 */ dCcG_Tg_Spl_UNK_0,
    /* 0x1 */ dCcG_Tg_Spl_UNK_1,
};

struct dCcD_SrcTri {};

struct dCcD_SrcSph {};

struct dCcD_SrcGObjTg {};

struct dCcD_SrcGObjInf {};

struct dCcD_SrcGObjAt {};

struct dCcD_SrcGAtTgCoCommonBase {};

struct dCcD_SrcCyl {};

struct dCcD_SrcCps {};

class dCcD_GStts : public cCcD_GStts {
public:
    void ClrAt() { mAt = 0; }
    void ClrTg() { mTg = 0; }
    void SetAtApid(unsigned int id) { mAtApid = id; }
    void SetTgApid(unsigned int id) { mTgApid = id; }
    u8 GetRoomId() { return mRoomId; }
    void SetRoomId(int id) { mRoomId = id; }
    unsigned int GetAtOldApid() { return mAtOldApid; }
    unsigned int GetTgOldApid() { return mTgOldApid; }
    bool ChkNoActor() { return field_0x1C & 1;}
    bool ChkNoneActorPerfTblId() { return field_0x08 == 0xFFFF; }
    dCcG_At_Spl GetAtSpl() { return (dCcG_At_Spl)mAt; }
    void SetAtSpl(dCcG_At_Spl spl) { mAt = spl; }
    dCcG_Tg_Spl GetTgSpl() { return (dCcG_Tg_Spl)mTg; }
    void SetTgSpl(dCcG_Tg_Spl spl) { mTg = spl; }
    void OnNoActor() { field_0x1C |= 1; }

    /* 0x04 */ u8 mAt;
    /* 0x05 */ u8 mTg;
    /* 0x06 */ u8 mRoomId;
    /* 0x08 */ u16 field_0x08;
    /* 0x0C */ int mAtApid;
    /* 0x10 */ int mAtOldApid;
    /* 0x14 */ int mTgApid;
    /* 0x18 */ int mTgOldApid;
    /* 0x1C */ int field_0x1C;
};  // Size = 0x20

class dCcD_Stts : public cCcD_Stts, public dCcD_GStts {
public:
};  // Size = 0x3C

class dCcD_GObjInf;
typedef void (*dCcD_HitCallback)(fopAc_ac_c* i_actorA, dCcD_GObjInf* i_objInfA, fopAc_ac_c* i_actorB, dCcD_GObjInf* i_objInfB);

class dCcD_GAtTgCoCommonBase {
public:
    /* 0x00 */ u32 mGFlag;
    /* 0x04 */ u32 mRPrm;
    /* 0x08 */ dCcD_HitCallback mHitCallback;
    /* 0x0C */ u32 mApid;
    /* 0x10 */ fopAc_ac_c* mAc;
    /* 0x14 */ s8 mEffCounter;
    /* 0x15 */ u8 field_0x15[3];
    /* 0x18 */ void* vtable;

    void ClrEffCounter() { mEffCounter = 0; }
    u32 GetGFlag() const { return mGFlag; }
    u32 GetRPrm() const { return mRPrm; }
    u32 MskSPrm(u32 mask) const { return mGFlag & mask; }
    u32 MskRPrm(u32 mask) const { return mRPrm & mask; }
    bool ChkSPrm(u32 mask) const { return MskSPrm(mask); }
    void OnSPrm(u32 flag) { mGFlag |= flag; }
    void OnRPrm(u32 flag) { mRPrm |= flag; }
    void OffSPrm(u32 flag) { mGFlag &= ~flag; }
    void OffRPrm(u32 flag) { mRPrm &= ~flag; }
    bool ChkRPrm(u32 flag) const { return MskRPrm(flag); }
    void SetHitCallback(dCcD_HitCallback callback) { mHitCallback = callback; }
    dCcD_HitCallback GetHitCallback() { return mHitCallback; }
};  // Size = 0x1C

static_assert(sizeof(dCcD_GAtTgCoCommonBase) == 0x1C);

class dCcD_GObjAt : public dCcD_GAtTgCoCommonBase {
public:
    void SetVec(cXyz& vec) { mVec = vec; }
    cXyz& GetVec() { return mVec; }
    cXyz* GetVecP() { return &mVec; }
    void SetHitMark(u8 mark) { mHitMark = mark; }
    void SetSe(u8 se) { mSe = se; }
    void SetMtrl(u8 mtrl) { mMtrl = mtrl; }
    void SetAtSpl(dCcG_At_Spl spl) { mSpl = spl; }
    u8 GetSe() { return mSe; }
    u8 GetSpl() { return mSpl; }
    u8 GetMtrl() { return mMtrl; }
    u8 GetHitMark() { return mHitMark; }
    void SetRVec(cXyz& vec) { mRVec = vec; }
    void SetHitPos(cXyz& pos) { mHitPos = pos; }
    cXyz* GetHitPosP() { return &mHitPos; }

    /* 0x1C */ u8 mSe;
    /* 0x1D */ u8 mMtrl;
    /* 0x1E */ u8 mHitMark;
    /* 0x1F */ u8 mSpl;
    /* 0x20 */ cXyz mHitPos;
    /* 0x2C */ cXyz mVec;
    /* 0x38 */ cXyz mRVec;
};  // Size = 0x44

static_assert(sizeof(dCcD_GObjAt) == 0x44);

class dCcD_GObjTg : public dCcD_GAtTgCoCommonBase {
public:
    void SetSe(u8 se) { mSe = se; }
    void SetVec(cXyz& vec) { mVec = vec; }
    cXyz& GetVec() { return mVec; }
    void SetShieldFrontRangeYAngle(s16* angle) { mShieldFrontRangeYAngle = angle; }
    void SetMtrl(u8 mtrl) { mMtrl = mtrl; }
    u8 GetMtrl() { return mMtrl; }
    void SetHitMark(CcG_Tg_HitMark mark) { mHitMark = mark; }
    s16* GetShieldFrontRangeYAngle() { return mShieldFrontRangeYAngle; }
    s16 GetShieldRange() { return mShieldRange; }
    u8 GetSpl() { return mSpl; }
    u8 GetHitMark() { return mHitMark; }
    void SetRVec(cXyz& vec) { mRVec = vec; }
    cXyz* GetVecP() { return &mVec; }
    void SetHitPos(cXyz& pos) { mHitPos = pos; }

    /* 0x1C */ u8 mSe;
    /* 0x1D */ u8 mMtrl;
    /* 0x1E */ u8 mHitMark;
    /* 0x1F */ u8 mSpl;
    /* 0x20 */ cXyz mVec;
    /* 0x2C */ cXyz mRVec;
    /* 0x38 */ cXyz mHitPos;
    /* 0x44 */ s16* mShieldFrontRangeYAngle;
    /* 0x48 */ s16 mShieldRange;
};  // Size = 0x4A ?

static_assert(sizeof(dCcD_GObjTg) == 0x4C);

class dCcD_GObjCo : public dCcD_GAtTgCoCommonBase {
public:
};  // Size = 0x1C ?

static_assert(sizeof(dCcD_GObjCo) == 0x1C);

class dCcD_GObjInf : public cCcD_GObjInf {
public:
    void SetAtVec(cXyz& vec) { mGObjAt.SetVec(vec); }
    void SetTgVec(cXyz& vec) { mGObjTg.SetVec(vec); }
    bool ChkAtNoMass() const { return mGObjAt.ChkSPrm(8); }
    void OnAtNoHitMark() { mGObjAt.OnSPrm(2); }
    void OffAtNoHitMark() { mGObjAt.OffSPrm(2); }
    void OnTgNoHitMark() { mGObjTg.OnSPrm(4); }
    void OffTgNoHitMark() { mGObjTg.OffSPrm(4); }
    void OnAtNoConHit() { mGObjAt.OnSPrm(1); }
    void OffAtNoConHit() { mGObjAt.OffSPrm(1); }
    void OnTgNoConHit() { mGObjTg.OnSPrm(2); }
    void SetAtHitMark(u8 mark) { mGObjAt.SetHitMark(mark); }
    void SetAtSe(u8 se) { mGObjAt.SetSe(se); }
    void SetTgSe(u8 se) { mGObjTg.SetSe(se); }
    void SetAtMtrl(u8 mtrl) { mGObjAt.SetMtrl(mtrl); }
    void SetTgMtrl(u8 mtrl) { mGObjTg.SetMtrl(mtrl); }
    bool ChkAtShieldHit() { return mGObjAt.ChkRPrm(1); }
    cXyz* GetAtVecP() { return mGObjAt.GetVecP(); }
    cXyz* GetTgVecP() { return mGObjTg.GetVecP(); }
    void SetAtSpl(dCcG_At_Spl spl) { mGObjAt.SetAtSpl(spl); }
    void SetAtHitCallback(dCcD_HitCallback callback) { mGObjAt.SetHitCallback(callback); }
    void SetTgHitCallback(dCcD_HitCallback callback) { mGObjTg.SetHitCallback(callback); }
    void SetCoHitCallback(dCcD_HitCallback callback) { mGObjCo.SetHitCallback(callback); }
    u8 GetAtSe() { return mGObjAt.GetSe(); }
    dCcG_At_Spl GetAtSpl() { return (dCcG_At_Spl)mGObjAt.GetSpl(); }
    u8 GetAtMtrl() { return mGObjAt.GetMtrl(); }
    u8 GetTgMtrl() { return mGObjTg.GetMtrl(); }
    void SetTgShieldFrontRangeYAngle(s16* angle) { mGObjTg.SetShieldFrontRangeYAngle(angle); }
    void OffTgWolfSpNoDamage() { mGObjTg.OffSPrm(0x800); }
    void OnTgWolfSpNoDamage() { mGObjTg.OnSPrm(0x800); }
    void SetTgHitMark(CcG_Tg_HitMark mark) { mGObjTg.SetHitMark(mark); }
    void OnTgSpShield() { mGObjTg.OnSPrm(0x40); }
    void OffTgSpShield() { mGObjTg.OffSPrm(0x40); }
    void OnTgShield() { mGObjTg.OnSPrm(0x1); }
    void OffTgShield() { mGObjTg.OffSPrm(0x1); }
    void OnTgShieldFrontRange() { mGObjTg.OnSPrm(0x8); }
    void OffTgShieldFrontRange() { mGObjTg.OffSPrm(0x8); }
    void OnTgSmallShield() { mGObjTg.OnSPrm(0x10); }
    void OffTgSmallShield() { mGObjTg.OffSPrm(0x10); }
    bool ChkTgIronBallRebound() { return mGObjTg.ChkSPrm(0x100); }
    s16* GetTgShieldFrontRangeYAngle() { return mGObjTg.GetShieldFrontRangeYAngle(); }
    s16 GetTgShieldRange() { return mGObjTg.GetShieldRange(); }
    bool ChkTgShield() { return mGObjTg.ChkSPrm(1); }
    bool ChkTgSpShield() { return mGObjTg.ChkSPrm(0x40); }
    bool ChkTgSmallShield() { return mGObjTg.ChkSPrm(0x10); }
    bool ChkTgShieldFrontRange() { return mGObjTg.ChkSPrm(8); }
    bool ChkAtNoConHit() { return mGObjAt.ChkSPrm(1); }
    bool ChkAtStopNoConHit() { return mGObjAt.ChkSPrm(0x4); }
    bool ChkTgNoConHit() { return mGObjTg.ChkSPrm(2); }
    bool ChkTgStopNoConHit() { return mGObjTg.ChkSPrm(0x2000); }
    bool ChkCoNoCamHit() { return mGObjCo.ChkSPrm(2); }
    dCcD_HitCallback GetCoHitCallback() { return mGObjCo.GetHitCallback(); }
    dCcD_HitCallback GetAtHitCallback() { return mGObjAt.GetHitCallback(); }
    dCcD_HitCallback GetTgHitCallback() { return mGObjTg.GetHitCallback(); }
    void OnCoHitNoActor() { mGObjCo.OnRPrm(1); }
    void OffCoHitNoActor() { mGObjCo.OffRPrm(1); }
    void OnAtHitNoActor() { mGObjAt.OnRPrm(2); }
    void OffAtHitNoActor() { mGObjAt.OffRPrm(2); }
    void OnTgHitNoActor() { mGObjTg.OnRPrm(1); }
    void OffTgHitNoActor() { mGObjTg.OffRPrm(1); }
    bool ChkCoHitNoActor() const { return mGObjCo.ChkRPrm(1); }
    bool ChkAtHitNoActor() const { return mGObjAt.ChkRPrm(2); }
    bool ChkTgHitNoActor() const { return mGObjTg.ChkRPrm(1); }
    bool ChkTgWolfSpNoDamage() { return mGObjTg.ChkSPrm(0x800); }
    bool ChkAtNoHitMark() { return mGObjAt.ChkSPrm(2); }
    bool ChkTgNoHitMark() { return mGObjTg.ChkSPrm(4); }
    bool ChkTgHookShotNoHitMark() { return mGObjTg.ChkSPrm(0x400); }
    bool ChkTgArrowNoHitMark() { return mGObjTg.ChkSPrm(0x1000); }
    dCcG_Tg_Spl GetTgSpl() { return (dCcG_Tg_Spl)mGObjTg.GetSpl(); }
    int GetTgHitMark() { return mGObjTg.GetHitMark(); }
    int GetAtHitMark() { return mGObjAt.GetHitMark(); }
    void ClrAtEffCounter() { mGObjAt.ClrEffCounter(); }
    void ClrTgEffCounter() { mGObjTg.ClrEffCounter(); }
    void ClrCoEffCounter() { mGObjCo.ClrEffCounter(); }
    void OnTgShieldHit() { mGObjTg.OnRPrm(2); }
    void OffTgShieldHit() { mGObjTg.OffRPrm(2); }
    void OnAtShieldHit() { mGObjAt.OnRPrm(1); }
    void OffAtShieldHit() { mGObjAt.OffRPrm(1); }
    void OffTgMagneHit() { mGObjTg.OffRPrm(4); }
    void SetTgRVec(cXyz& vec) { mGObjTg.SetRVec(vec); }
    void SetAtRVec(cXyz& vec) { mGObjAt.SetRVec(vec); }
    void SetTgHitPos(cXyz& pos) { mGObjTg.SetHitPos(pos); }
    void SetAtHitPos(cXyz& pos) { mGObjAt.SetHitPos(pos); }
    cXyz* GetAtHitPosP() { return mGObjAt.GetHitPosP(); }
    bool ChkTgHookshotThrough() { return mGObjTg.ChkSPrm(0x80); }

    void ClrTgHit() {
        dCcD_GObjInf__ClrTgHit(this);
    }

    void ResetTgHit() {
        dCcD_GObjInf__ResetTgHit(this);
    }

    /* 0x058 */ dCcD_GObjAt mGObjAt;
    /* 0x09C */ dCcD_GObjTg mGObjTg;
    /* 0x0E8 */ dCcD_GObjCo mGObjCo;
};  // Size = 0x104

static_assert(sizeof(dCcD_GObjInf) == 0x104);

#ifndef WII_PLATFORM
#define dCcD_Cyl_vtable __vt__8dCcD_Cyl
#else
#define dCcD_Cyl_vtable dCcD_Cyl____vt
#endif

extern "C" cCcD_GObjInf__vtbl_t dCcD_Cyl_vtable;

class dCcD_Cyl {
public:
    dCcD_GObjInf mGObjInf;
    cCcD_CylAttr mCylAttr;
};  // Size = 0x13C

#ifndef WII_PLATFORM
#define dCcD_Sph_vtable __vt__8dCcD_Sph
#else
#define dCcD_Sph_vtable dCcD_Sph____vt
#endif

extern "C" cCcD_GObjInf__vtbl_t dCcD_Sph_vtable;

class dCcD_Sph {
public:
    dCcD_GObjInf mGObjInf;
    cCcD_SphAttr mSphAttr;
};  // Size = 0x138

#ifndef WII_PLATFORM
#define dCcD_Cps_vtable __vt__8dCcD_Cps
#else
#define dCcD_Cps_vtable dCcD_Cps____vt
#endif

extern "C" cCcD_GObjInf__vtbl_t dCcD_Cps_vtable;

class dCcD_Cps {
public:
    dCcD_GObjInf mGObjInf;
    cCcD_CpsAttr mCpsAttr;
};  // Size = 0x144

class dCcD_Tri {
public:
};

#endif /* D_CC_D_CC_D_H */
