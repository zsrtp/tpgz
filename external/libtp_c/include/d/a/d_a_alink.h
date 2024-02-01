#ifndef D_A_D_A_ALINK_H
#define D_A_D_A_ALINK_H

#include "../../Z2AudioLib/Z2Creature.h"
#include "../../Z2AudioLib/Z2WolfHowlMgr.h"
#include "d_a_player.h"
#include "../bg/d_bg_s.h"
#include "../cc/d_cc_d.h"
#include "../cc/d_cc_mass_s.h"
#include "../d_attention.h"
#include "../d_drawlist.h"
#include "../d_eye_hl.h"
#include "../d_jnt_col.h"
#include "../kankyo/d_kankyo.h"
#include "../meter/d_meter2_info.h"
#include "../msg/d_msg_flow.h"
#include "../particle/d_particle.h"
#include "../particle/d_particle_copoly.h"
#include "../../JSystem/J2DGraph/J2DPane.h"
#include "../../defines.h"

class J2DScreen {};
class J2DAnmBase {};
class J3DAnmBase {};
class JKRExpHeap;
class J3DModelData {};

class daAlink_lockCursor_c : public dDlst_base_c {
public:
    /* 0x04 */ bool field_0x4;
    /* 0x05 */ u8 field_0x5[3];
    /* 0x08 */ J2DScreen* field_0x8;
    /* 0x0C */ J2DPane* field_0xc;
    /* 0x10 */ J2DPane* field_0x10;
    /* 0x14 */ J2DPane* field_0x14;
    /* 0x18 */ J2DPane* field_0x18;
    /* 0x1C */ J2DAnmBase* field_0x1c;
    /* 0x20 */ J2DAnmBase* field_0x20;
    /* 0x24 */ J2DAnmBase* field_0x24;
    /* 0x28 */ J2DAnmBase* field_0x28;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
};

class daAlink_sight_c : public daPy_sightPacket_c {
public:
    /* 0x4C */ bool mLockFlag;
    /* 0x4D */ u8 field_0x4d[3];
    /* 0x50 */ daAlink_lockCursor_c field_0x50;
};

class daAlink_blur_c : public J3DPacket {
public:
    /* 0x010 */ u8 field_0x10[4];
    /* 0x014 */ int field_0x14;
    /* 0x018 */ u8 field_0x18[4];
    /* 0x01C */ int field_0x1c;
    /* 0x020 */ u8 field_0x20[4];
    /* 0x024 */ f32 field_0x24;
    /* 0x028 */ u8 field_0x28[4];
    /* 0x02C */ cXyz field_0x2c;
    /* 0x038 */ cXyz field_0x38[0x3C];
    /* 0x308 */ cXyz field_0x308[0x3C];
};  // Size = 0x5D8

class dAlink_bottleWaterPcallBack_c : public JPAParticleCallBack {
public:
    /* 0x04 */ s16 mHitFlg;
    /* 0x06 */ s16 mAppearFlg;
    /* 0x08 */ f32 mKeepMinY;
    /* 0x0C */ cXyz mHitPos;
};  // Size = 0x18

class daAlink_footData_c {
public:
    u8 field_0x00[0x8];
    cXyz field_0x08;
    Mtx field_0x14;
    Mtx field_0x44;
    Mtx field_0x74;
};  // Size = 0xA4

class daAlink_c : public daPy_py_c {
public:
    enum daAlink_ANM {
        GANON_FINISH = 408  // name probably wrong, fix later
    };

    enum daAlink_UPPER {
        Unk0,
        Unk1,
        UPPER_NOW  // needs better name. main upper anmheap idx checked for actions
    };

    enum daAlink_UNDER {};
    enum daAlink_FTANM {};
    enum daAlink_WARP_MAT_MODE {};
    enum daAlink_WANM {};

    enum MODE_FLG {
        PLAYER_FLY = 0x70852,
    };

    enum daAlink_PROC {
        PREACTION_UNEQUIP,
        SERVICE_WAIT,
        HUMAN_WAIT = 3,
        HUMAN_SIDESTEP = 10,
        HUMAN_SIDESTEP_LAND,
        HUMAN_SLIDE,
        FRONT_ROLL = 14,
        FRONT_ROLL_CRASH,
        HUMAN_KNOCKBACK,
        SIDE_ROLL,
        BACK_JUMP,
        BACK_JUMP_LAND,
        SLIP,
        HUMAN_AUTOJUMP,
        DIVE_JUMP,
        ROLL_JUMP,
        FALL,
        LAND,
        SMALL_JUMP,
        STEP_MOVE,
        GUARD_SLIP = 29,
        GUARD_ATTACK,
        GUARD_BREAK,
        TURN_MOVE,
        CUT_NORMAL,
        CUT_FINISH,
        CUT_FINISH_JUMP_UP,
        CUT_FINISH_JUMP_UP_LAND,
        CUT_REVERSE,
        CUT_JUMP,
        CUT_JUMP_LAND,
        COMBO_CUT_TURN,
        CUT_CHARGE,
        CUT_TURN_MOVE,
        CUT_DOWN,
        CUT_DOWN_LAND,
        CUT_HEAD,
        CUT_HEAD_LAND,
        CUT_LARGE_JUMP_CHARGE,
        CUT_LARGE_JUMP,
        CUT_LARGE_JUMP_LAND,
        DAMAGE,
        LAND_DAMAGE = 52,
        CRAWL_START,
        CRAWL_MOVE,
        CRAWL_AUTOMOVE,
        CRAWL_END,
        PULL_MOVE,
        HORSE_RIDE,
        HORSE_GETOFF,
        HORSE_TURN = 61,
        HORSE_JUMP,
        HORSE_LAND,
        HORSE_SUBJECTIVITY,
        HORSE_CUT,
        HORSE_CUT_CHARGE_READY,
        HORSE_CUT_TURN,
        HORSE_DAMAGE,
        RIDE_BOW_READY,
        HORSE_BOTTLE_DRINK = 76,
        HORSE_KANDELAAR_POUR = 78,
        HORSE_RUN,
        HORSE_HANG,
        BOAR_RUN = 83,
        HANG_START = 85,
        HANG_FALL_START,
        HANG_UP,
        HANG_WAIT,
        HANG_MOVE,
        COPY_ROD_SWING = 101,
        GRAB_READY = 108,
        GRAB_UP,
        GRAB_THROW = 111,
        GRAB_DOWN,
        GRAB_REBOUND = 114,
        GRAB_STAND,
        INSECT_CATCH,
        PICK_UP,
        PICK_PUT,
        HUMAN_ST_ESCAPE,
        CLIMB_MOVE_VERTICAL = 130,
        CLIMB_MOVE_HORIZONTAL,
        CANOE_RIDE = 140,
        CANOE_JUMP_RIDE,
        CANOE_GETOFF,
        CANOE_ROW = 144,
        CANOE_PADDLE_SHIFT,
        CANOE_PADDLE_PUT,
        CANOE_PADDLE_GRAB,
        CANOE_ROD_GRAB,
        CANOE_FISHING_REEL = 150,
        CANOE_FISHING_GET,
        CANOE_SUBJECTIVITY,
        CANOE_BOTTLE_DRINK = 160,
        CANOE_KANDELAAR_POUR,
        FISHING_FOOD = 163,
        BOARD_CUT_TURN = 173,
        FM_CHAIN_UP,
        BOTTLE_DRINK = 179,
        EMPTY_BOTTLE_SWING = 181,
        GRASS_WHISTLE = 186,
        HAWK_WAIT = 188,
        FLOOR_DOWN_REBOUND = 189,
        GORON_RIDE_WAIT,
        GOAT_THROW = 192,
        GOAT_STROKE,
        MAGNE_BOOTS_FLY = 204,
        BOOTS_EQUIP,
        SUMOU_PUSH = 207,
        SUMOU_SIDE_MOVE,
        SUMOU_ACTION,
        SUMOU_STAGGER,
        SUMOU_WIN_LOSE,
        BOSS_ENEMY_HANG = 220,
        SCREAM_WAIT = 222,
        DUNGEON_WARP_READY = 234,
        WOLF_HOWL = 237,
        WOLF_WAIT = 241,
        WOLF_DASH = 243,
        WOLF_KNOCKBACK = 244,
        WOLF_SIDESTEP = 247,
        WOLF_AUTOJUMP = 252,
        WOLF_RSIT = 255,
        WOLF_DAMAGE = 263,
        WOLF_SLIDE = 271,
        WOLF_ROPE_HANG = 275,
        WOLF_TAGLOCK_JUMP = 280,
        WOLF_TAGLOCK_LAND,
        WOLF_DOWNATTACK_PULLOUT = 291,
        WOLF_JUMPATTACK = 284,
        WOLF_ST_ESCAPE = 289,
        WOLF_CHAIN = 305,
        WOLF_DIG,
        WOLF_ENEMY_HANG_BITE = 310,
        SUBJECTIVITY = 318,
        POLY_DAMAGE = 321,
        ELEC_DAMAGE,
        PUSH_PULL_WAIT,
        PUSH_MOVE,
        TRESURE_STAND = 328,
        METAMORPHOSE = 333,
        DEAD = 336,
        LARGE_DAMAGE = 345,
        LARGE_DAMAGE_WALL,
    };

    // this might be one of the above enums, but not clear yet
    enum UPPER_ANM {
        ANM_SMALL_GUARD = 22,
        ANM_HUMAN_CHAIN_GRAB = 98,
        ANM_WOLF_CHAIN_GRAB = 672,
        ANM_WOLF_ENEMY_THROW_LEFT = 701,
        ANM_WOLF_ENEMY_THROW_RIGHT,
    };

    class firePointEff_c {
        /* 0x00 */ u8 field_0x0[0xc];
        /* 0x0C */ cXyz field_0xc;
        /* 0x18 */ cXyz field_0x18;
        /* 0x24 */ cXyz field_0x24;
    };

    class hsChainShape_c {};

    // inlined version of checkModeFlg
    u32 checkModeFlg(u32 pFlag) const { return mModeFlg & pFlag; }
    bool checkUpperAnime(u16 pIdx) const { return mUpperAnime[UPPER_NOW].getIdx() == pIdx; }

