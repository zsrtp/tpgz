#ifndef D_A_D_A_PLAYER_H
#define D_A_D_A_PLAYER_H

#include "../../SSystem/SComponent/c_bg_s_poly_info.h"
#include "../d_drawlist.h"
#include "../d_stage.h"
#include "../save/d_save.h"
#include "../../f_op/f_op_actor.h"
#include "../../m_Do/m_Do_ext.h"
#include "../../JSystem/JUtility/JUTTexture.h"

class daPy_sightPacket_c : dDlst_base_c {
public:
    /* 0x04 */ bool mDrawFlag;
    /* 0x05 */ uint8_t field_0x5[3];
    /* 0x08 */ cXyz mPos;
    /* 0x14 */ Mtx field_0x14;
    /* 0x44 */ ResTIMG* field_0x44;
    /* 0x48 */ ResTIMG* field_0x48;
};

struct daPy_boomerangMove_c {};

struct JKRHeap;

class daPy_anmHeap_c {
public:
    enum daAlinkHEAP_TYPE {};

    uint16_t getIdx() const { return mIdx; }
    void resetIdx() { mIdx = 0xffff; }
    void resetPriIdx() { mPriIdx = 0xffff; }
    void resetArcNo() { mArcNo = 0xffff; }

    /* 0x00 */ uint16_t mIdx;
    /* 0x02 */ uint16_t mPriIdx;
    /* 0x04 */ uint16_t mArcNo;
    /* 0x06 */ uint16_t field_0x06;
    /* 0x08 */ int mBufferSize;
    /* 0x0C */ void* mBuffer;
    /* 0x10 */ JKRHeap* mAnimeHeap;
};  // Size = 0x14

class daPy_actorKeep_c {
public:
    uint32_t getID(void) const { return mID; }
    void setID(uint32_t id) { mID = id; }
    fopAc_ac_c* getActor(void) const { return mActor; }

    uint32_t mID;
    fopAc_ac_c* mActor;
};

#pragma pack(push, 1)
class daPy_frameCtrl_c : public J3DFrameCtrl {
public:
    uint16_t getEndFlg() { return mEndFlg; }
    uint16_t getNowSetFlg() { return mNowSetFlg; }
    void onEndFlg() { mEndFlg = 1; }
    void onNowSetFlg() { mNowSetFlg = 1; }
    void offNowSetFlg() { mNowSetFlg = 0; }
    void offEndFlg() {
        mEndFlg = 0;
        mNowSetFlg = 0;
    }

    /* 0x14 */ uint16_t mEndFlg;
    /* 0x16 */ uint16_t mNowSetFlg;
};
#pragma pack(pop)

class daPy_demo_c {
public:
    void setDemoType(uint16_t pType) { mDemoType = pType; }
    uint16_t getDemoType() const { return mDemoType; }

    /* 0x00 */ uint16_t mDemoType;
    /* 0x02 */ int16_t mDemoMoveAngle;
    /* 0x04 */ int16_t mTimer;
    /* 0x06 */ int16_t mParam2;
    /* 0x08 */ int mParam0;
    /* 0x0C */ int mParam1;
    /* 0x10 */ int mDemoMode;
    /* 0x14 */ float mStick;
    /* 0x18 */ cXyz mDemoPos0;
};  // Size = 0x24

class daPy_py_c : public fopAc_ac_c {
public:
    /* 0x0568 */ uint8_t mCutType;
    /* 0x0569 */ uint8_t mComboCutCount;
#ifdef WII_PLATFORM
    uint8_t unk_field0[4];  // might be part of fopAc_ac_c, fix later
#endif
    /* 0x056A */ uint8_t mSpecialMode;  // maybe needs better name
    /* 0x056B */ uint8_t field_0x56b;
    /* 0x056C */ int16_t mDamageTimer;
    /* 0x056E */ uint16_t mSwordUpTimer;
    /* 0x0570 */ int mNoResetFlg0;
    /* 0x0574 */ int mNoResetFlg1;
    /* 0x0578 */ int mNoResetFlg2;
    /* 0x057C */ int mNoResetFlg3;
    /* 0x0580 */ int mResetFlg0;
    /* 0x0584 */ int mResetFlg1;
    /* 0x0588 */ int mEndResetFlg0;
    /* 0x058C */ int mEndResetFlg1;
    /* 0x0590 */ int mEndResetFlg2;
    /* 0x0594 */ float field_0x594;
    /* 0x0598 */ uint8_t field_0x598[0x4];
    /* 0x059C */ int16_t mLookAngleY;
    /* 0x059E */ uint8_t field_0x59e[0x6];
    /* 0x05A4 */ cXyz mHeadTopPos;
    /* 0x05B0 */ cXyz mItemPos;
    /* 0x05BC */ cXyz mSwordTopPos;
    /* 0x05C8 */ cXyz mLeftHandPos;
    /* 0x05D4 */ cXyz mRightHandPos;
    /* 0x05E0 */ cXyz mLeftFootPosP;
    /* 0x05EC */ cXyz mRightFootPosP;
    /* 0x05F8 */ uint8_t field_0x5f8[0xC];
    /* 0x0604 */ daPy_demo_c mDemo;
    void* vtable;

public:
    enum daPy_FLG0 {
        FLG0_UNK_40000000 = 0x40000000,
        EQUIP_HEAVY_BOOTS = 0x2000000,
        FLG0_UNK_8000000 = 0x8000000,
        FLG0_UNK_1000000 = 0x1000000,
        UNDER_WATER_MOVEMENT = 0x800000,
        FLG0_UNK_80000 = 0x80000,
        FLG0_UNK_20000 = 0x20000,
        FLG0_UNK_8000 = 0x8000,
        MAGNE_BOOTS_ON = 0x1000,
        FLG0_UNK_80 = 0x80,
        FLG0_UNK_40 = 0x40,
        FLG0_UNK_20 = 0x20,
        UNK_F_ROLL_CRASH_2 = 0x10,
        UNK_F_ROLL_CRASH_1 = 0x8,
        MIDNA_RIDE = 4,

