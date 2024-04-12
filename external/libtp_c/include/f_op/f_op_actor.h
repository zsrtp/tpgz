#ifndef F_OP_ACTOR_H_
#define F_OP_ACTOR_H_

#include "../SSystem/SComponent/c_sxyz.h"
#include "../SSystem/SComponent/c_xyz.h"
#include "../dolphin/mtx/mtx.h"
#include "../f_pc/f_pc_leaf.h"
#include "../d/kankyo/d_kankyo.h"

struct JKRSolidHeap;

enum dEvt_Command_e {
    dEvtCmd_NONE_e,
    dEvtCmd_INTALK_e,
    dEvtCmd_INDEMO_e,
    dEvtCmd_INDOOR_e,
    dEvtCmd_INGETITEM_e,
    dEvtCmd_INCATCH_e = 6,
    dEvtCmd_DUMMY = 0xFFFF,
};

enum dEvt_Condition_e {
    dEvtCnd_NONE_e = 0x0000,
    dEvtCnd_CANTALK_e = 0x0001,
    dEvtCnd_CANDOOR_e = 0x0004,
    dEvtCnd_CANGETITEM_e = 0x0008,
    dEvtCnd_CANTALKITEM_e = 0x0020,
    dEvtCnd_DUMMY = 0x8000,
};

class dEvt_info_c {
public:
    void setCommand(u16 command) { mCommand = command; }
    void setMapToolId(u8 id) { mMapToolId = id; }
    void setEventId(s16 id) { mEventId = id; }
    void setCondition(u16 condition) { mCondition = condition; }
    u16 getCondition() { return mCondition; }
    void setArchiveName(char* name) { mArchiveName = name; }
    u8 getMapToolId() { return mMapToolId; }
    s16 getEventId() { return mEventId; }
    s16 getIdx() { return mIndex; }
    void setIdx(u8 i_idx) { mIndex = i_idx; }
    char* getArchiveName() { return mArchiveName; }
    BOOL chkCondition(u16 condition) { return (mCondition & condition) == condition; }
    void i_onCondition(u16 cond) { mCondition |= cond; }
    void i_offCondition(u16 cond) { mCondition &= ~cond; }

    bool checkCommandTalk() { return mCommand == dEvtCmd_INTALK_e; }
    bool checkCommandItem() { return mCommand == dEvtCmd_INGETITEM_e; }
    BOOL i_checkCommandDoor() { return mCommand == dEvtCmd_INDOOR_e; }
    bool i_checkCommandDemoAccrpt() { return mCommand == dEvtCmd_INDEMO_e; }
    bool i_checkCommandCatch() { return mCommand == dEvtCmd_INCATCH_e; }

public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ u16 mCommand;
    /* 0x06 */ u16 mCondition;
    /* 0x08 */ s16 mEventId;
    /* 0x0A */ u8 mMapToolId;
    /* 0x0B */ s8 mIndex;
    /* 0x0C */ char* mArchiveName;
    /* 0x10 */ u8 field_0x10;
    /* 0x14 */ void (*field_0x14)(void*);
};  // Size = 0x18

struct actor_place {
    /* 0x00 */ cXyz pos;
    /* 0x0C */ csXyz angle;
    /* 0x12 */ s8 roomNo;
    /* 0x13 */ u8 field_0x13;
};

struct actor_attention_types {
    void setFlag(u32 flags) { mFlags |= flags; }

    /* 0x00 */ u8 field_0x0[9];
    /* 0x0A */ s16 field_0xa;
    /* 0x0C */ cXyz mPosition;
    /* 0x18 */ u32 mFlags;
};  // Size = 0x1C

class dJntCol_c;

struct cull_sphere {
    /* 0x0 */ Vec mCenter;
    /* 0xC */ f32 mRadius;
};

struct cull_box {
    /* 0x0 */ Vec mMin;
    /* 0xC */ Vec mMax;
};