    /* 0x0062C */ void* field_0x062C;
    /* 0x00630 */ int field_0x0630;
    /* 0x00634 */ char* mArcName;
    /* 0x00638 */ JKRExpHeap** field_0x0638;
    /* 0x0063C */ void* field_0x063C;
    /* 0x00640 */ int field_0x0640;
    /* 0x00644 */ char* mShieldArcName;
    /* 0x00648 */ JKRExpHeap** field_0x0648;
    /* 0x0064C */ J3DModelData* field_0x064C;
    /* 0x00650 */ J3DModel* field_0x0650;
    /* 0x00654 */ J3DModel* field_0x0654;
    /* 0x00658 */ J3DModel* field_0x0658;
    /* 0x0065C */ J3DModel* field_0x065c;
    /* 0x00660 */ J3DModel* field_0x0660;
    /* 0x00664 */ J3DModel* field_0x0664;
    /* 0x00668 */ J3DModel* field_0x0668;
    /* 0x0066C */ J3DModel* field_0x066c;
    /* 0x00670 */ J3DModel* field_0x0670;
    /* 0x00674 */ J3DModel* field_0x0674;
    /* 0x00678 */ J3DModel* mShieldModel;
    /* 0x0067C */ J3DAnmBase* field_0x067c;
    /* 0x00680 */ J3DAnmBase* field_0x0680;
    /* 0x00684 */ J3DModel* field_0x0684;
    /* 0x00688 */ J3DModel* field_0x0688;
    /* 0x0068C */ J3DAnmBase* field_0x068c;
    /* 0x00690 */ mDoExt_baseAnm** field_0x0690;
    /* 0x00694 */ void* field_0x0694;
    /* 0x00698 */ void* field_0x0698;
    /* 0x0069C */ void* field_0x069c;
    /* 0x006A0 */ J3DModel* field_0x06a0;
    /* 0x006A4 */ mDoExt_bckAnm* field_0x06a4;
    /* 0x006A8 */ J3DModel* field_0x06a8;
    /* 0x006AC */ mDoExt_bckAnm* field_0x06ac;
    /* 0x006B0 */ mDoExt_bckAnm* field_0x06b0;
    /* 0x006B4 */ J3DAnmTransform* field_0x06b4;
    /* 0x006B8 */ J3DModel* mSwordModel;
    /* 0x006BC */ J3DModel* field_0x06bc;
    /* 0x006C0 */ J3DModelData* field_0x06c0;
    /* 0x006C4 */ J3DAnmBase* m_nSwordBtk;
    /* 0x006C8 */ J3DAnmBase* m_mSwordBtk;
    /* 0x006CC */ J3DAnmBase* m_mSwordBck;
    /* 0x006D0 */ void* field_0x06d0;
    /* 0x006D4 */ void* field_0x06d4;
    /* 0x006D8 */ void* field_0x06d8;
    /* 0x006DC */ void* field_0x06dc;
    /* 0x006E0 */ void* field_0x06e0;
    /* 0x006E4 */ void* field_0x06e4;
    /* 0x006E8 */ void* field_0x06e8;
    /* 0x006EC */ void* field_0x06ec;
    /* 0x006F0 */ void* field_0x06f0;
    /* 0x006F4 */ J3DAnmBase* field_0x06f4;
    /* 0x006F8 */ J3DAnmBase* field_0x06f8;
    /* 0x006FC */ J3DModel* field_0x06fc;
    /* 0x00700 */ J3DModel* field_0x0700;
    /* 0x00704 */ J3DAnmBase* field_0x0704;
    /* 0x00708 */ J3DModel* mHeldItemModel;
    /* 0x0070C */ J3DModel* field_0x070c;
    /* 0x00710 */ J3DModel* field_0x0710;
    /* 0x00714 */ J3DModel* field_0x0714;
    /* 0x00718 */ J3DAnmBase* field_0x0718;
    /* 0x0071C */ J3DAnmBase* field_0x071c;
    /* 0x00720 */ J3DAnmBase* field_0x0720;
    /* 0x00724 */ J3DAnmBase* field_0x0724;
    /* 0x00728 */ J3DAnmBase* field_0x0728;
    /* 0x0072C */ J3DAnmBase* field_0x072c;
    /* 0x00730 */ mDoExt_bckAnm field_0x730;
    /* 0x0074C */ mDoExt_bckAnm field_0x74C;
    /* 0x00768 */ u8 field_0x0768[0x5C];
    /* 0x007C4 */ daPy_actorKeep_c mWolfLockAcKeep[10];
    /* 0x00814 */ dCcD_Stts field_0x814;
    /* 0x00850 */ dCcD_Cyl field_0x850[3];
    /* 0x00C04 */ dCcD_Cyl field_0xC04[3];
    /* 0x00FB8 */ dCcD_Sph field_0xFB8;
    /* 0x010F0 */ dCcD_Cyl field_0x10F0;
    /* 0x0122C */ dCcD_Cps field_0x122C[3];
    /* 0x015F8 */ dCcD_Cps field_0x15F8;
    /* 0x0173C */ dCcD_Stts field_0x173c;
    /* 0x01778 */ dCcD_Sph field_0x1778;
    /* 0x018B0 */ dBgS_AcchCir field_0x18B0[3];
    /* 0x01970 */ dBgS_LinkAcch mLinkAcch;
    /* 0x01B48 */ dBgS_LinkLinChk mLinkLinChk;
    /* 0x01BB8 */ dBgS_RopeLinChk mRopeLinChk;
    /* 0x01C28 */ dBgS_BoomerangLinChk mBoomerangLinChk;
    /* 0x01C98 */ dBgS_ArrowLinChk mArrowLinChk;
    /* 0x01D08 */ dBgS_LinkGndChk mLinkGndChk;
    /* 0x01D5C */ dBgS_LinkRoofChk mLinkRoofChk;
    /* 0x01DAC */ dBgS_LinkLinChk mLinkLinChk2;
    /* 0x01E1C */ cBgS_PolyInfo mPolyInfo1;
    /* 0x01E2C */ cBgS_PolyInfo mPolyInfo2;
    /* 0x01E3C */ cBgS_PolyInfo mPolyInfo3;
    /* 0x01E4C */ cBgS_PolyInfo mPolyInfo4;
    /* 0x01E5C */ dBgS_ObjLinChk mObjLinChk;
    /* 0x01ECC */ dBgS_ObjGndChk mObjGndChk;
    /* 0x01F20 */ u8 field_0x1f20[8];
    /* 0x01F28 */ mDoExt_AnmRatioPack field_0x1f28[3];
    /* 0x01F40 */ mDoExt_AnmRatioPack field_0x1f40[3];
    /* 0x01F58 */ daPy_anmHeap_c mUnderAnime[3];
    /* 0x01F94 */ daPy_anmHeap_c mUpperAnime[3];
    /* 0x01FD0 */ daPy_frameCtrl_c mFrameCtrl1[3];
    /* 0x02018 */ daPy_frameCtrl_c mFrameCtrl2[3];
    /* 0x02060 */ void* field_0x2060;  // mDoExt_MtxCalcOldFrame*
    /* 0x02064 */ daAlink_sight_c mSight;
#ifdef WII_PLATFORM
    u8 unk_field0[4];
#endif
    /* 0x020F0 */ daPy_anmHeap_c mAnmHeap3;
    /* 0x02104 */ daPy_anmHeap_c mAnmHeap4;
    /* 0x02118 */ daPy_anmHeap_c mAnmHeap5;
    /* 0x0212C */ daPy_anmHeap_c mAnmHeap6;
    /* 0x02140 */ daPy_anmHeap_c mAnmHeap7;
    /* 0x02154 */ mDoExt_bckAnm field_0x2154;
    /* 0x02170 */ u8 field_0x2170[0x18];
    /* 0x02188 */ dEyeHL_c mEyeHL1;
    /* 0x0219C */ dEyeHL_c mEyeHL2;
    /* 0x021B0 */ daPy_anmHeap_c mItemHeap[2];
    /* 0x021D8 */ daPy_anmHeap_c mAnmHeap9;
    /* 0x021EC */ u8 field_0x21ec[4];
    /* 0x021F0 */ daAlink_blur_c m_swordBlur;
    /* 0x027C8 */ dAlink_bottleWaterPcallBack_c field_0x27c8;
    /* 0x027E0 */ dAttention_c* mAttention;
    /* 0x027E4 */ dAttList_c* mAttList;
    /* 0x027E8 */ dAttList_c* mAttList2;
    /* 0x027EC */ fopAc_ac_c* mTargetedActor;
    /* 0x027F0 */ fopAc_ac_c* field_0x27f0;
    /* 0x027F4 */ fopAc_ac_c* field_0x27f4;
    /* 0x027F8 */ fopAc_ac_c* field_0x27f8;
    /* 0x027FC */ fopAc_ac_c* field_0x27fc;
    /* 0x02800 */ fopAc_ac_c* mMidnaMsg;
    /* 0x02804 */ fopAc_ac_c* field_0x2804;
    /* 0x02808 */ fopAc_ac_c* field_0x2808;
    /* 0x0280C */ daPy_actorKeep_c field_0x280c;
    /* 0x02814 */ daPy_actorKeep_c mRideActor;  // daspinnerc?
    /* 0x0281C */ daPy_actorKeep_c field_0x281c;
    /* 0x02824 */ daPy_actorKeep_c mItemActor;  // name might be wrong
    /* 0x0282C */ daPy_actorKeep_c mGrabItemActor;
    /* 0x02834 */ daPy_actorKeep_c mThrowBoomerangActor;
    /* 0x0283C */ daPy_actorKeep_c mCopyRodAcKeep;
    /* 0x02844 */ daPy_actorKeep_c field_0x2844;
    /* 0x0284C */ daPy_actorKeep_c field_0x284c;
    /* 0x02854 */ daPy_actorKeep_c mCargoCarryActor;
    /* 0x0285C */ daPy_actorKeep_c field_0x285c;
    /* 0x02864 */ dMsgFlow_c mMsgFlow;
    /* 0x028B0 */ u8 field_0x28b0[0x40];
    /* 0x028F0 */ int field_0x28f0;
    /* 0x028F4 */ int mAtnActorID;
    /* 0x028F8 */ int field_0x28f8;
    /* 0x028FC */ int field_0x28fc;
    /* 0x02900 */ void* field_0x2900;
    /* 0x02904 */ daAlink_footData_c mFootData1[2];
    /* 0x02A4C */ daAlink_footData_c mFootData2[2];
    /* 0x02B94 */ f32* field_0x2b94;
    /* 0x02B98 */ f32* field_0x2b98;
    /* 0x02B98 */ f32* field_0x2b9c;
    /* 0x02BA0 */ f32* field_0x2ba0;
    /* 0x02BA4 */ f32* field_0x2ba4;
    /* 0x02BA8 */ f32* field_0x2ba8;
    /* 0x02BAC */ cXyz field_0x2bac;
    /* 0x02BB8 */ Mtx mInvMtx;
    /* 0x02BE8 */ Mtx field_0x2be8;
    /* 0x02C18 */ Mtx mRootMtx;
    /* 0x02C48 */ Mtx field_0x2c48;
    /* 0x02C78 */ Mtx field_0x2c78;
    /* 0x02CA8 */ Z2CreatureLink mZ2Link;
    /* 0x02D75 */ u8 field_0x2d75[3];  // padding
    /* 0x02D78 */ void* field_0x2d78;
    /* 0x02D7C */ daPy_frameCtrl_c* field_0x2d7c;
    /* 0x02D80 */ int field_0x2d80;
    /* 0x02D84 */ Z2WolfHowlMgr mZ2WolfHowlMgr;
    /* 0x02E44 */ dJntCol_c field_0x2e44;
    /* 0x02E54 */ dPaPo_c field_0x2e54;
    /* 0x02E8C */ u8 field_0x2e8c[0x90];
    /* 0x02F1C */ dPaPo_c* field_0x2f1c;
    /* 0x02F20 */ dPa_hermiteEcallBack_c field_0x2f20;
    /* 0x02F38 */ dPa_hermiteEcallBack_c field_0x2f38;
    /* 0x02F50 */ Vec* field_0x2f50;
    /* 0x02F54 */ Vec* field_0x2f54;
    /* 0x02F58 */ u16* field_0x2f58;
    /* 0x02F5C */ LIGHT_INFLUENCE field_0x2f5c;
    /* 0x02F7C */ u8 field_0x2f7c[16];
    /* 0x02F8C */ u8 field_0x2f8c;
    /* 0x02F8D */ u8 mItemTrigger;
    /* 0x02F8E */ u8 mItemButton;
    /* 0x02F8F */ u8 field_0x2f8f;
    /* 0x02F90 */ u8 field_0x2f90;
    /* 0x02F91 */ u8 field_0x2f91;
    /* 0x02F92 */ u8 field_0x2f92;
    /* 0x02F93 */ u8 field_0x2f93;
    /* 0x02F94 */ u8 field_0x2f94;
    /* 0x02F95 */ u8 field_0x2f95;
    /* 0x02F96 */ u8 field_0x2f96;
    /* 0x02F97 */ u8 field_0x2f97;
    /* 0x02F98 */ u8 field_0x2f98;
    /* 0x02F99 */ u8 field_0x2f99;
    /* 0x02F9A */ s8 mVoiceReverbIntensity;
    /* 0x02F9B */ u8 field_0x2f9b;
    /* 0x02F9C */ u8 mSelectItemId;
    /* 0x02F9D */ u8 field_0x2f9d;
    /* 0x02F9E */ u8 field_0x2f9e;
    /* 0x02F9F */ u8 field_0x2f9f;
    /* 0x02FA0 */ u8 field_0x2fa0;
    /* 0x02FA1 */ u8 mRunCutComboCount;
    /* 0x02FA2 */ u8 mActiveBombNum;
    /* 0x02FA3 */ u8 field_0x2fa3;
    /* 0x02FA4 */ u8 mRollCrashFlg;
    /* 0x02FA5 */ u8 field_0x2fa5;
    /* 0x02FA6 */ u8 field_0x2fa6;
    /* 0x02FA7 */ u8 field_0x2fa7;
    /* 0x02FA8 */ u8 field_0x2fa8;
    /* 0x02FA9 */ u8 field_0x2fa9;
    /* 0x02FAA */ u8 mRideStatus;
    /* 0x02FAB */ u8 field_0x2fab;
    /* 0x02FAC */ u8 field_0x2fac;
    /* 0x02FAD */ u8 field_0x2fad;
    /* 0x02FAE */ u8 field_0x2fae;
    /* 0x02FAF */ u8 field_0x2faf;
    /* 0x02FB0 */ u8 field_0x2fb0;
    /* 0x02FB1 */ u8 mWolfLockNum;
    /* 0x02FB2 */ u8 mMidnaTalkDelayTimer;
    /* 0x02FB3 */ u8 field_0x2fb3;
    /* 0x02FB4 */ u8 field_0x2fb4;
    /* 0x02FB5 */ u8 field_0x2fb5;
    /* 0x02FB6 */ u8 field_0x2fb6;
    /* 0x02FB7 */ u8 field_0x2fb7;
    /* 0x02FB8 */ u8 field_0x2fb8;
    /* 0x02FB9 */ u8 field_0x2fb9;
    /* 0x02FBA */ u8 field_0x2fba;
    /* 0x02FBB */ u8 field_0x2fbb;
    /* 0x02FBC */ u8 field_0x2fbc;
    /* 0x02FBD */ u8 field_0x2fbd;
    /* 0x02FBE */ u8 field_0x2fbe;
    /* 0x02FBF */ u8 mClothesChangeWaitTimer;
    /* 0x02FC0 */ u8 field_0x2fc0;
    /* 0x02FC1 */ u8 field_0x2fc1;
    /* 0x02FC2 */ u8 field_0x2fc2;
    /* 0x02FC3 */ u8 field_0x2fc3;
    /* 0x02FC4 */ u8 field_0x2fc4;
    /* 0x02FC5 */ u8 field_0x2fc5;
    /* 0x02FC6 */ u8 field_0x2fc6;
    /* 0x02FC7 */ u8 field_0x2fc7;
    /* 0x02FC8 */ u8 field_0x2fc8;
    /* 0x02FC9 */ u8 field_0x2fc9;
    /* 0x02FCA */ u8 field_0x2fca;
    /* 0x02FCB */ u8 field_0x2fcb;
    /* 0x02FCC */ u8 field_0x2fcc;
    /* 0x02FCD */ u8 field_0x2fcd;
    /* 0x02FCE */ u8 field_0x2fce;
    /* 0x02FCF */ u8 field_0x2fcf;
    /* 0x02FD0 */ u8 field_0x2fd0;
    /* 0x02FD1 */ u8 mShieldChangeWaitTimer;
    /* 0x02FD2 */ u8 field_0x2fd2;
    /* 0x02FD3 */ u8 field_0x2fd3;
    /* 0x02FD4 */ u8 field_0x2fd4;
    /* 0x02FD5 */ u8 field_0x2fd5;
    /* 0x02FD6 */ u8 mSwordChangeWaitTimer;
    /* 0x02FD7 */ u8 field_0x2fd7;
    /* 0x02FD8 */ u8 field_0x2fd8;
    /* 0x02FD9 */ u8 field_0x2fd9[3];
    /* 0x02FDC */ u16 mEquipItem;
    /* 0x02FDE */ u16 field_0x2fde;
    /* 0x02FE0 */ u16 field_0x2fe0;
    /* 0x02FE2 */ s16 field_0x2fe2;
    /* 0x02FE4 */ s16 field_0x2fe4;
    /* 0x02FE6 */ s16 field_0x2fe6;
    /* 0x02FE8 */ u16 mActionID;
    /* 0x02FEA */ u16 field_0x2fea;
    /* 0x02FEC */ s16 field_0x2fec;
    /* 0x02FEE */ s16 field_0x2fee;
    /* 0x02FF0 */ s16 field_0x2ff0;
    /* 0x02FF2 */ s16 field_0x2ff2;
    /* 0x02FF4 */ s16 field_0x2ff4;
    /* 0x02FF6 */ s16 field_0x2ff6;
    /* 0x02FF8 */ s16 field_0x2ff8;
    /* 0x02FFA */ s16 field_0x2ffa;
    /* 0x02FFC */ s16 field_0x2ffc;
    /* 0x02FFE */ s16 field_0x2ffe;
    /* 0x03000 */ s16 field_0x3000;
    /* 0x03002 */ s16 field_0x3002;
    /* 0x03004 */ s16 field_0x3004;
    /* 0x03006 */ s16 field_0x3006;
    /* 0x03008 */ s16 field_0x3008;
    /* 0x0300A */ s16 field_0x300a;
    /* 0x0300C */ s16 mCommonCounter;  // might need more accurate name
    /* 0x0300E */ s16 field_0x300e;
    /* 0x03010 */ s16 field_0x3010;
    /* 0x03012 */ s16 field_0x3012;
    /* 0x03014 */ s16 mFallVoiceInit;
    /* 0x03016 */ u8 field_0x3016[2];
    /* 0x03018 */ s16 field_0x3018;
    /* 0x0301A */ s16 field_0x301a;
    /* 0x0301C */ s16 field_0x301c;
    /* 0x0301E */ s16 field_0x301e;
    /* 0x03020 */ s16 field_0x3020;
    /* 0x03022 */ s16 field_0x3022;
    /* 0x03024 */ s16 field_0x3024;
    /* 0x03026 */ s16 field_0x3026;
    /* 0x03028 */ s16 field_0x3028;
    /* 0x0302A */ u8 field_0x302a[2];
    /* 0x0302C */ s16 field_0x302c;
    /* 0x0302E */ s16 field_0x302e;
    /* 0x03030 */ s16 field_0x3030;
    /* 0x03032 */ s16 field_0x3032;
    /* 0x03034 */ s16 field_0x3034;
    /* 0x03036 */ s16 field_0x3036;
    /* 0x03038 */ u8 field_0x3038[2];
    /* 0x0303A */ s16 field_0x303a;
    /* 0x0303C */ u8 field_0x303c[4];
    /* 0x03040 */ s16 field_0x3040;
    /* 0x03042 */ s16 field_0x3042;
    /* 0x03044 */ s16 field_0x3044;
    /* 0x03046 */ s16 field_0x3046;
    /* 0x03048 */ s16 field_0x3048;
    /* 0x0304A */ s16 field_0x304a;
    /* 0x0304C */ u8 field_0x304c[2];
    /* 0x0304E */ s16 field_0x304e;
    /* 0x03050 */ u8 field_0x3050[4];
    /* 0x03054 */ s16 field_0x3054;
    /* 0x03056 */ s16 field_0x3056;
    /* 0x03058 */ u8 field_0x3058[2];
    /* 0x0305A */ s16 field_0x305a;
    /* 0x0305C */ s16 field_0x305c;
    /* 0x0305E */ u8 field_0x305e[2];
    /* 0x03060 */ s16 field_0x3060;
    /* 0x03062 */ s16 field_0x3062;
    /* 0x03064 */ s16 field_0x3064;
    /* 0x03066 */ s16 field_0x3066;
    /* 0x03068 */ u8 field_0x3068[4];
    /* 0x0306C */ s16 field_0x306c;
    /* 0x0306E */ s16 field_0x306e;
    /* 0x03070 */ s16 field_0x3070;
    /* 0x03072 */ s16 field_0x3072;
    /* 0x03074 */ s16 field_0x3074;
    /* 0x03076 */ s16 field_0x3076;
    /* 0x03078 */ s16 field_0x3078;
    /* 0x0307A */ s16 field_0x307a;
    /* 0x0307C */ s16 field_0x307c;
    /* 0x0307E */ s16 field_0x307e;
    /* 0x03080 */ s16 field_0x3080;
    /* 0x03082 */ s16 field_0x3082;
    /* 0x03084 */ u16 field_0x3084;
    /* 0x03086 */ u16 field_0x3086;
    /* 0x03088 */ s16 field_0x3088;
    /* 0x0308A */ s16 field_0x308a;
    /* 0x0308C */ s16 field_0x308c;
    /* 0x0308E */ s16 mFastShotTime;
    /* 0x03090 */ s16 field_0x3090;
    /* 0x03092 */ s16 field_0x3092;
    /* 0x03094 */ s16 field_0x3094;
    /* 0x03096 */ u8 field_0x3096[4];
    /* 0x0309A */ s16 field_0x309a;
    /* 0x0309C */ u8 field_0x309c[4];
    /* 0x030A0 */ s16 field_0x30a0;
    /* 0x030A2 */ s16 field_0x30a2;
    /* 0x030A4 */ s16 field_0x30a4;
    /* 0x030A6 */ s16 field_0x30a6;
    /* 0x030A8 */ u16 field_0x30a8;
    /* 0x030AA */ u16 field_0x30aa;
    /* 0x030AC */ s16 mWolfEyeUp;
    /* 0x030AE */ u16 field_0x30ae;
    /* 0x030B0 */ s16 field_0x30b0;
    /* 0x030B2 */ s16 field_0x30b2;
    /* 0x030B4 */ u16 field_0x30b4;
    /* 0x030B6 */ u16 field_0x30b6;
    /* 0x030B8 */ u16 field_0x30b8;
    /* 0x030BA */ u16 field_0x30ba;
    /* 0x030BC */ u16 field_0x30bc;
    /* 0x030BE */ u16 field_0x30be;
    /* 0x030C0 */ u16 field_0x30c0;
    /* 0x030C2 */ u16 field_0x30c2;
    /* 0x030C4 */ u16 field_0x30c4;
    /* 0x030C6 */ u16 field_0x30c6;
    /* 0x030C8 */ s16 field_0x30c8;
    /* 0x030CA */ s16 field_0x30ca;
    /* 0x030CC */ s16 field_0x30cc;
    /* 0x030CE */ u16 field_0x30ce;
    /* 0x030D0 */ s16 field_0x30d0;
    /* 0x030D2 */ s16 field_0x30d2;
    /* 0x030D4 */ u16 field_0x30d4;
    /* 0x030D6 */ s16 field_0x30d6;
    /* 0x030D8 */ u8 field_0x30d8[0x14];
    /* 0x030EC */ s16 field_0x30ec;
    /* 0x030EE */ s16 field_0x30ee;
    /* 0x030F0 */ u16 field_0x30f0;
    /* 0x030F2 */ u8 field_0x30f2[2];
    /* 0x030F4 */ s16 mSwordFlourishTimer;
    /* 0x030F6 */ s16 field_0x30f6;
    /* 0x030F8 */ s16 field_0x30f8;
    /* 0x030FA */ s16 field_0x30fa;
    /* 0x030FC */ u16 field_0x30fc;
    /* 0x030FE */ u16 field_0x30fe;
    /* 0x03100 */ u16 field_0x3100;
    /* 0x03102 */ s16 field_0x3102;
    /* 0x03104 */ s16 field_0x3104;
    /* 0x03106 */ u16 field_0x3106;
    /* 0x03108 */ s16 field_0x3108;
    /* 0x0310A */ s16 field_0x310a;
    /* 0x0310C */ s16 field_0x310c;
    /* 0x0310E */ s16 field_0x310e;
    /* 0x03110 */ s16 field_0x3110;
    /* 0x03112 */ u16 field_0x3112;
    /* 0x03114 */ s16 field_0x3114;
    /* 0x03116 */ s16 field_0x3116;
    /* 0x03118 */ s16 field_0x3118;
    /* 0x0311A */ s16 field_0x311a;
    /* 0x0311C */ s16 field_0x311c;
    /* 0x0311E */ s16 field_0x311e;
    /* 0x03120 */ u16 mMidnaMsgNum;
    /* 0x03122 */ s16 field_0x3122;
    /* 0x03124 */ s16 field_0x3124;
    /* 0x03126 */ s16 field_0x3126;
    /* 0x03128 */ s16 field_0x3128;
    /* 0x0312A */ csXyz field_0x312a[2];
    /* 0x03136 */ csXyz field_0x3136[2];
    /* 0x03142 */ csXyz field_0x3142[4];
    /* 0x0315A */ csXyz field_0x315a;
    /* 0x03160 */ csXyz field_0x3160;
    /* 0x03166 */ csXyz field_0x3166;
    /* 0x0316C */ csXyz field_0x316c;
    /* 0x03172 */ u8 field_0x3172[2];
    /* 0x03174 */ int field_0x3174;
    /* 0x03178 */ int field_0x3178;
    /* 0x0317C */ int field_0x317c;
    /* 0x03180 */ int field_0x3180;
    /* 0x03184 */ int field_0x3184;
    /* 0x03184 */ int field_0x3188;
    /* 0x0318C */ int field_0x318c;
    /* 0x03190 */ int field_0x3190;
    /* 0x03194 */ int field_0x3194;
    /* 0x03198 */ int field_0x3198;
    /* 0x0319C */ int field_0x319c;
    /* 0x031A0 */ u32 mModeFlg;
    /* 0x031A4 */ int field_0x31a4;
    /* 0x031A8 */ u8 field_0x31a8[8];
    /* 0x031B0 */ int field_0x31b0;
    /* 0x031B4 */ u8 field_0x31b4[8];
    /* 0x031BC */ u32 field_0x31bc;
    /* 0x031C0 */ u32 field_0x31c0;
    /* 0x031C4 */ u32 field_0x31c4;
    /* 0x031C8 */ u32 field_0x31c8;
    /* 0x031CC */ u32 field_0x31cc;
    /* 0x031D0 */ u32 field_0x31d0;
    /* 0x031D4 */ u32 field_0x31d4;
    /* 0x031D8 */ u8 field_0x31d8[12];
    /* 0x031E4 */ u32 field_0x31e4;
    /* 0x031E8 */ u8 field_0x31e8[16];
    /* 0x031F8 */ u32 field_0x31f8;
    /* 0x031FC */ u32 field_0x31fc;
    /* 0x03200 */ u32 field_0x3200;
    /* 0x03204 */ u32 field_0x3204;
    /* 0x03208 */ u32 field_0x3208;
    /* 0x0320C */ u8 field_0x320c[16];
    /* 0x0321C */ u32 field_0x321c;
    /* 0x03220 */ u32 field_0x3220;
    /* 0x03224 */ u32 field_0x3224;
    /* 0x03228 */ u8 field_0x3228[24];
    /* 0x03240 */ u32 field_0x3240;
    /* 0x03244 */ u8 field_0x3244[20];
    /* 0x03258 */ u32 field_0x3258;
    /* 0x0325C */ u32 field_0x325c;
    /* 0x03260 */ u8 field_0x3260[40];
    /* 0x03288 */ u32 field_0x3288;
    /* 0x0328C */ u32 field_0x328c;
    /* 0x03290 */ u32 field_0x3290;
    /* 0x03294 */ u32 field_0x3294;
    /* 0x03298 */ u8 field_0x3298[8];
    /* 0x032A0 */ J3DGXColorS10 field_0x32a0[2];
    /* 0x032B0 */ J3DGXColorS10 field_0x32b0[2];
    /* 0x032C0 */ s16 field_0x32c0;
    /* 0x032C2 */ u8 field_0x32c2[2];
    /* 0x032C4 */ u16 field_0x32c4;
    /* 0x032C6 */ u16 field_0x32c6;
    /* 0x032C8 */ u32 field_0x32c8;
    /* 0x032CC */ u32 field_0x32cc;
    /* 0x032D0 */ u32 field_0x32d0;
    /* 0x032D4 */ u32 field_0x32d4;
    /* 0x032D8 */ firePointEff_c field_0x32d8[4];
    /* 0x03398 */ f32 mNormalSpeed;
    /* 0x0339C */ f32 mSpeedModifier;
    /* 0x033A0 */ f32 field_0x33a0;
    /* 0x033A4 */ f32 field_0x33a4;
    /* 0x033A8 */ f32 field_0x33a8;
    /* 0x033AC */ f32 field_0x33ac;
    /* 0x033B0 */ f32 field_0x33b0;
    /* 0x033B4 */ f32 mWaterY;
    /* 0x033B8 */ f32 field_0x33b8;
    /* 0x033BC */ f32 field_0x33bc;
    /* 0x033C0 */ f32 field_0x33c0;
    /* 0x033C4 */ f32 mFallHeight;
    /* 0x033C8 */ f32 field_0x33c8;
    /* 0x033CC */ f32 field_0x33cc;
    /* 0x033D0 */ f32 field_0x33d0;
    /* 0x033D4 */ f32 field_0x33d4;
    /* 0x033D8 */ f32 field_0x33d8;
    /* 0x033DC */ f32 field_0x33dc;
    /* 0x033E0 */ f32 field_0x33e0;
    /* 0x033E4 */ f32 field_0x33e4;
    /* 0x033E8 */ f32 field_0x33e8;
    /* 0x033EC */ f32 field_0x33ec;
    /* 0x033F0 */ f32 field_0x33f0;
    /* 0x033F4 */ f32 field_0x33f4;
    /* 0x033F8 */ f32 field_0x33f8;
    /* 0x033FC */ f32 field_0x33fc;
    /* 0x03400 */ f32 field_0x3400;
    /* 0x03404 */ f32 field_0x3404;
    /* 0x03408 */ f32 field_0x3408;
    /* 0x0340C */ f32 field_0x340c;
    /* 0x03410 */ f32 field_0x3410;
    /* 0x03414 */ f32 field_0x3414;
    /* 0x03418 */ f32 field_0x3418;
    /* 0x0341C */ f32 field_0x341c;
    /* 0x03420 */ f32 field_0x3420;
    /* 0x03424 */ f32 field_0x3424;
    /* 0x03428 */ f32 field_0x3428;
    /* 0x0342C */ f32 field_0x342c;
    /* 0x03430 */ f32 field_0x3430;
    /* 0x03434 */ f32 mHeavySpeedMultiplier;
    /* 0x03438 */ f32 field_0x3438;
    /* 0x0343C */ f32 field_0x343c;
    /* 0x03440 */ f32 field_0x3440;
    /* 0x03444 */ f32 field_0x3444;
    /* 0x03448 */ f32 field_0x3448;
    /* 0x0344C */ f32 field_0x344c;
    /* 0x03450 */ u8 field_0x3450[4];
    /* 0x03454 */ f32 field_0x3454;
    /* 0x03458 */ f32 field_0x3458;
    /* 0x0345C */ f32 field_0x345c;
    /* 0x03460 */ f32 field_0x3460;
    /* 0x03464 */ f32 field_0x3464;
    /* 0x03468 */ f32 field_0x3468;
    /* 0x0346C */ f32 field_0x346c;
    /* 0x03470 */ f32 field_0x3470;
    /* 0x03474 */ f32 mSwordUpColorIntensity;
    /* 0x03478 */ f32 field_0x3478;
    /* 0x0347C */ f32 field_0x347c;
    /* 0x03480 */ f32 field_0x3480;
    /* 0x03484 */ f32 field_0x3484;
    /* 0x03488 */ f32 field_0x3488;
    /* 0x0348C */ f32 field_0x348c;
    /* 0x03490 */ f32 mSearchBallScale;
    /* 0x03494 */ f32 field_0x3494;
    /* 0x03498 */ cXyz field_0x3498;
    /* 0x034A4 */ cXyz field_0x34a4;
    /* 0x034B0 */ cXyz field_0x34b0;
    /* 0x034BC */ cXyz field_0x34bc;
    /* 0x034C8 */ cXyz field_0x34c8;
    /* 0x034D4 */ cXyz field_0x34d4;
    /* 0x034E0 */ cXyz field_0x34e0;
    /* 0x034EC */ cXyz field_0x34ec;
    /* 0x034F8 */ cXyz mLastJumpPos;
    /* 0x03504 */ cXyz field_0x3504;
    /* 0x03510 */ cXyz field_0x3510;
    /* 0x0351C */ cXyz field_0x351c;
    /* 0x03528 */ cXyz field_0x3528;
    /* 0x03534 */ cXyz field_0x3534;
    /* 0x03540 */ cXyz field_0x3540;
    /* 0x0354C */ cXyz field_0x354c[4];
    /* 0x0357C */ cXyz mLookPosFromOut;
    /* 0x03588 */ cXyz field_0x3588;
    /* 0x03594 */ cXyz field_0x3594;
    /* 0x035A0 */ cXyz field_0x35a0;
    /* 0x035AC */ cXyz field_0x35ac;
    /* 0x035B8 */ cXyz field_0x35b8;
    /* 0x035C4 */ cXyz field_0x35c4;
    /* 0x035D0 */ cXyz field_0x35d0;
    /* 0x035DC */ cXyz field_0x35dc;
    /* 0x035E8 */ cXyz field_0x35e8;
    /* 0x035F4 */ cXyz mMidnaAtnPos;
    /* 0x03600 */ cXyz field_0x3600;
    /* 0x0360C */ cXyz field_0x360c;
    /* 0x03618 */ cXyz field_0x3618;
    /* 0x03624 */ cXyz field_0x3624;
    /* 0x03630 */ cXyz field_0x3630;
    /* 0x0363C */ cXyz field_0x363c[4];
    /* 0x0366C */ cXyz field_0x366c[4];
    /* 0x0369C */ cXyz field_0x369c;
    /* 0x036A8 */ cXyz mMagneBootsTopVec;
    /* 0x036B4 */ cXyz field_0x36b4;
    /* 0x036C0 */ cXyz field_0x36c0[4];
    /* 0x036F0 */ cXyz field_0x36f0[4];
    /* 0x03720 */ cXyz field_0x3720;
    /* 0x0372C */ cXyz field_0x372c;
    /* 0x03738 */ cXyz field_0x3738;
    /* 0x03744 */ cXyz field_0x3744;
    /* 0x03750 */ cXyz field_0x3750;
    /* 0x0375C */ cXyz field_0x375c;
    /* 0x03768 */ cXyz field_0x3768;
    /* 0x03774 */ cXyz mForcePutPos;
    /* 0x03780 */ cXyz field_0x3780;
    /* 0x0378C */ cXyz field_0x378c;
    /* 0x03798 */ cXyz field_0x3798;
    /* 0x037A4 */ cXyz field_0x37a4;
    /* 0x037B0 */ cXyz field_0x37b0[2];
    /* 0x037C8 */ cXyz field_0x37c8;
    /* 0x037D4 */ cXyz field_0x37d4;
    /* 0x037E0 */ cXyz field_0x37e0;
    /* 0x037EC */ cXyz field_0x37ec;
    /* 0x037F8 */ cXyz field_0x37f8;
    /* 0x03804 */ cXyz field_0x3804;
    /* 0x03810 */ cXyz field_0x3810;
    /* 0x0381C */ cXyz field_0x381c;
    /* 0x03828 */ cXyz field_0x3828;
    /* 0x03834 */ cXyz field_0x3834;
    /* 0x03840 */ cXyz* mIronBallChainPos;
    /* 0x03844 */ csXyz* mIronBallChainAngle;
    /* 0x03848 */ void* field_0x3848;
    /* 0x0384C */ f32* field_0x384c;
    /* 0x03850 */ u32 field_0x3850;
    /* 0x03854 */ u32 field_0x3854;
    /* 0x03858 */ u32 field_0x3858;
};