        HEAVY_STATE_BOOTS = FLG0_UNK_40000000 | EQUIP_HEAVY_BOOTS | FLG0_UNK_20000,
    };
    enum daPy_FLG1 { IS_WOLF = 0x2000000, FLG1_UNK_10000 = 0x10000, THROW_DAMAGE = 0x4000 };
    enum daPy_FLG2 {
        FLG2_UNK_4080000 = 0x4080000,
        FLG2_UNK_2080000 = 0x2080000,
        BOAR_SINGLE_BATTLE = 0x1800000,
        STATUS_WINDOW_DRAW = 0x400000,
        UNK_ARMOR = 0x80000,
        UNK_FLG2_2 = 2,
        UNK_DAPY_FLG2_1 = 1
    };
    enum daPy_FLG3 {
        FLG3_UNK_2000000 = 0x2000000,
        FLG3_UNK_100000 = 0x100000,
        COPY_ROD_THROW_AFTER = 0x40000
    };
    enum daPy_ERFLG0 {
        ERFLG0_UNK_8000000 = 0x8000000,
        ERFLG0_UNK_1000000 = 0x1000000,
        ERFLG0_UNK_800000 = 0x800000,
        ERFLG0_UNK_100000 = 0x100000,
        ERFLG0_UNK_2 = 2,
        ERFLG0_UNK_1 = 1,
    };
    enum daPy_ERFLG1 {
        GANON_FINISH = 0x80000000,
        UNK_FORCE_PUT_POS = 0x2000,
        ERFLG1_UNK_1 = 1,
    };
    enum daPy_ERFLG2 {
        ERFLG2_UNK_100 = 0x100,
    };
    enum daPy_RFLG0 {
        RFLG0_UNK_8000000 = 0x8000000,
        RFLG0_UNK_4000 = 0x4000,
        ENEMY_ATTENTION_LOCK = 0x1000,
        RFLG0_UNK_80 = 0x80,
        RFLG0_UNK_40 = 0x40,
        RFLG0_UNK_2 = 0x2,
    };

    enum {
        /* 0x01 */ SMODE_SUMO_READY = 1,
        /* 0x25 */ SMODE_SUMO_LOSE = 37,
        /* 0x27 */ SMODE_WOLF_PUZZLE = 39,
        /* 0x2A */ SMODE_GOAT_STOP = 42,
        /* 0x2B */ SMODE_GORON_THROW,
        /* 0x2C */ SMODE_CARGO_CARRY,
    };

    enum CutType {
        /* 0x01 */ TYPE_CUT_VERTICAL = 1,
        /* 0x02 */ TYPE_CUT_STAB,
        /* 0x03 */ TYPE_CUT_SWEEP,
        /* 0x04 */ TYPE_CUT_HORIZONTAL,
        /* 0x05 */ TYPE_CUT_HEAD,  // Helm Splitter
        /* 0x06 */ TYPE_CUT_LEFT_SWEEP_FINISH,
        /* 0x07 */ TYPE_CUT_DOWN_FINISH,
        /* 0x08 */ TYPE_CUT_TURN_RIGHT,
        /* 0x0A */ TYPE_CUT_JUMP = 10,
        /* 0x10 */ TYPE_CUT_AIR = 0x10,
        /* 0x12 */ TYPE_CUT_LARGE_JUMP_INIT = 0x12,
        /* 0x13 */ TYPE_CUT_LARGE_JUMP,
        /* 0x14 */ TYPE_CUT_LARGE_JUMP_FINISH,
        /* 0x15 */ TYPE_CUT_RIGHT_SWEEP_FINISH,
        /* 0x16 */ TYPE_CUT_TURN_LEFT,
        /* 0x17 */ TYPE_CUT_LARGE_TURN_LEFT,
        /* 0x18 */ TYPE_CUT_LARGE_TURN_RIGHT,
        /* 0x1A */ TYPE_CUT_FAST_MOVE = 0x1A,
        /* 0x1E */ TYPE_CUT_TWIRL = 0x1E,  // Back Slice
        /* 0x1F */ TYPE_CUT_FAST,
        /* 0x20 */ TYPE_CUT_STAB_FINISH,
        /* 0x21 */ TYPE_CUT_STAB_COMBO,
    };

    inline bool getSumouCameraMode() const {
        bool sumouCameraMode = false;
        if (mSpecialMode != 0 && mSpecialMode < 0x26) {
            sumouCameraMode = true;
        }
        return sumouCameraMode;
    }

    int checkNoResetFlg0(daPy_FLG0 pFlag) const {
        return mNoResetFlg0 & pFlag;
    }
    int checkNoResetFlg1(daPy_FLG1 pFlag) const {
        return mNoResetFlg1 & pFlag;
    }
    int checkNoResetFlg2(daPy_FLG2 pFlag) const {
        return mNoResetFlg2 & pFlag;
    }
    void onNoResetFlg0(int pFlg) {
        mNoResetFlg0 |= pFlg;
    }
    void onEndResetFlg1(daPy_ERFLG1 pFlg) {
        mEndResetFlg1 |= pFlg;
    }
    int checkWolf() {
        return checkNoResetFlg1(IS_WOLF);
    }
};

#endif /* D_A_D_A_PLAYER_H */