class fopAc_ac_c : public leafdraw_class {
public:
    /* 0x0C0 */ int mAcType;
    /* 0x0C4 */ create_tag_class mAcTg;
    /* 0x0D8 */ create_tag_class mDwTg;
    /* 0x0EC */ profile_method_class* mSubMtd;
    /* 0x0F0 */ JKRSolidHeap* mHeap;
    /* 0x0F4 */ dEvt_info_c mEvtInfo;
    /* 0x10C */ dKy_tevstr_c mTevStr;
    /* 0x494 */ u16 mSetID;
    /* 0x496 */ u8 mGroup;
    /* 0x497 */ s8 mCullType;
    /* 0x498 */ u8 mDemoActorId;
    /* 0x499 */ s8 mSubtype;
    /* 0x49A */ u8 mCarryType;
    /* 0x49C */ u32 mStatus;
    /* 0x4A0 */ u32 mCondition;
    /* 0x4A4 */ u32 mParentPcId;
    /* 0x4A8 */ actor_place orig;
    /* 0x4BC */ actor_place next;
    /* 0x4D0 */ actor_place current;
    /* 0x4E4 */ csXyz shape_angle;
    /* 0x4EC */ cXyz mScale;
    /* 0x4F8 */ cXyz speed;
    /* 0x504 */ MtxP mCullMtx;
    union {
        /* 0x508 */ cull_box mBox;
        /* 0x508 */ cull_sphere mSphere;
    } mCull;
    /* 0x520 */ f32 mCullSizeFar;
    /* 0x524 */ J3DModel* model;
    /* 0x528 */ dJntCol_c* mJntCol;
    /* 0x52C */ f32 speedF;
    /* 0x530 */ f32 mGravity;
    /* 0x534 */ f32 mMaxFallSpeed;
    /* 0x538 */ cXyz mEyePos;
    /* 0x544 */ actor_attention_types mAttentionInfo;
#ifdef WII_PLATFORM
    u8 unkdata[4];
#endif
    /* 0x560 */ s16 field_0x560;
    /* 0x562 */ s16 mHealth;
    /* 0x564 */ u8 field_0x564;
    /* 0x565 */ u8 field_0x565;
    /* 0x566 */ u8 field_0x566;
    /* 0x567 */ s8 field_0x567;
};  // Size: 0x568

#ifndef WII_PLATFORM
static_assert(sizeof(fopAc_ac_c) == 0x568);
#endif

class J3DAnmTextureSRTKey;
class J3DAnmTevRegKey;

class fopEn_enemy_c : public fopAc_ac_c {
public:
    bool checkWolfNoLock() const { return mFlags & 0x200; }
    bool checkHeadLockFlg() const { return mFlags & 0x80; }
    bool checkDownFlg() const { return mFlags & 0x1; }
    bool checkDeadFlg() const { return mFlags & 0x8; }
    cXyz& getDownPos() { return mDownPos; }
    cXyz& getHeadLockPos() { return mHeadLockPos; }

    void onCutDownHitFlg() { mFlags |= 2; }
    void onWolfBiteDamage() { mFlags |= 0x40; }
    void onWolfDownStartFlg() { mFlags |= 0x14; }
    void onWolfDownPullEndFlg() { mFlags |= 0x20; }

    void setThrowModeCatch() { mThrowMode |= 2; }
    void setThrowModeDash() { mThrowMode |= 4; }
    void setThrowModeThrowRight() { mThrowMode |= 0x10; }
    void setThrowModeThrowLeft() { mThrowMode |= 8; }
    
    /* 0x568 */ cXyz mDownPos;
    /* 0x574 */ cXyz mHeadLockPos;
    /* 0x580 */ J3DModel* mBallModel;
    /* 0x584 */ J3DAnmTextureSRTKey* mBtk;
    /* 0x588 */ J3DAnmTevRegKey* mBrk;
    /* 0x58C */ u8 field_0x58c;
    /* 0x58D */ u8 mThrowMode;
    /* 0x58E */ u16 mFlags;
    /* 0x590 */ f32 field_0x590;
    /* 0x594 */ u32 mEffectID1;
    /* 0x598 */ u32 mEffectID2;
    /* 0x59C */ u32 mMidnaBindID[3];
    /* 0x5A8 */ u8 field_0x5a8;
};  // Size: 0x5AC

#ifndef WII_PLATFORM
static_assert(sizeof(fopEn_enemy_c) == 0x5AC);
#endif

#endif