struct daAlinkHIO_anm_c {
    /* 0x00 */ s16 field_0x00;  // end f?
    /* 0x04 */ f32 field_0x04;    // speed?
    /* 0x08 */ f32 field_0x08;    // start?
    /* 0x0C */ f32 field_0x0c;    // interpolation?
    /* 0x10 */ f32 field_0x10;    // CF?
};                                  // size = 0x14

struct daAlinkHIO_basic_c1 {
    /* 0x00 */ bool mOneHitKill;
    /* 0x02 */ s16 mNeckMaxHorizontal;
    /* 0x04 */ s16 mNeckMaxUp;
    /* 0x06 */ s16 mNeckMaxDown;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 mHotspringRecoverTime;
    /* 0x0C */ s16 mWiiCamSpeedV;
    /* 0x0E */ s16 mWiiCamSpeedH;
    /* 0x10 */ s16 mTransformBlockFarAngle;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 mAnmBlendFactor;
    /* 0x1C */ f32 mWaitTurnSpeed;
    /* 0x20 */ f32 mStandDefenseBlend;
    /* 0x24 */ f32 mWaterSurfaceEffectHeight;
    /* 0x28 */ f32 mWolfWaterSurfaceEffectHeight;
    /* 0x2C */ f32 mMaxWindInfluenceDist;
    /* 0x30 */ f32 mNoWindInfluenceDist;
    /* 0x34 */ f32 mMaxWindSpeed;
    /* 0x38 */ f32 mLavaDeathDepth;
    /* 0x3C */ f32 mLinkWolfTransformSpeed;
    /* 0x40 */ f32 mWolfLinkTransformSpeed;
    /* 0x44 */ f32 mIndoorSpeedFactor;
    /* 0x48 */ f32 mSandSinkSpeed;
    /* 0x4C */ f32 mSandSurfaceSpeed;
    /* 0x50 */ f32 mTransformBlockNearDis;
    /* 0x54 */ f32 mTransformBlockFarDis;
};

