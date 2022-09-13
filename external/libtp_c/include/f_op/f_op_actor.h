#ifndef F_OP_ACTOR_H_
#define F_OP_ACTOR_H_

#include "../SSystem/SComponent/c_sxyz.h"
#include "../SSystem/SComponent/c_xyz.h"
#include "../dolphin/mtx/mtx.h"
#include "../f_pc/f_pc_leaf.h"
#include "../d/kankyo/d_kankyo.h"

struct JKRSolidHeap;

class dEvt_info_c {
public:
    void setCommand(uint16_t command) { mCommand = command; }
    void setMapToolId(uint8_t id) { mMapToolId = id; }
    void setEventId(int16_t id) { mEventId = id; }
    void setCondition(uint16_t condition) { mCondition = condition; }
    void setArchiveName(char* name) { mArchiveName = name; }
    uint8_t getMapToolId() { return mMapToolId; }
    int16_t getEventId() { return mEventId; }
    uint8_t getIdx() { return mIndex; }
    char* getArchiveName() { return mArchiveName; }
    bool chkCondition(uint16_t condition) { return mCondition == condition; }

    bool checkCommandTalk() { return mCommand == 1; }
    bool checkCommandItem() { return mCommand == 4; }

public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ uint16_t mCommand;
    /* 0x06 */ uint16_t mCondition;
    /* 0x08 */ int16_t mEventId;
    /* 0x0A */ uint8_t mMapToolId;
    /* 0x0B */ uint8_t mIndex;
    /* 0x0C */ char* mArchiveName;
    /* 0x10 */ void* field_0x10;
    /* 0x14 */ void* field_0x14;
};  // Size = 0x18

struct actor_place {
    cXyz mPosition;
    csXyz mAngle;
    uint8_t mRoomNo;
};

struct actor_attention_types {
    /* 0x00 */ uint32_t mDistance1;
    /* 0x04 */ uint32_t mDistance2;
    /* 0x08 */ uint32_t mDistance3;
    /* 0x0C */ cXyz mPosition;
    /* 0x18 */ uint32_t mFlags;
};  // Size = 0x1C

class dJntCol_c;

class fopAc_ac_c : public leafdraw_class {
public:
    /* 0x0C0 */ int mAcType;
    /* 0x0C4 */ create_tag_class mAcTg;
    /* 0x0D8 */ create_tag_class mDwTg;
    /* 0x0EC */ profile_method_class* mSubMtd;
    /* 0x0F0 */ JKRSolidHeap* mHeap;
    /* 0x0F4 */ dEvt_info_c mEvtInfo;
    /* 0x10C */ dKy_tevstr_c mTevStr;
    /* 0x494 */ int16_t mSetID;
    /* 0x496 */ uint8_t mGroup;
    /* 0x497 */ uint8_t mCullType;
    /* 0x498 */ uint8_t mDemoActorId;
    /* 0x499 */ int8_t mSubtype;
    /* 0x49C */ uint32_t mStatus;
    /* 0x4A0 */ uint32_t mCondition;
    /* 0x4A4 */ uint32_t mParentPcId;
    /* 0x4A8 */ actor_place mOrig;
    /* 0x4BC */ actor_place mNext;
    /* 0x4D0 */ actor_place mCurrent;
    /* 0x4E4 */ csXyz mCollisionRot;
    /* 0x4EC */ cXyz mScale;
    /* 0x4F8 */ cXyz mSpeed;
    /* 0x504 */ Mtx* mCullMtx;
    union {
        struct {
            /* 0x508 */ cXyz mMin;
            /* 0x514 */ cXyz mMax;
        } mBox;
        struct {
            /* 0x508 */ cXyz mCenter;
            /* 0x514 */ float mRadius;
        } mSphere;
    } mCull;
    /* 0x520 */ float mCullSizeFar;
    /* 0x524 */ void* field_0x524;  // possibly J3DModel*
    /* 0x528 */ dJntCol_c* mJntCol;
    /* 0x52C */ float mSpeedF;
    /* 0x530 */ float mGravity;
    /* 0x534 */ float mMaxFallSpeed;
    /* 0x538 */ cXyz mEyePos;
    /* 0x544 */ actor_attention_types mAttentionInfo;
    /* 0x560 */ uint8_t field_0x560[0x8];  // not 100% sure on this

    const cXyz& getPosition() const { return mCurrent.mPosition; }
    const csXyz& getAngle() const { return mCurrent.mAngle; }
};  // Size: 0x568

#endif