class daAlinkHIO_backJump_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
};  // Size: 0x38

class daAlinkHIO_autoJump_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mJump;
    /* 0x14 */ daAlinkHIO_anm_c mLand;
    /* 0x28 */ daAlinkHIO_anm_c mDive;
    /* 0x3C */ daAlinkHIO_anm_c mDiveUnk;
    /* 0x50 */ u8 field_0x50;
    /* 0x52 */ s16 field_0x52;
    /* 0x54 */ s16 field_0x54;
    /* 0x56 */ s16 field_0x56;
    /* 0x58 */ s16 field_0x58;
    /* 0x5C */ f32 field_0x5c;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6c;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 mGravity;
    /* 0x78 */ f32 mMaxFallSpeed;
    /* 0x7C */ f32 field_0x7c;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
    /* 0x8C */ f32 field_0x8c;
    /* 0x90 */ f32 field_0x90;
    /* 0x94 */ f32 field_0x94;
    /* 0x98 */ f32 field_0x98;
    /* 0x9C */ f32 field_0x9c;
    /* 0xA0 */ f32 field_0xa0;
    /* 0xA4 */ f32 field_0xa4;
    /* 0xA8 */ f32 field_0xa8;
    /* 0xAC */ f32 field_0xac;
    /* 0xB0 */ f32 field_0xb0;
};  // Size: 0xB4

class daAlinkHIO_smallJump_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
};  // Size: 0x48

class daAlinkHIO_cut_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mEquipAnm;
    /* 0x14 */ daAlinkHIO_anm_c mReleaseAnm;
    /* 0x28 */ daAlinkHIO_anm_c mRecoilAnm;
    /* 0x3C */ daAlinkHIO_anm_c mStabAnm;
    /* 0x50 */ bool mForceHitCombo;
    /* 0x52 */ s16 mComboDuration;
    /* 0x54 */ s16 mBlurAlpha;
    /* 0x56 */ s16 mNormalSwingDuration;
    /* 0x58 */ s16 mDashBlurAlpha;
    /* 0x5A */ s16 mUnkTime;  // might be related to flourish
    /* 0x5C */ s16 mFlourishTime;
    /* 0x5E */ s16 mUnkBodyDownwards;  // ?
    /* 0x60 */ s16 mUnkBodyUpwards;    // ?
    /* 0x62 */ s16 mSpinSlashWait;     // ? maybe related to wii?
    /* 0x64 */ f32 mRecoilSpeed;
    /* 0x68 */ f32 mRecoilDeceleration;
    /* 0x6C */ f32 mFlourishAnmSpeed;
    /* 0x70 */ f32 mFlourishEndAnmSpeed;
    /* 0x74 */ f32 mSwordLength;
    /* 0x78 */ f32 mSwordRadius;
    /* 0x7C */ f32 mSwordLengthHorseback;
    /* 0x80 */ f32 mSwordRadiusHorseback;
    /* 0x84 */ f32 mRunCutLength;
    /* 0x88 */ f32 mRunCutRadius;
    /* 0x8C */ f32 mUnkReleaseASpeed;
    /* 0x90 */ f32 mSwordLengthHorsebackFight;
    /* 0x94 */ f32 mSwordRadiusHorsebackFight;
    /* 0x98 */ f32 mFlourishControlStartFrame;
};  // Size: 0x9C

class daAlinkHIO_cutTurn_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
    /* 0x8C */ f32 field_0x8C;
    /* 0x90 */ f32 field_0x90;
    /* 0x94 */ f32 field_0x94;
};  // Size: 0x98

class daAlinkHIO_cutJump_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mCutAnm;
    /* 0x14 */ daAlinkHIO_anm_c mLandAnm;
    /* 0x28 */ f32 mBaseJumpSpeedH;
    /* 0x2C */ f32 mBaseJumpSpeedV;
    /* 0x30 */ f32 mAirJumpSpeedH;
    /* 0x34 */ f32 mAirJumpSpeedV;
    /* 0x38 */ f32 mStartAttackFrame;
    /* 0x3C */ f32 mEndAttackFrame;
    /* 0x40 */ f32 mJumpSpinDelay;
};  // Size: 0x44

class daAlinkHIO_cutLargeJump_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mChargeAnm;      // ?
    /* 0x14 */ daAlinkHIO_anm_c mChargeMoveAnm;  // ?
    /* 0x28 */ daAlinkHIO_anm_c mCutAnm;
    /* 0x3C */ daAlinkHIO_anm_c mLandAnm;
    /* 0x50 */ f32 mCutSpeedH;
    /* 0x54 */ f32 mCutSpeedV;
    /* 0x58 */ f32 mJumpAttackStartF;
    /* 0x5C */ f32 mJumpAttackEndF;
    /* 0x60 */ f32 mCutInitF;
    /* 0x64 */ f32 mLandAttackInitF;
    /* 0x68 */ f32 mLandAttackEndF;
    /* 0x6C */ f32 mLandAttackRadius;
    /* 0x70 */ f32 mSpinSlashUnkCF;
};  // Size: 0x74

class daAlinkHIO_cutNmV_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daAlinkHIO_cutNmSR_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daAlinkHIO_cutNmSL_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daAlinkHIO_cutNmR_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daAlinkHIO_cutNmL_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daAlinkHIO_cutHead_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
};  // Size: 0x60

class daAlinkHIO_cutFnV_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
};  // Size: 0x2C

class daAlinkHIO_cutFnSm_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
};  // Size: 0x2C

class daAlinkHIO_cutFnSl_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
};  // Size: 0x2C

class daAlinkHIO_cutFnS_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
};  // Size: 0x2C

class daAlinkHIO_cutFnR_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
};  // Size: 0x2C

class daAlinkHIO_cutFnL_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
};  // Size: 0x2C

class daAlinkHIO_cutFnJU_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
};  // Size: 0x54

class daAlinkHIO_cutDown_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ daAlinkHIO_anm_c field_0x50;
    /* 0x64 */ s16 field_0x64;
    /* 0x66 */ s16 field_0x66;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
};  // Size: 0x74

class daAlinkHIO_cutDaR_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daAlinkHIO_cutDaL_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daAlinkHIO_cutDaCharge_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daAlinkHIO_move_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mSlideAnm;
    /* 0x14 */ s16 mMaxTurnAngle;
    /* 0x16 */ s16 mMinTurnAngle;
    /* 0x18 */ s16 mTurnAngleRate;
    /* 0x1C */ f32 mWaitAnmSpeed;
    /* 0x20 */ f32 mWalkAnmSpeed;
    /* 0x24 */ f32 mRunAnmSpeed;
    /* 0x28 */ f32 mWalkChangeRate;
    /* 0x2C */ f32 mRunChangeRate;
    /* 0x30 */ f32 mMaxSpeed;
    /* 0x34 */ f32 mAcceleration;
    /* 0x38 */ f32 mDeceleration;
    /* 0x3C */ f32 mSlideThresholdSpeed;  // speed needed to trigger a slide
    /* 0x40 */ f32 mSlideSpeed;
    /* 0x44 */ f32 mSlideDeceleration;
    /* 0x48 */ f32 mFootPositionRatio;
    /* 0x4C */ f32 mUnkInterpolation;
    /* 0x50 */ f32 mMinWalkFrame;
    /* 0x54 */ f32 mMinTiredWalkFrame;
};  // Size: 0x58

class daAlinkHIO_sideStep_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mSideJumpAnm;
    /* 0x14 */ daAlinkHIO_anm_c mSideLandAnm;
    /* 0x28 */ daAlinkHIO_anm_c mBackJumpAnm;
    /* 0x3C */ daAlinkHIO_anm_c mBackLandAnm;
    /* 0x50 */ f32 mSideJumpSpeedH;
    /* 0x54 */ f32 mSideJumpSpeedV;
    /* 0x58 */ f32 mBackJumpSpeedH;
    /* 0x5C */ f32 mBackJumpSpeedV;
    /* 0x60 */ f32 mFallHeight;
    /* 0x64 */ f32 mFallInterpolation;
};  // Size: 0x68

class daAlinkHIO_atnMove_c1 {
public:
    /* 0x00 */ s16 mMaxTurnAngle;
    /* 0x02 */ s16 mMinTurnAngle;
    /* 0x04 */ s16 mTurnAngleRate;
    /* 0x08 */ f32 mWaitAnmSpeed;
    /* 0x0C */ f32 mWalkAnmSpeed;
    /* 0x10 */ f32 mRunAnmSpeed;
    /* 0x14 */ f32 mWalkChangeRate;
    /* 0x18 */ f32 mRunChangeRate;
    /* 0x1C */ f32 mMaxSpeed;
    /* 0x20 */ f32 mAcceleration;
    /* 0x24 */ f32 mDeceleration;
    /* 0x28 */ f32 mBackWalkAnmSpeed;
    /* 0x2C */ f32 mBackRunAnmSpeed;
    /* 0x30 */ f32 mBackWalkChangeRate;
    /* 0x34 */ f32 mBackRunChangeRate;
    /* 0x38 */ f32 mMaxBackwardsSpeed;
    /* 0x3C */ f32 mBackAcceleration;
    /* 0x40 */ f32 mBackDeceleration;
    /* 0x44 */ f32 mMinWalkFrame;
    /* 0x48 */ f32 mMinBackWalkFrame;
    /* 0x4C */ f32 mWalkForwardAnmSpeed;
    /* 0x50 */ f32 mRunForwardAnmSpeed;
};  // Size: 0x54

class daAlinkHIO_noActAtnMove_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
};  // Size: 0x54

class daAlinkHIO_wallMove_c1 {
public:
    /* 0x00 */ f32 mMinAnmSpeed;
    /* 0x04 */ f32 mMaxAnmSpeed;
    /* 0x08 */ f32 mInterpolation;
    /* 0x0C */ f32 mMinSpeed;
    /* 0x10 */ f32 mMaxSpeed;
};

class daAlinkHIO_turnMove_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mTurnAnm;
    /* 0x14 */ s16 mTurnSpeedRate;
    /* 0x16 */ s16 mMaxTurnSpeed;
    /* 0x18 */ s16 mMinTurnSpeed;
    /* 0x1A */ s16 mMaxHalfTurnSpeed;
    /* 0x1C */ f32 mHalfTurnAnmSpeed;
    /* 0x20 */ f32 mTwirlCutDelayF;
    /* 0x24 */ f32 mSideRollAnmSpeed;
    /* 0x28 */ f32 mSideRollSpeed;
};  // Size: 0x2C

class daAlinkHIO_slide_c1 {
public:
    // most of these havent been verified yet
    /* 0x00 */ daAlinkHIO_anm_c mForwardSlideAnm;
    /* 0x14 */ daAlinkHIO_anm_c mBackwardSlideAnm;
    /* 0x28 */ daAlinkHIO_anm_c mForwardLandAnm;  // this and 0x3C might have names reversed?
    /* 0x3C */ daAlinkHIO_anm_c mBackwardLandAnm;
    /* 0x50 */ f32 mMaxSpeed;
    /* 0x54 */ f32 mAcceleration;
    /* 0x58 */ f32 mSlideAngle;
    /* 0x5C */ f32 mClimbAngle;
    /* 0x60 */ f32 mClimbAnmMinSpeed;
    /* 0x64 */ f32 mMaxClimbSpeed;
    /* 0x68 */ f32 mLavaFloorSlideAngle;      // ?
    /* 0x6C */ f32 mLavaFloorWeakSlideAngle;  // ?
    /* 0x70 */ f32 mLavaFloorWeakSlideSpeed;
    /* 0x74 */ f32 mMaxClimbAnmSpeed;
};  // Size: 0x78

class daAlinkHIO_frontRoll_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mRollAnm;
    /* 0x14 */ daAlinkHIO_anm_c mCrashAnm;
    /* 0x28 */ daAlinkHIO_anm_c mCrashHitAnm;  // ?
    /* 0x3C */ s16 mCrashAngleThreshold;
    /* 0x3E */ s16 mTurnRate;
    /* 0x40 */ s16 mTurnMaxAngle;
    /* 0x42 */ s16 mTurnMinAngle;
    /* 0x44 */ f32 mInitSpeed;
    /* 0x48 */ f32 mSpeedRate;
    /* 0x4C */ f32 mMinSpeed;
    /* 0x50 */ f32 mCrashSpeedThreshold;
    /* 0x54 */ f32 mCrashInitF;
    /* 0x58 */ f32 mCrashEndF;
    /* 0x5C */ f32 mCrashSpeedH;
    /* 0x60 */ f32 mCrashSpeedV;
    /* 0x64 */ f32 mBootsAttackInitF;
    /* 0x68 */ f32 mBootsAttackEndF;
    /* 0x6C */ f32 mBootsAttackRadius;
};  // Size: 0x70

class daAlinkHIO_swim_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mResurfaceAnm;
    /* 0x14 */ daAlinkHIO_anm_c mDiveAnm;
    /* 0x28 */ daAlinkHIO_anm_c mUnderwaterDiveAnm;
    /* 0x3C */ daAlinkHIO_anm_c mDashAnm;
    /* 0x50 */ s16 mTurnRate;
    /* 0x52 */ s16 mTurnMin;
    /* 0x54 */ s16 mTurnMax;
    /* 0x56 */ s16 mUnderwaterTurnRate;
    /* 0x58 */ s16 mUnderwaterTurnMin;
    /* 0x5A */ s16 mUnderwaterTurnMax;
    /* 0x5C */ s16 val1a;   // related to dash
    /* 0x5E */ s16 val1a_;  // related to dash
    /* 0x60 */ f32 mInitHeight;
    /* 0x64 */ f32 mResurfaceHeight;
    /* 0x68 */ f32 mMaxForwardSpeed;
    /* 0x6C */ f32 mMaxStrafeSpeed;
    /* 0x70 */ f32 mMaxBackwardSpeed;
    /* 0x74 */ f32 mMaxUnderwaterSpeed;
    /* 0x78 */ f32 mUnderwaterMaxSinkSpeed;
    /* 0x7C */ f32 mAcceleration;
    /* 0x80 */ f32 mDeceleration;
    /* 0x84 */ f32 mMaxSinkSpeed;
    /* 0x88 */ f32 mMaxFloatUpSpeed;
    /* 0x8C */ f32 mBuoyancy;  // ?
    /* 0x90 */ f32 mWaitAnmSpeed;
    /* 0x94 */ f32 mWaitInterpolation;
    /* 0x98 */ f32 mWaitVibrationIntensity;
    /* 0x9C */ f32 mForwardMinAnmSpeed;
    /* 0xA0 */ f32 mForwardMaxAnmSpeed;
    /* 0xA4 */ f32 mStrafeMinAnmSpeed;
    /* 0xA8 */ f32 mStrafeMaxAnmSpeed;
    /* 0xAC */ f32 mBackwardMinAnmSpeed;
    /* 0xB0 */ f32 mBackwardMaxAnmSpeed;
    /* 0xB4 */ f32 mUnderwaterMinAnmSpeed;
    /* 0xB8 */ f32 mUnderwaterMaxAnmSpeed;
    /* 0xBC */ f32 mMoveInterpolation;
    /* 0xC0 */ f32 mClimbHeight;
    /* 0xC4 */ f32 mUnderwaterClimbHeight;
    /* 0xC8 */ f32 mForwardMinSpeed;
    /* 0xCC */ f32 mInitMaxSinkSpeed;
    /* 0xD0 */ f32 mBootsMaxSinkSpeed;
    /* 0xD4 */ f32 mNormalFloatDepth;
    /* 0xD8 */ f32 mZoraFloatDepth;
    /* 0xDC */ f32 mUnderwaterButtonSpeed;
    /* 0xE0 */ f32 mUnderwaterButtonAnmSpeed;  // ?
    /* 0xE4 */ f32 mBootsGravity;
    /* 0xE8 */ f32 mSurfaceSwimSpeedRate;
    /* 0xEC */ f32 mDashMaxSpeed;  // ?
    /* 0xF0 */ f32 mDashDeceleration;
    /* 0xF4 */ f32 mDashMinAnmSpeed;
    /* 0xF8 */ f32 mDashMaxAnmSpeed;
};  // Size: 0xFC

class daAlinkHIO_ladder_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
};  // Size: 0x70

class daAlinkHIO_wallHang_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daAlinkHIO_wallFall_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
};  // Size: 0x28

class daAlinkHIO_wallCatch_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ f32 field_0x50;
};  // Size: 0x54

class daAlinkHIO_roofHang_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
};  // Size: 0x4C

class daAlinkHIO_pushpull_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ s16 field_0xC;
    /* 0x0E */ s16 field_0xE;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
};  // Size: 0x3C

class daAlinkHIO_pickUp_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
};  // Size: 0x30

class daAlinkHIO_crouch_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2A;
    /* 0x2C */ s16 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
};  // Size: 0x4C

class daAlinkHIO_canoe_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
};  // Size: 0x48

class daAlinkHIO_horse_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ s16 field_0x50;
    /* 0x52 */ s16 field_0x52;
    /* 0x54 */ s16 field_0x54;
    /* 0x56 */ s16 field_0x56;
    /* 0x58 */ s16 field_0x58;
    /* 0x5A */ s16 field_0x5A;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
};  // Size: 0x6C

class daAlinkHIO_huLight_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daAlinkHIO_hoCutRA_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daAlinkHIO_hoCutRB_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daAlinkHIO_hoCutLA_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daAlinkHIO_hoCutLB_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daAlinkHIO_hoCutCharge_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ s16 field_0x3E;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
};  // Size: 0x54

class daAlinkHIO_guard_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ s16 field_0x50;
    /* 0x52 */ s16 field_0x52;
    /* 0x54 */ s16 field_0x54;
    /* 0x56 */ s16 field_0x56;
    /* 0x58 */ s16 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
};  // Size: 0x80

class daAlinkHIO_grab_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ daAlinkHIO_anm_c field_0x50;
    /* 0x64 */ daAlinkHIO_anm_c field_0x64;
    /* 0x78 */ daAlinkHIO_anm_c field_0x78;
    /* 0x8C */ daAlinkHIO_anm_c field_0x8C;
    /* 0xA0 */ daAlinkHIO_anm_c field_0xA0;
    /* 0xB4 */ daAlinkHIO_anm_c field_0xB4;
    /* 0xC8 */ daAlinkHIO_anm_c field_0xC8;
    /* 0xDC */ s16 field_0xDC;
    /* 0xDE */ s16 field_0xDE;
    /* 0xE0 */ f32 field_0xE0;
};  // Size: 0xE4

class daAlinkHIO_gAtPush_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
};  // Size: 0x24

class daAlinkHIO_gAtKick_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
};  // Size: 0x24

class daAlinkHIO_fmChain_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
};  // Size: 0x28

class daAlinkHIO_damage_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2A;
    /* 0x2C */ s16 field_0x2C;
    /* 0x2E */ s16 field_0x2E;
    /* 0x30 */ s16 field_0x30;
    /* 0x32 */ s16 field_0x32;
    /* 0x34 */ s16 field_0x34;
    /* 0x36 */ s16 field_0x36;
    /* 0x38 */ s16 field_0x38;
    /* 0x3A */ s16 field_0x3A;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ s16 field_0x3E;
    /* 0x40 */ s16 field_0x40;
    /* 0x42 */ s16 field_0x42;
    /* 0x44 */ s16 field_0x44;
    /* 0x46 */ s16 field_0x46;
    /* 0x48 */ s16 field_0x48;
    /* 0x4A */ s16 field_0x4A;
    /* 0x4C */ s16 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
};  // Size: 0x58

class daAlinkHIO_damNormal_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ s16 field_0x50;
    /* 0x52 */ s16 field_0x52;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
};  // Size: 0x64

class daAlinkHIO_damLarge_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ daAlinkHIO_anm_c field_0x50;
    /* 0x64 */ daAlinkHIO_anm_c field_0x64;
    /* 0x78 */ daAlinkHIO_anm_c field_0x78;
    /* 0x8C */ daAlinkHIO_anm_c field_0x8C;
    /* 0xA0 */ s16 field_0xA0;
    /* 0xA4 */ f32 field_0xA4;
    /* 0xA8 */ f32 field_0xA8;
    /* 0xAC */ f32 field_0xAC;
    /* 0xB0 */ f32 field_0xB0;
    /* 0xB4 */ f32 field_0xB4;
    /* 0xB8 */ f32 field_0xB8;
};  // Size: 0xBC

class daAlinkHIO_damHuge_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ daAlinkHIO_anm_c field_0x50;
    /* 0x64 */ daAlinkHIO_anm_c field_0x64;
    /* 0x78 */ daAlinkHIO_anm_c field_0x78;
    /* 0x8C */ daAlinkHIO_anm_c field_0x8C;
    /* 0xA0 */ s16 field_0xA0;
    /* 0xA4 */ f32 field_0xA4;
    /* 0xA8 */ f32 field_0xA8;
    /* 0xAC */ f32 field_0xAC;
    /* 0xB0 */ f32 field_0xB0;
    /* 0xB4 */ f32 field_0xB4;
    /* 0xB8 */ f32 field_0xB8;
};  // Size: 0xBC

class daAlinkHIO_damHorse_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2A;
};  // Size: 0x2C

class daAlinkHIO_damFall_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2A;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
};  // Size: 0x48

class daAlinkHIO_damSwim_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ daAlinkHIO_anm_c field_0x50;
    /* 0x64 */ daAlinkHIO_anm_c field_0x64;
    /* 0x78 */ s16 field_0x78;
    /* 0x7A */ s16 field_0x7A;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
};  // Size: 0x8C

class daAlinkHIO_damCaught_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
};  // Size: 0x24

class daAlinkHIO_wolf_c1 {
public:
    /* 0x00 */ s16 mMaxNeckTurnH;
    /* 0x02 */ s16 mMaxNeckTurnUp;
    /* 0x04 */ s16 mMaxNeckTurnDown;
    /* 0x06 */ s16 mMaxTiredNeckTurnH;
    /* 0x08 */ s16 mMaxTiredNeckTurnUp;
    /* 0x0A */ s16 mMaxTiredNeckTurnDown;
    /* 0x0C */ s16 mSensesLingerTime;  // ?
    /* 0x0E */ s16 mLightDropR;
    /* 0x10 */ s16 mLightDropG;
    /* 0x12 */ s16 mLightDropB;
    /* 0x14 */ f32 mSwampInputRate;  // ?
};                                     // Size: 0x18

class daAlinkHIO_wlMove_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mSlipAnm;
    /* 0x14 */ daAlinkHIO_anm_c mRollOverAnm;
    /* 0x28 */ daAlinkHIO_anm_c mDashAnm;
    /* 0x3C */ daAlinkHIO_anm_c mDashBounceAnm;
    /* 0x50 */ s16 mTurnMax;
    /* 0x52 */ s16 mTurnMin;
    /* 0x54 */ s16 mRotateAngleRate;
    /* 0x56 */ s16 mDashTime;
    /* 0x58 */ s16 mDashWaitTime;
    /* 0x5A */ s16 mDashTimeSlow;
    /* 0x5C */ s16 mDashWaitTimeSlow;
    /* 0x5E */ s16 mDashTimeSlow2;
    /* 0x60 */ s16 mDashWaitTimeSlow2;
    /* 0x64 */ f32 mMaxSpeed;
    /* 0x68 */ f32 mAcceleration;
    /* 0x6C */ f32 mDeceleration;
    /* 0x70 */ f32 mIdleAnmSpeed;
    /* 0x74 */ f32 mWalkAnmSpeed;
    /* 0x78 */ f32 mFastWalkAnmSpeed;
    /* 0x7C */ f32 mRunAnmSpeed;
    /* 0x80 */ f32 mFastRunAnmSpeed;
    /* 0x84 */ f32 mWalkTransitionRate;
    /* 0x88 */ f32 mFastWalkTransitionRate;
    /* 0x8C */ f32 mRunTransitionRate;
    /* 0x90 */ f32 mFastRunTransitionRate;
    /* 0x94 */ f32 mNormalInterpolation;
    /* 0x98 */ f32 mWalkRunInterpolation;
    /* 0x9C */ f32 mRunAnmMinUnit;
    /* 0xA0 */ f32 mSlideInitRate;
    /* 0xA4 */ f32 mSlideInitSpeed;
    /* 0xA8 */ f32 mSlideDeceleration;
    /* 0xAC */ f32 mRollOverSpeed;
    /* 0xB0 */ f32 mStartRollOverF;
    /* 0xB4 */ f32 field_0xB4;
    /* 0xB8 */ f32 field_0xB8;
    /* 0xBC */ f32 mIdleInterpolation;
    /* 0xC0 */ f32 mRollOverFallHeight;
    /* 0xC4 */ f32 mRollOverFallInterpolation;
    /* 0xC8 */ f32 mDashMaxSpeed;
    /* 0xCC */ f32 mDashRunAnmSpeed;
    /* 0xD0 */ f32 mDashAcceleration;
    /* 0xD4 */ f32 mDashInitSpeed;
    /* 0xD8 */ f32 mDashSideBounceSpeed;
    /* 0xDC */ f32 mDashTopBounceSpeed;
    /* 0xE0 */ f32 mDashMaxSpeedSlow;
    /* 0xE4 */ f32 mDashInitSpeedSlow;
    /* 0xE8 */ f32 mDashRunAnmSpeedSlow;
    /* 0xEC */ f32 mDashAccelSlow;
    /* 0xF0 */ f32 mDashMaxSpeedSlow2;
    /* 0xF4 */ f32 mDashInitSpeedSlow2;
    /* 0xF8 */ f32 mDashRunAnmSpeedSlow2;
    /* 0xFC */ f32 mDashAccelSlow2;
};  // Size: 0x100

class daAlinkHIO_wlMoveNoP_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
};  // Size: 0x48

class daAlinkHIO_wlAtnMove_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
};  // Size: 0x38

class daAlinkHIO_wlAutoJump_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x00;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ u8 field_0x3c;
    /* 0x3E */ s16 field_0x3e;
    /* 0x40 */ s16 field_0x40;
    /* 0x42 */ s16 field_0x42;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4c;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5c;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6c;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
};  // size = 0x7C

class daAlinkHIO_wlSlide_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ s16 field_0x50;
    /* 0x52 */ s16 field_0x52;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
};  // Size: 0x7C

class daAlinkHIO_wlSideStep_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
};  // Size: 0x68

class daAlinkHIO_wlBackJump_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
};  // Size: 0x38

class daAlinkHIO_wlRope_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
};  // Size: 0x38

class daAlinkHIO_wlPush_c1 {
public:
    /* 0x00 */ f32 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
};  // Size: 0x14

class daAlinkHIO_wlPoint_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ daAlinkHIO_anm_c field_0x50;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
};  // Size: 0x7C

class daAlinkHIO_wlWallHang_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ daAlinkHIO_anm_c field_0x50;
    /* 0x64 */ daAlinkHIO_anm_c field_0x64;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
    /* 0x8C */ f32 field_0x8C;
    /* 0x90 */ f32 field_0x90;
    /* 0x94 */ f32 field_0x94;
    /* 0x98 */ f32 field_0x98;
};  // Size: 0x9C

class daAlinkHIO_wlSwim_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mSurfaceAnm;
    /* 0x14 */ daAlinkHIO_anm_c mWaterShakeAnm;
    /* 0x28 */ daAlinkHIO_anm_c mDashAnm;
    /* 0x3C */ s16 mTurnRate;
    /* 0x3E */ s16 mTurnMin;
    /* 0x40 */ s16 mTurnMax;
    /* 0x42 */ s16 mWaitTurnRate;
    /* 0x44 */ s16 mWaitTurnMin;
    /* 0x46 */ s16 mWaitTurnMax;
    /* 0x48 */ f32 mStartHeight;
    /* 0x4C */ f32 mSurfaceHeight;
    /* 0x50 */ f32 mMaxSpeed;
    /* 0x54 */ f32 mDeceleration;
    /* 0x58 */ f32 mMaxFallSpeed;
    /* 0x5C */ f32 mMaxRiseSpeed;
    /* 0x60 */ f32 mBuoyancy;
    /* 0x64 */ f32 mIdleAnmSpeed;
    /* 0x68 */ f32 mIdleInterpolation;
    /* 0x6C */ f32 mIdleOscillationAmount;
    /* 0x70 */ f32 mMoveAnmSpeedMin;
    /* 0x74 */ f32 mMoveAnmSpeedMax;
    /* 0x78 */ f32 mMoveInterpolation;
    /* 0x7C */ f32 mClimbHeight;
    /* 0x80 */ f32 mMaxSpeedWeak;
    /* 0x84 */ f32 mDecelerationWeak;
    /* 0x88 */ f32 mIdleAnmSpeedWeak;
    /* 0x8C */ f32 mMoveAnmSpeedMinWeak;
    /* 0x90 */ f32 mMoveAnmSpeedMaxWeak;
    /* 0x94 */ f32 mUnderwaterClimb;
    /* 0x98 */ f32 field_0x98;
    /* 0x9C */ f32 field_0x9C;
    /* 0xA0 */ f32 field_0xA0;
    /* 0xA4 */ f32 field_0xA4;
};  // Size: 0xA8

class daAlinkHIO_wlAttack_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mLandAnm;
    /* 0x14 */ s16 mUnkTime;
    /* 0x16 */ s16 mComboDuration;
    /* 0x18 */ f32 mFallHeight;
    /* 0x1C */ f32 mFallInterpolation;
    /* 0x20 */ f32 mReadyInterpolation;
    /* 0x24 */ f32 mAttackRange;
    /* 0x28 */ f32 mJumpBackSpeedH;
    /* 0x2C */ f32 mJumpBackSpeedV;
    /* 0x30 */ f32 mJumpAttackSpeedV;
    /* 0x34 */ f32 mJumpAttackSpeedH;
};  // Size: 0x38

class daAlinkHIO_wlHowl_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
};  // Size: 0x60

class daAlinkHIO_wlGrab_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ daAlinkHIO_anm_c field_0x50;
};  // Size: 0x64

class daAlinkHIO_wlChain_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ s16 field_0x3E;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
};  // Size: 0x5C

class daAlinkHIO_wlBall_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ s16 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
};  // Size: 0x38

class daAlinkHIO_wlLie_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2A;
    /* 0x2C */ s16 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
};  // Size: 0x4C

class daAlinkHIO_wlLight_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daAlinkHIO_wlAtWaTl_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
};  // Size: 0x3C

class daAlinkHIO_wlAtWaSc_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
};  // Size: 0x3C

class daAlinkHIO_wlAtWaLr_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
};  // Size: 0x3C

class daAlinkHIO_wlAtRoll_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daAlinkHIO_wlAtNjump_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
};  // Size: 0x3C

class daAlinkHIO_wlAtLock_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
};  // Size: 0x54

class daAlinkHIO_wlAtLand_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ f32 field_0x3C;
};  // Size: 0x40

class daAlinkHIO_wlDamage_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ f32 field_0x28;
};  // Size: 0x2C

class daAlinkHIO_wlDamNormal_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
};  // Size: 0x60

class daAlinkHIO_wlDamLarge_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ s16 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
};  // Size: 0x6C

class daAlinkHIO_wlDamHuge_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ s16 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
};  // Size: 0x6C

class daAlinkHIO_wlDamFall_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2A;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
};  // Size: 0x40

class daAlinkHIO_wlDamCaught_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
};  // Size: 0x10

class daAlinkHIO_wlAtDown_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ daAlinkHIO_anm_c field_0x50;
    /* 0x64 */ daAlinkHIO_anm_c field_0x64;
    /* 0x78 */ daAlinkHIO_anm_c field_0x78;
    /* 0x8C */ s16 field_0x8C;
    /* 0x8E */ s16 field_0x8E;
    /* 0x90 */ f32 field_0x90;
    /* 0x94 */ f32 field_0x94;
    /* 0x98 */ f32 field_0x98;
};  // Size: 0x9C

class daAlinkHIO_wlAtCjump_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
};  // Size: 0x64

class daAlinkHIO_wlAtBite_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2A;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
};  // Size: 0x5C

class daAlinkHIO_zwLight_c1 {  // may be wrong
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daAlinkHIO_board_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
    /* 0x8C */ f32 field_0x8C;
    /* 0x90 */ f32 field_0x90;
    /* 0x94 */ f32 field_0x94;
    /* 0x98 */ f32 field_0x98;
};  // Size: 0x9C

class daAlinkHIO_item_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mOneHandEquipAnm;
    /* 0x14 */ daAlinkHIO_anm_c mTwoHandEquipAnm;
    /* 0x28 */ s16 mItemFPTransitionTimer;
    /* 0x2A */ s16 mItemFPMaxUnk;
    /* 0x2C */ s16 mItemFPUpMaxUnk;
    /* 0x2E */ s16 mWiiItemFPDownMaxUnk;
    /* 0x30 */ s16 mWiiItemFPUpMaxUnk;
    /* 0x34 */ f32 mOneHandReleaseAnmSpeed;
    /* 0x38 */ f32 mTwoHandReleaseAnmSpeed;
};  // Size: 0x3C

class daAlinkHIO_bottle_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ daAlinkHIO_anm_c field_0x3C;
    /* 0x50 */ daAlinkHIO_anm_c field_0x50;
    /* 0x64 */ daAlinkHIO_anm_c field_0x64;
    /* 0x78 */ daAlinkHIO_anm_c field_0x78;
    /* 0x8C */ daAlinkHIO_anm_c field_0x8C;
    /* 0xA0 */ daAlinkHIO_anm_c field_0xA0;
};  // Size: 0xB4

class daAlinkHIO_boom_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mThrowAnm;
    /* 0x14 */ daAlinkHIO_anm_c mCatchAnm;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 mBgThroughTime;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3c;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 mCatchSpeed;
};  // Size: 0x4c

class daAlinkHIO_ironBall_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
};  // Size: 0x8C

class daAlinkHIO_bow_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c val0;
    /* 0x14 */ daAlinkHIO_anm_c val5;
    /* 0x28 */ s16 vala;
    /* 0x2A */ s16 valb;
    /* 0x2C */ s16 valc;
    /* 0x30 */ f32 vale;
    /* 0x34 */ f32 valf;
    /* 0x38 */ f32 val10;
    /* 0x3C */ f32 val11;
    /* 0x40 */ f32 val12;
    /* 0x44 */ f32 val13;
    /* 0x48 */ f32 val14;
    /* 0x4C */ f32 val15;
    /* 0x50 */ f32 val16;
    /* 0x54 */ f32 val17;
    /* 0x58 */ f32 val18;
    /* 0x5C */ f32 val19;
    /* 0x60 */ f32 val1a;
    /* 0x64 */ f32 val1b;
    /* 0x68 */ f32 val1c;
    /* 0x6C */ f32 val1d;
};  // Size: 0x70

class daAlinkHIO_copyRod_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mSwingAnm;
    /* 0x14 */ daAlinkHIO_anm_c mBigSwingAnm;
    /* 0x28 */ f32 mBallSpeed;
    /* 0x2c */ f32 mBallMaxDistance;
    /* 0x30 */ f32 mBallReturnSpeed;
    /* 0x34 */ f32 mBossBallMaxDistance;
};  // Size: 0x38

class daAlinkHIO_kandelaar_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ daAlinkHIO_anm_c field_0x14;
    /* 0x28 */ daAlinkHIO_anm_c field_0x28;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ s16 field_0x3E;
    /* 0x40 */ s16 field_0x40;
    /* 0x42 */ s16 field_0x42;
    /* 0x44 */ s16 field_0x44;
    /* 0x46 */ s16 field_0x46;
    /* 0x48 */ s16 field_0x48;
    /* 0x4A */ s16 field_0x4A;
    /* 0x4C */ f32 field_0x4C;
};  // Size: 0x50

class daAlinkHIO_bomb_c1 {
public:
    /* 0x00 */ s16 mExplodeTime;
    /* 0x02 */ s16 mEnemyBombColorR;
    /* 0x04 */ s16 mBombInsectLimitAngle;
    /* 0x08 */ f32 mGravity;
    /* 0x0C */ f32 mMaxFallSpeed;
    /* 0x10 */ f32 mBoundRate;
    /* 0x14 */ f32 mStopSpeedY;
    /* 0x18 */ f32 mMaxSpeedY;
    /* 0x1C */ f32 mEffScale;
    /* 0x20 */ f32 mAtRadius;
    /* 0x24 */ f32 mPokeBombTrackRate;
    /* 0x28 */ f32 mWaterGravity;
    /* 0x2C */ f32 mWaterMaxFallSpeed;
    /* 0x30 */ f32 mThrowSpeedH;
    /* 0x34 */ f32 mThrowSpeedV;
    /* 0x38 */ f32 mWaterThrowSpeedH;
    /* 0x3C */ f32 mWaterThrowSpeedV;
    /* 0x40 */ f32 mWolfThrowSpeedH;
    /* 0x44 */ f32 mWolfThrowSpeedV;
    /* 0x48 */ f32 mExplodeWaterEffectLimit;
};  // Size: 0x4C

class daAlinkHIO_magneBoots_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mEquipAnm;
    /* 0x14 */ f32 mInputFactor;
    /* 0x18 */ f32 mFeetPositionRatio;
    /* 0x1C */ f32 mWalkAnmSpeedMax;
    /* 0x20 */ f32 mWalkAnmSpeedMin;
    /* 0x24 */ f32 mWaterInputFactor;
    /* 0x28 */ f32 mWaterStartWalkAnmRate;
    /* 0x2C */ f32 mWaterWalkAnmRate;
    /* 0x30 */ f32 mMaxMagneFlySpeed;
    /* 0x34 */ f32 mMagneFlyAccelRate;
    /* 0x38 */ f32 mWaterVelocityY;
    /* 0x3C */ f32 mWaterVelocityX;
    /* 0x40 */ f32 mWaterVelRateSword;
    /* 0x44 */ f32 mZoraWaterInputFactor;
    /* 0x48 */ f32 mZoraWaterAnmSpeed;
};  // Size: 0x4C

class daAlinkHIO_spinner_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c field_0x0;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 field_0x1A;
    /* 0x1C */ s16 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
};  // Size: 0x40

class daAlinkHIO_hookshot_c1 {
public:
    /* 0x00 */ daAlinkHIO_anm_c mShootAnm;
    /* 0x14 */ daAlinkHIO_anm_c mCeilingStopAnm;
    /* 0x28 */ daAlinkHIO_anm_c mWallStopAnm;
    /* 0x3C */ bool mForceStick;
    /* 0x40 */ f32 mIdleAnmSpeed;
    /* 0x44 */ f32 mStartInterpolation;
    /* 0x48 */ f32 mMaxLength;
    /* 0x4C */ f32 mShootSpeed;
    /* 0x50 */ f32 mReturnSpeed;
    /* 0x54 */ f32 mClawReturnSpeed;
    /* 0x58 */ f32 mHangAscendSpeed;
    /* 0x5C */ f32 mHangDecendSpeed;
    /* 0x60 */ f32 mBossMaxLength;
    /* 0x64 */ f32 mBossShootSpeed;
    /* 0x68 */ f32 mBossReturnSpeed;
    /* 0x6C */ f32 mBossClawReturnSpeed;
};  // Size: 0x70

class daHorse_c {
public:
    /* 0x0000 */ fopAc_ac_c mActor;
    /* 0x0538 */ u8 field_0x538[0xD1C];
    /* 0x1254 */ daPy_actorKeep_c mZeldaActorKeep;
};

class daMidna_c {
public:
    enum daMidna_ERFLG0 {
        NoServiceWait = 128,
        ForcePanic = 8,
    };
    enum daMidna_FLG1 { ForceNormalColor = 8, ForceTiredColor = 4 };

    void onEndResetStateFlg0(daMidna_ERFLG0 pFlg) { mEndResetStateFlg0 |= pFlg; }
    u32 checkStateFlg1(daMidna_FLG1 pFlg) const { return mStateFlg1 & pFlg; }

    /* 0x0000 */ fopAc_ac_c mActor;
    /* 0x0538 */ u8 field_0x538[0x35C];
    /* 0x0894 */ u32 mStateFlg1;
    /* 0x0898 */ u32 mEndResetStateFlg0;
};

#ifdef WII_PLATFORM
#define daAlinkHIO_swim daAlinkHIO_swim_c0__m
#define daAlinkHIO_frontRoll daAlinkHIO_frontRoll_c0__m
#define daAlinkHIO_wlMove daAlinkHIO_wlMove_c0__m
#define daAlinkHIO_wlSwim daAlinkHIO_wlSwim_c0__m
#else
#define daAlinkHIO_swim m__18daAlinkHIO_swim_c0
#define daAlinkHIO_frontRoll m__23daAlinkHIO_frontRoll_c0
#define daAlinkHIO_wlMove m__20daAlinkHIO_wlMove_c0
#define daAlinkHIO_wlSwim m__20daAlinkHIO_wlSwim_c0
#endif
extern "C" {
extern daAlinkHIO_swim_c1 daAlinkHIO_swim;
extern daAlinkHIO_frontRoll_c1 daAlinkHIO_frontRoll;
extern daAlinkHIO_wlMove_c1 daAlinkHIO_wlMove;
extern daAlinkHIO_wlSwim_c1 daAlinkHIO_wlSwim;
}

#ifdef WII_PLATFORM
#define daAlinkHIO_hookshot daAlinkHIO_hookshot_c0__m
#else
#define daAlinkHIO_hookshot m__22daAlinkHIO_hookshot_c0
#endif
extern daAlinkHIO_hookshot_c1 daAlinkHIO_hookshot;

LIBTP_DEFINE_FUNC(checkStageName__9daAlink_cFPCc, daAlink_c__checkStageName_char_const___,
                  int, daAlink_c__checkStageName, (const char*))

#endif /* D_A_D_A_ALINK_H */