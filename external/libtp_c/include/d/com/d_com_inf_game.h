#ifndef D_COM_D_COM_INF_GAME_H
#define D_COM_D_COM_INF_GAME_H

#include "../save/d_save.h"
#include "../bg/d_bg_s.h"
#include "../cc/d_cc_s.h"
#include "../d_stage.h"
#include "../event/d_event.h"
#include "../event/d_event_manager.h"
#include "../d_attention.h"
#include "../d_vibration.h"
#include "../d_drawlist.h"
#include "../a/d_a_alink.h"
#include "../../JSystem/JKernel/JKRArchive.h"

struct dTimer_c {};

struct J2DGrafContext {};

class __d_timer_info_c {
public:
    dTimer_c* mTimerPtr;
    s32 mTimerNowTimeMs;
    s32 mTimerLimitTimeMs;
    s32 mTimerMode;
    u8 mTimerType;
};

struct camera_class {};

class dComIfG_camera_info_class {
public:
    /* 0x00 */ camera_class* mCamera;
    /* 0x04 */ u8 field_0x4;
    /* 0x05 */ u8 field_0x5[3];
    /* 0x08 */ u32 mCameraAttentionStatus;
    /* 0x0C */ f32 mCameraZoomScale;
    /* 0x10 */ f32 mCameraZoomForcus;
    /* 0x14 */ char* mCameraParamFileName;
    /* 0x18 */ cXyz mCameraPos;
    /* 0x24 */ cXyz mCameraTarget;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ s16 field_0x34;
};

class dComIfG_play_c {
public:
    bool& isPauseFlag() { return mPauseFlag; }
    void* getMsgObjectClass() { return mMsgObjectClass; }
    dStage_roomControl_c& getRoomControl() { return mRoomControl; }
    dEvt_control_c& getEvent() { return mEvent; }
    dEvent_manager_c& getEventManager() { return mEvtManager; }
    void* getPlayerPtr(int idx) { return mPlayerPtr[idx]; }
    u8& getItemLifeCountType() { return mItemLifeCountType; }
    void setItem(u8 slot, u8 i_no) {
        mItemSlot = slot;
        mItemID = i_no;
    }

    void setZStatus(u8 status, u8 flag) {
        mZStatus = status;
        mZSetFlag = flag;
    }
    void setRStatus(u8 status, u8 flag) {
        mRStatus = status;
        mRSetFlag = flag;
    }
    void setDoStatus(u8 status, u8 flag) {
        mDoStatus = status;
        mDoSetFlag = flag;
    }
    void setAStatus(u8 status, u8 flag) {
        mAStatus = status;
        mASetFlag = flag;
    }
    void setBottleStatus(u8 status, u8 flag) {
        mBottleStatus = status;
        mBottleSetFlag = flag;
    }
    void setItemLifeCount(f32 hearts, u8 type) {
        mItemLifeCount += hearts;
        mItemLifeCountType = type;
    }
    void setItemRupeeCount(int rupees) { mItemRupeeCount += rupees; }
    void setItemMagicCount(s16 magic) { mItemMagicCount += magic; }
    void setItemMaxMagicCount(s16 max) { mItemMaxMagicCount += max; }
    void setItemArrowNumCount(s16 arrows) { mItemArrowNumCount += arrows; }
    void setItemPachinkoNumCount(s16 seeds) { mItemPachinkoNumCount += seeds; }
    void setItemKeyNumCount(s16 keys) { mItemKeyNumCount += keys; }
    void setItemMaxLifeCount(s16 max) { mItemMaxLifeCount += max; }
    void setOxygen(int oxygen) { mOxygen = oxygen; }
    void setNowOxygen(int oxygen) { mNowOxygen = oxygen; }
    void setMaxOxygen(int max) { mMaxOxygen = max; }
    u8 getDoStatus(void) { return mDoStatus; }
    u8 getRStatus(void) { return mRStatus; }
    // inline char* getStartStageName() { return mStartStage.getName(); }

public:
    /* 0x00000 */ dBgS mDBgS;
    /* 0x01404 */ dCcS mDCcS;
    /* 0x03EC8 */ dStage_startStage_c mStartStage;
    /* 0x03ED6 */ dStage_nextStage_c mNextStage;
    /* 0x03EE8 */ dStage_stageDt_c mStageData;
    /* 0x03F8C */ dStage_roomControl_c mRoomControl;
    /* 0x03F90 */ dEvt_control_c mEvent;
    /* 0x040C0 */ dEvent_manager_c mEvtManager; /* Wii: +0x4 */
    /* 0x04780 */ dAttention_c mAttention;
#ifdef WII_PLATFORM
    /* 0x04CA0 */ u8 field_0x4ca0[12];
#endif
    /* 0x04C9C */ dVibration_c mVibration; /* Wii: +0x10 */
    /* 0x04D2C */ u8 field_0x4d2c[4];
    /* 0x04D30 */ JKRArchive* mFieldMapArchive2;
    /* 0x04D34 */ JKRArchive* mMsgArchive[11];
    /* 0x04D60 */ JKRArchive* mDemoMsgArchive;
    /* 0x04D64 */ JKRArchive* mMeterButtonArchive;
    /* 0x04D68 */ void* field_0x4d68;
    /* 0x04D6C */ JKRArchive* mFontArchive;
    /* 0x04D70 */ JKRArchive* mRubyArchive;
    /* 0x04D74 */ JKRArchive* mAnmArchive;
    /* 0x04D78 */ void* field_0x4d78[2];
    /* 0x04D80 */ JKRArchive* mCollectResArchive;
    /* 0x04D84 */ JKRArchive* mFmapResArchive;
    /* 0x04D88 */ JKRArchive* mDmapResArchive;
    /* 0x04D8C */ JKRArchive* mOptionResArchive;
    /* 0x04D90 */ void* field_0x4d90[2];
    /* 0x04D98 */ JKRArchive* mItemIconArchive;
    /* 0x04D9C */ JKRArchive* mNameResArchive;
    /* 0x04DA0 */ JKRArchive* mErrorResArchive;
    /* 0x04DA4 */ void* field_0x4da4;
    /* 0x04DA8 */ JKRArchive* mAllMapArchive;
    /* 0x04DAC */ JKRArchive* mMsgCommonArchive;
    /* 0x04DB0 */ JKRArchive* mRingResArchive;
    /* 0x04DB4 */ void* field_0x4db4;
    /* 0x04DB8 */ JKRArchive* mCardIconResArchive;
    /* 0x04DBC */ JKRArchive* mMsgDtArchive[15];
    /* 0x04DF8 */ JKRArchive* mMain2DArchive;
    /* 0x04DFC */ void* field_0x4dfc[2];
    /* 0x04E04 */ void* mParticle;
    /* 0x04E08 */ void* mSimpleModel;
    /* 0x04E0C */ u8 mWindowNum;
    /* 0x04E0D */ u8 mLayerOld;
    /* 0x04E0E */ u16 mStatus;
    /* 0x04E10 */ dDlst_window_c mWindow[1];
    /* 0x04E3C */ dComIfG_camera_info_class mCameraInfo[1];
    /* 0x04E74 */ daAlink_c* mPlayer[1];
    /* 0x04E78 */ s8 mPlayerCameraID[4];
    /* 0x04E7C */ void* mPlayerPtr[2];
    /* 0x04E84 */ void* mMsgObjectClass;
    /* 0x04E88 */ f32 mItemLifeCount;
    /* 0x04E8C */ int mItemRupeeCount;
    /* 0x04E90 */ s16 mItemKeyNumCount;
    /* 0x04E92 */ s16 mItemMaxLifeCount;
    /* 0x04E94 */ s16 mItemMagicCount;
    /* 0x04E96 */ s16 mItemNowMagicCount;
    /* 0x04E98 */ s16 mItemMaxMagicCount;
    /* 0x04E9A */ s16 field_0x4e9a;
    /* 0x04E9C */ int mItemOilCount;
    /* 0x04EA0 */ int mItemNowOil;
    /* 0x04EA4 */ int mItemMaxOilCount;
    /* 0x04EA8 */ int mOxygen;
    /* 0x04EAC */ int mNowOxygen;
    /* 0x04EB0 */ int mMaxOxygen;
    /* 0x04EB4 */ int mOxygenCount;
    /* 0x04EB8 */ int mMaxOxygenCount;
    /* 0x04EBC */ s16 mItemArrowNumCount;
    /* 0x04EBE */ s16 mItemPachinkoNumCount;
    /* 0x04EC0 */ s16 mItemMaxArrowNumCount;
    /* 0x04EC2 */ s16 mItemBombNumCount[3];
    /* 0x04EC8 */ u8 field_0x4ec8[4];
    /* 0x04ECC */ s16 mItemMaxBombNumCount1;
    /* 0x04ECE */ s16 mItemMaxBombNumCount2;
    /* 0x04ED0 */ u8 field_0x4ed0[6];
    /* 0x04ED6 */ s16 mItemMaxBombNumCount3;
    /* 0x04ED8 */ u8 field_0x4ed8[6];
    /* 0x04EDE */ u16 mItemNowLife;
    /* 0x04EE0 */ u8 field_0x4ee0[2];
    /* 0x04EE2 */ u8 mMesgStatus;
    /* 0x04EE3 */ u8 field_0x4ee3;
    /* 0x04EE4 */ u8 mRStatus;
    /* 0x04EE5 */ u8 mAStatus;  // B button
    /* 0x04EE6 */ u8 field_0x4ee6;
    /* 0x04EE7 */ u8 mNunStatus;
    /* 0x04EE8 */ u8 mBottleStatus;
    /* 0x04EE9 */ u8 mRemoConStatus;
    /* 0x04EEA */ u8 field_0x4eea[2];
    /* 0x04EEC */ u8 mDoStatus;  // A button
    /* 0x04EED */ u8 field_0x4eed;
    /* 0x04EEE */ u8 m3DStatus;
    /* 0x04EEF */ u8 field_0x4eef;  // related to NunStatusForce
    /* 0x04EF0 */ u8 field_0x4ef0;  // related to NunStatus
    /* 0x04EF1 */ u8 field_0x4ef1;  // related to RemoConStatusForce
    /* 0x04EF2 */ u8 field_0x4ef2;  // related to RemoConStatus
    /* 0x04EF3 */ u8 field_0x4ef3[2];
    /* 0x04EF5 */ u8 m3DDirection;
    /* 0x04EF6 */ u8 m3DDirectionForce;
    /* 0x04EF7 */ u8 mCStickStatus;
    /* 0x04EF8 */ u8 mCStickDirection;
    /* 0x04EF9 */ u8 mCStickDirectionForce;
    /* 0x04EFA */ u8 mSButtonStatus;
    /* 0x04EFB */ u8 mZStatus;
    /* 0x04EFC */ u8 mRStatusForce;
    /* 0x04EFD */ u8 mAStatusForce;
    /* 0x04EFE */ u8 field_0x4efe;
    /* 0x04EFF */ u8 field_0x4eff;  // related to NunStatusForce
    /* 0x04F00 */ u8 mBottleStatusForce;
    /* 0x04F01 */ u8 field_0x4f01;  // related to RemoConStatusForce
    /* 0x04F02 */ u8 field_0x4f02[2];
    /* 0x04F04 */ u8 mDoStatusForce;
    /* 0x04F05 */ u8 mTouchStatusForce;
    /* 0x04F06 */ u8 m3DStatusForce;
    /* 0x04F07 */ u8 mCStickStatusForce;
    /* 0x04F08 */ u8 mSButtonStatusForce;
    /* 0x04F09 */ u8 mZStatusForce;
    /* 0x04F0A */ u8 mRSetFlag;
    /* 0x04F0B */ u8 mASetFlag;
    /* 0x04F0C */ u8 field_0x4f0c;
    /* 0x04F0D */ u8 mNunSetFlag;
    /* 0x04F0E */ u8 mBottleSetFlag;
    /* 0x04F0F */ u8 mRemoConSetFlag;
    /* 0x04F10 */ u8 field_0x4f10[2];
    /* 0x04F12 */ u8 mDoSetFlag;
    /* 0x04F13 */ u8 m3DSetFlag;
    /* 0x04F14 */ u8 mCStickSetFlag;
    /* 0x04F15 */ u8 mSButtonSetFlag;
    /* 0x04F16 */ u8 mZSetFlag;
    /* 0x04F17 */ u8 mRSetFlagForce;
    /* 0x04F18 */ u8 mASetFlagForce;
    /* 0x04F19 */ u8 field_0x4f19;
    /* 0x04F1A */ u8 field_0x4f1a;  // related to NunStatusForce
    /* 0x04F1B */ u8 mBottleSetFlagForce;
    /* 0x04F1C */ u8 field_0x4f1c;  // related to RemoConStatusForce
    /* 0x04F1D */ u8 field_0x4f1d[2];
    /* 0x04F1F */ u8 mDoSetFlagForce;
    /* 0x04F20 */ u8 m3DSetFlagForce;
    /* 0x04F21 */ u8 mCStickSetFlagForce;
    /* 0x04F22 */ u8 mSButtonSetFlagForce;
    /* 0x04F23 */ u8 mZSetFlagForce;
    /* 0x04F24 */ u8 mXStatus;
    /* 0x04F25 */ u8 mXStatusForce;
    /* 0x04F26 */ u8 field_0x4fbe;  // related to XStatus
    /* 0x04F27 */ u8 mXSetFlagForce;
    /* 0x04F28 */ u8 mYStatus;
    /* 0x04F29 */ u8 mYStatusForce;
    /* 0x04F2A */ u8 mYSetFlag;
    /* 0x04F2B */ u8 mYSetFlagForce;
    /* 0x04F2C */ u8 mNunZStatus;
    /* 0x04F2D */ u8 mNunZSetFlag;
    /* 0x04F2E */ u8 field_0x4fc6;  // related to NunZStatusForce
    /* 0x04F2F */ u8 field_0x4fc7;  // related to NunZStatusForce
    /* 0x04F30 */ u8 mNunCStatus;
    /* 0x04F31 */ u8 mNunCSetFlag;
    /* 0x04F32 */ u8 field_0x4fca;  // related to NunCStatusForce
    /* 0x04F33 */ u8 field_0x4fcb;  // related to NunCStatusForce
    /* 0x04F34 */ u8 mSelectItem[8];
    /* 0x04F3C */ u8 mSelectEquip[6];
    /* 0x04F42 */ u8 mBaseAnimeID;
    /* 0x04F43 */ u8 mFaceAnimeID;
    /* 0x04F44 */ u8 mNowAnimeID;
    /* 0x04F45 */ u8 mItemSlot;
    /* 0x04F46 */ u8 mItemID;
    /* 0x04F47 */ u8 field_0x4f47[2];
    /* 0x04F49 */ u8 mDirection;
    /* 0x04F4A */ u8 field_0x4f4a;
    /* 0x04F4B */ u8 field_0x4f4b;  // related to itemInit
    /* 0x04F4C */ u8 field_0x4f4c;  // related to itemInit
    /* 0x04F4D */ u8 field_0x4f4d;
    /* 0x04F4E */ u8 mMesgCancelButton;
    /* 0x04F4F */ u8 field_0x4f4f[2];
    /* 0x04F51 */ u8 mGameoverStatus;
    /* 0x04F52 */ u8 field_0x4f52[5];
    /* 0x04F57 */ u8 mHeapLockFlag;
    /* 0x04F58 */ u8 mSubHeapLockFlag[2];
    /* 0x04F5A */ u8 mNowVibration;
    /* 0x04F5B */ u8 field_0x4f5b[2];
    /* 0x04F5D */ u8 mWolfAbility;
    /* 0x04F5E */ u8 field_0x4f5e[11];
    /* 0x04F69 */ u8 mNeedLightDropNum;
    /* 0x04F6A */ u8 field_0x4f6a[18];
    /* 0x04F7C */ u8 mMesgBgm;
    /* 0x04F7D */ bool mPauseFlag;
    /* 0x04F7E */ u8 mItemLifeCountType;
    /* 0x04F7F */ u8 mOxygenShowFlag;
    /* 0x04F80 */ u8 mShow2D;
    /* 0x04F81 */ u8 field_0x4f81[3];
    /* 0x04F84 */ JKRExpHeap* mExpHeap2D;
    /* 0x04F88 */ JKRExpHeap* mSubExpHeap2D[2];
    /* 0x04F90 */ JKRExpHeap* mMsgExpHeap;
    /* 0x04F94 */ char field_0x4F94[8];  // related to setWarpItemData
    /* 0x04F9C */ cXyz field_0x4f9c;     // related to setWarpItemData
    /* 0x04FA8 */ s16 field_0x4fa8;
    /* 0x04FAA */ s8 field_0x4faa;   // related to setWarpItemData
    /* 0x04FAB */ u8 field_0x4fab;  // related to setWarpItemData
    /* 0x04FAC */ u8 field_0x4fac;  // related to setWarpItemData
    /* 0x04FAD */ u8 field_0x4fad[3];
    /* 0x04FB0 */ void* mMesgCamInfo;
    /* 0x04FB4 */ int mMesgCamInfoBasicID;
    /* 0x04FB8 */ fopAc_ac_c* mMesgCamInfoActor1;
    /* 0x04FBC */ fopAc_ac_c* mMesgCamInfoActor2;
    /* 0x04FC0 */ fopAc_ac_c* mMesgCamInfoActor3;
    /* 0x04FC4 */ fopAc_ac_c* mMesgCamInfoActor4;
    /* 0x04FC8 */ fopAc_ac_c* mMesgCamInfoActor5;
    /* 0x04FCC */ fopAc_ac_c* mMesgCamInfoActor6;
    /* 0x04FD0 */ fopAc_ac_c* mMesgCamInfoActor7;
    /* 0x04FD4 */ fopAc_ac_c* mMesgCamInfoActor8;
    /* 0x04FD8 */ fopAc_ac_c* mMesgCamInfoActor9;
    /* 0x04FDC */ fopAc_ac_c* mMesgCamInfoActor10;
    /* 0x04FE0 */ int mPlayerStatus;
    /* 0x04FE4 */ u8 field_0x4fe4[0x14];
    /* 0x04FF8 */ __d_timer_info_c mTimerInfo;
    /* 0x0500C */ dDlst_window_c* mCurrentWindow;
    /* 0x05010 */ void* mCurrentView;
    /* 0x05014 */ void* mCurrentViewport;
    /* 0x05018 */ J2DGrafContext* mCurrentGrafPort;
    /* 0x0501C */ void* mItemTable;
    /* 0x0501D */ u8 field_0x501d[4];
    /* 0x05024 */ char mLastPlayStageName[8];
};

class dComIfG_inf_c {
public:
    /* 0x00000 */ dSv_info_c info;
    /* 0x00F38 */ dComIfG_play_c play;
    /* 0x05F64 */ u8 field_0x5F64[0x17EAC];
};  // Size: 0x1DE10

#ifdef GCN_PLATFORM
static_assert(sizeof(dComIfG_inf_c) == 0x1DE10);
#endif

extern dComIfG_inf_c g_dComIfG_gameInfo;

extern volatile u8 bossFlags;

struct TitleScreenPtr {
    u8 _p0[0x59];             // 0x00
    u8 trigger_on_next_load;  // 0x59
};
struct TitleScreenInfo {
    TitleScreenPtr* title_screen_info;
};
extern TitleScreenInfo l_fpcNdRq_Queue;

LIBTP_DEFINE_FUNC(getLayerNo_common_common__14dComIfG_play_cFPCcii, dComIfG_play_c__getLayerNo_common_common_char_const____int__int_,
                  int, tp_getLayerNo, (const char* stageName, int roomId, int layerOverride))

inline dBgS* dComIfG_Bgsp() {
    return &g_dComIfG_gameInfo.play.mDBgS;
}

inline dCcS* dComIfG_Ccsp() {
    return &g_dComIfG_gameInfo.play.mDCcS;
}

// Inline Functions
inline void dComIfGs_setItem(int slot_no, u8 item_no) {
    dSv_player_item_c__setItem(&g_dComIfG_gameInfo.info.getPlayer().getItem(), slot_no, item_no);
}
inline u8 dComIfGs_getItem(int slot_no, bool is_combo_item) {
    return dSv_player_item_c__getItem(&g_dComIfG_gameInfo.info.getPlayer().getItem(), slot_no,
                                      is_combo_item);
}
inline void dComIfGp_setRStatus(u8 status, u8 flag) {
    g_dComIfG_gameInfo.play.setRStatus(status, flag);
}
inline void dComIfGp_setDoStatus(u8 status, u8 flag) {
    g_dComIfG_gameInfo.play.setDoStatus(status, flag);
}
inline void dComIfGp_setAStatus(u8 status, u8 flag) {
    g_dComIfG_gameInfo.play.setAStatus(status, flag);
}
inline void dComIfGp_setZStatus(u8 status, u8 flag) {
    g_dComIfG_gameInfo.play.setZStatus(status, flag);
}
inline void dComIfGp_setItemMagicCount(s16 amount) {
    g_dComIfG_gameInfo.play.setItemMagicCount(amount);
}
inline void dComIfGp_setItemMaxMagicCount(s16 max) {
    g_dComIfG_gameInfo.play.setItemMaxMagicCount(max);
}
inline void dComIfGp_setItemArrowNumCount(s16 amount) {
    g_dComIfG_gameInfo.play.setItemArrowNumCount(amount);
}
inline void dComIfGp_setItemPachinkoNumCount(s16 amount) {
    g_dComIfG_gameInfo.play.setItemPachinkoNumCount(amount);
}
inline void dComIfGp_setItemKeyNumCount(s16 amount) {
    g_dComIfG_gameInfo.play.setItemKeyNumCount(amount);
}
inline void dComIfGp_setItemMaxLifeCount(s16 max) {
    g_dComIfG_gameInfo.play.setItemMaxLifeCount(max);
}
/* inline void dComIfGs_onDungeonItemMap(void) {
    g_dComIfG_gameInfo.info.getMemory().getBit().onDungeonItemMap();
}
inline void dComIfGs_onDungeonItemCompass(void) {
    g_dComIfG_gameInfo.info.getMemory().getBit().onDungeonItemCompass();
}
inline void dComIfGs_onDungeonItemWarp(void) {
    g_dComIfG_gameInfo.info.getMemory().getBit().onDungeonItemWarp();
}*/
inline void dComIfGs_setOxygen(int amount) {
    g_dComIfG_gameInfo.play.setOxygen(amount);
}
inline void dComIfGs_setNowOxygen(int amount) {
    g_dComIfG_gameInfo.play.setNowOxygen(amount);
}
inline void dComIfGs_setMaxOxygen(int max) {
    g_dComIfG_gameInfo.play.setMaxOxygen(max);
}
inline void dComIfGs_setOil(u16 amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setOil(amount);
}
inline void dComIfGs_setMaxOil(u16 max) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMaxOil(max);
}
inline void dComIfGs_setWalletSize(u8 size) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setWalletSize(size);
}
inline void dComIfGs_setMagic(u8 amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(amount);
}
inline void dComIfGs_setMaxMagic(u8 max) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMaxMagic(max);
}
inline void dComIfGs_setRupee(u16 amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setRupee(amount);
}
inline void dComIfGs_setLife(u16 amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(amount);
}
inline void dComIfGs_setMaxLife(u8 max) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMaxLife(max);
}
/*
inline void dComIfGs_onDungeonItemBossKey(void) {
    g_dComIfG_gameInfo.info.getMemory().getBit().onDungeonItemBossKey();
}
inline void dComIfGs_setCollectSword(u8 sword_id) {
    g_dComIfG_gameInfo.info.getSavedata().getCollect().setCollect(COLLECT_SWORD, sword_id);
}
inline void dComIfGs_setCollectShield(u8 shield_id) {
    g_dComIfG_gameInfo.info.getSavedata().getCollect().setCollect(COLLECT_SHIELD, shield_id);
}
inline void dComIfGs_setCollectClothes(u8 clothes_id) {
    g_dComIfG_gameInfo.info.getSavedata().getCollect().setCollect(COLLECT_CLOTHING, clothes_id);
}
inline void dComIfGs_setRodTypeLevelUp(void) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setRodTypeLevelUp();
}*/
inline void dComIfGs_setArrowNum(u8 amount) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setArrowNum(amount);
}
inline void dComIfGs_setPachinkoNum(u8 amount) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setPachinkoNum(amount);
}
inline void dComIfGs_setArrowMax(u8 max) {
    g_dComIfG_gameInfo.info.getPlayer().getItemMax().setArrowNum(max);
}
inline u8 dComIfGs_getPachinkoNum() {
    return g_dComIfG_gameInfo.info.getPlayer().getItemRecord().getPachinkoNum();
}
inline u8 dComIfGs_getPachinkoMax(void) {
    return 50;
}
/*
inline void dComIfGs_setEmptyBombBag(void) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBombBag();
}
inline void dComIfGs_setEmptyBombBag(u8 type, u8 amount) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBombBag(type, amount);
}
inline void dComIfGs_setEmptyBombBagItemIn(u8 type, bool unk) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBombBagItemIn(type, unk);
}
inline void dComIfGs_setEmptyBottle(void) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBottle();
}
inline void dComIfGs_setEmptyBottle(u8 type) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBottle(type);
}
inline void dComIfGs_setEmptyBottleItemIn(u8 type) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBottleItemIn(type);
}
inline void dComIfGs_onEventBit(u16 id) {
    g_dComIfG_gameInfo.info.getSavedata().getEventFlags().onEventBit(id);
}
inline void dComIfGs_onLightDropFlag(u8 area_id) {
    g_dComIfG_gameInfo.info.getSavedata().getLightDrop().onLightDropGetFlag(area_id);
}
inline void dComIfGs_onSwitch(int param1, int param2) {
    g_dComIfG_gameInfo.getInfo().onSwitch(param1, param2);
}
inline int dComIfGs_isCollectSword(u8 sword_id) {
    return g_dComIfG_gameInfo.info.getSavedata().getCollect().isCollect(COLLECT_SWORD, sword_id);
}
inline int dComIfGs_isCollectClothing(u8 clothing_id) {
    return g_dComIfG_gameInfo.info.getSavedata().getCollect().isCollect(COLLECT_CLOTHING,
                                                                         clothing_id);
}
inline u8 dComIfGs_checkBottle(u8 type) {
    return g_dComIfG_gameInfo.info.getSavedata().getItem().checkBottle(type);
}
inline int dComIfGs_isLightDropGetFlag(u8 area_id) {
    return g_dComIfG_gameInfo.info.getSavedata().getLightDrop().isLightDropGetFlag(area_id);
}*/
inline u8 dComIfGs_getArrowMax(void) {
    return g_dComIfG_gameInfo.info.getSavedata().getPlayer().getItemMax().getArrowNum();
}
inline u8 dComIfGs_getCollectSmell(void) {
    return g_dComIfG_gameInfo.info.getSavedata().getPlayer().getPlayerStatusA().getSelectEquip(3);
}
inline u8 dComIfGs_getPohSpiritNum(void) {
    return g_dComIfG_gameInfo.info.getSavedata().getPlayer().getCollect().getPohNum();
}
inline void dComIfGs_setPohSpiritNum(u8 num) {
    return g_dComIfG_gameInfo.info.getSavedata().getPlayer().getCollect().setPohNum(num);
}
inline u8 dComIfGs_getKeyNum(void) {
    return g_dComIfG_gameInfo.info.getMemory().getBit().getKeyNum();
}
/*
inline void dComIfGs_onItemFirstBit(u8 i_no) {
    g_dComIfG_gameInfo.info.getSavedata().getGetItem().onFirstBit(i_no);
}*/
inline u16 dComIfGs_getMaxLife(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getMaxLife();
}
/*
inline void dComIfGs_offEventBit(u16 event) {
    g_dComIfG_gameInfo.info.getSavedata().getEventFlags().offEventBit(event);
}*/
inline const char* dComIfGs_getLastWarpMarkStageName(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerLastMarkInfo().getName();
}
inline cXyz dComIfGs_getLastWarpMarkPlayerPos(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerLastMarkInfo().getPos();
}
inline s16 dComIfGs_getLastWarpMarkPlayerAngleY(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerLastMarkInfo().getAngleY();
}
inline s8 dComIfGs_getLastWarpMarkRoomNo(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerLastMarkInfo().getRoomNo();
}
inline char dComIfGs_getLastWarpAcceptStage(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerLastMarkInfo().getWarpAcceptStage();
}
inline u8 dComIfGs_getSelectEquipClothes(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectEquip(COLLECT_CLOTHING);
}
inline u8 dComIfGs_getSelectEquipSword(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectEquip(COLLECT_SWORD);
}
inline u8 dComIfGs_getSelectEquipShield(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectEquip(COLLECT_SHIELD);
}
/*
inline u8 dComIfGs_getLightDropNum(u8 area_id) {
    return g_dComIfG_gameInfo.info.getSavedata().getLightDrop().getLightDropNum(area_id);
}*/
inline u8 dComIfGs_getSelectItemIndex(int idx) {
    return dSv_player_status_a_c__getSelectItemIndex(
        &g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA(), idx);
}

LIBTP_DEFINE_FUNC(dComIfGs_setSelectItemIndex__FiUc, dComIfGs_setSelectItemIndex_int__unsigned_char_,
                  void, dComIfGs_setSelectItemIndex, (s32 idx, u8 item))

LIBTP_DEFINE_FUNC(dComIfGs_getMixItemIndex__Fi, dComIfGs_getMixItemIndex_int_,
                  u8, dComIfGs_getMixItemIndex, (s32 idx))

LIBTP_DEFINE_FUNC(dComIfGs_setMixItemIndex__FiUc, dComIfGs_setMixItemIndex_int__unsigned_char_,
                  void, dComIfGs_setMixItemIndex, (s32 idx, u8 item))

inline void dComIfGp_setItem(u8 slot, u8 i_no) {
                  g_dComIfG_gameInfo.play.setItem(slot, i_no);
}
/*
inline u32 dComIfGp_getNowVibration(void) {
    return g_dComIfG_gameInfo.play.getNowVibration();
}
inline char* dComIfGp_getStartStageName(void) {
    return g_dComIfG_gameInfo.play.getStartStageName();
}*/

inline void dComIfGp_setNextStage(const char* stage, s8 room, s16 point, s8 layer,
                                  s8 wipe, u8 wipe_speed) {
    dStage_nextStage_c__set(&g_dComIfG_gameInfo.play.mNextStage, stage, room, point, layer, wipe,
                            wipe_speed);
}

inline void dComIfGs_setTransformStatus(u8 status) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setTransformStatus(status);
}

inline u8 dComIfGs_getTransformStatus() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getTransformStatus();
}

inline daAlink_c* dComIfGp_getPlayer() {
    return g_dComIfG_gameInfo.play.mPlayer[0];
}

inline u8 dComIfGs_getLightDropNum(u8 area) {
    return dSv_light_drop_c__getLightDropNum(&g_dComIfG_gameInfo.info.getPlayer().getLightDrop(),
                                             area);
}

inline void dComIfGs_setLightDropNum(u8 area, u8 num) {
    dSv_light_drop_c__setLightDropNum(&g_dComIfG_gameInfo.info.getPlayer().getLightDrop(), area,
                                      num);
}

inline void dComIfGs_onSwitch(int i_no, int i_roomNo) {
    dSv_info_c__onSwitch(&g_dComIfG_gameInfo.info, i_no, i_roomNo);
}

inline void dComIfGs_offSwitch(int i_no, int i_roomNo) {
    dSv_info_c__offSwitch(&g_dComIfG_gameInfo.info, i_no, i_roomNo);
}

inline void dComIfGs_putSave(int i_stageNo) {
    tp_putSave(&g_dComIfG_gameInfo.info, i_stageNo);
}

inline void dComIfGs_getSave(int i_stageNo) {
    tp_getSave(&g_dComIfG_gameInfo.info, i_stageNo);
}

#ifdef WII_PLATFORM
inline dEvt_control_c& dComIfGp_getEvent() {
    return g_dComIfG_gameInfo.play.getEvent();
}

inline dEvent_manager_c& dComIfGp_getEventManager() {
    return g_dComIfG_gameInfo.play.getEventManager();
}
#else

LIBTP_DEFINE_FUNC(dComIfGp_getEvent__Fv, dComIfGp_getEvent__Fv,
                  dEvt_control_c&, dComIfGp_getEvent, (void))

LIBTP_DEFINE_FUNC(dComIfGp_getEventManager__Fv, ,
                  dEvent_manager_c&, dComIfGp_getEventManager, (void))
#endif

inline void dComIfGs_setTime(f32 pTime) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().setTime(pTime);
}

inline f32 dComIfGs_getTime() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().getTime();
}

inline dSv_save_c& dComIfGs_getSavedata() {
    return g_dComIfG_gameInfo.info.mSavedata;
}

inline u16 dComIfGs_getLife() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getLife();
}

inline void dComIfGs_setBombNum(u8 idx, u8 num) {
    dSv_player_item_record_c__setBombNum(&g_dComIfG_gameInfo.info.getPlayer().getItemRecord(), idx,
                                         num);
}

#ifdef WII_PLATFORM
inline bool dComIfGs_isItemFirstBit(u8 flag) {
    return dSv_player_get_item_c__isFirstBit_unsigned_char__const(
        &g_dComIfG_gameInfo.info.getPlayer().getGetItem(), flag);
}
#else

LIBTP_DEFINE_FUNC(dComIfGs_isItemFirstBit__FUc, dComIfGs_isItemFirstBit__FUc,
                  bool, dComIfGs_isItemFirstBit, (u8 item))
#endif

inline u8 dComIfGs_getWalletSize() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getWalletSize();
}

inline void dComIfGs_onItemFirstBit(u8 item) {
    dSv_player_get_item_c__onFirstBit(&g_dComIfG_gameInfo.info.getPlayer().getGetItem(), item);
}

inline void dComIfGs_offItemFirstBit(u8 item) {
    dSv_player_get_item_c__offFirstBit(&g_dComIfG_gameInfo.info.getPlayer().getGetItem(), item);
}

inline bool dComIfGs_isEventBit(u16 flag) {
    return dSv_event_c__isEventBit(&g_dComIfG_gameInfo.info.mSavedata.mEvent, flag);
}

inline void dComIfGs_onEventBit(u16 flag) {
    dSv_event_c__onEventBit(&g_dComIfG_gameInfo.info.mSavedata.mEvent, flag);
}

inline void dComIfGs_offEventBit(u16 flag) {
    dSv_event_c__offEventBit(&g_dComIfG_gameInfo.info.mSavedata.mEvent, flag);
}

inline void dComIfGs_setKeyNum(u8 num) {
    g_dComIfG_gameInfo.info.getMemory().getBit().setKeyNum(num);
}

inline bool dComIfGs_isTransformLV(s32 flag) {
    return dSv_player_status_b_c__isTransformLV(
        &g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB(), flag);
}

inline void dComIfGs_onTransformLV(s32 flag) {
    dSv_player_status_b_c__onTransformLV(&g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB(),
                                         flag);
}

inline void dComIfGs_offTransformLV(s32 flag) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().offTransformLV(flag);
}

inline bool dComIfGs_isDungeonItemMap() {
    return dSv_memBit_c__isDungeonItem(&g_dComIfG_gameInfo.info.getMemory().getBit(),
                                       dSv_memBit_c::MAP);
}

inline bool dComIfGs_isDungeonItemBossKey() {
    return dSv_memBit_c__isDungeonItem(&g_dComIfG_gameInfo.info.getMemory().getBit(),
                                       dSv_memBit_c::BOSS_KEY);
}

inline u8 dComIfGs_getArrowNum() {
    return g_dComIfG_gameInfo.info.getSavedata().getPlayer().getItemRecord().getArrowNum();
}

inline u8 dComIfGs_getBombNum(u8 bagIdx) {
    return dSv_player_item_record_c__getBombNum(
        &g_dComIfG_gameInfo.info.getPlayer().getItemRecord(), bagIdx);
}

#ifdef WII_PLATFORM
inline u16 dComIfGs_getRupee() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getRupee();
}
#else

LIBTP_DEFINE_FUNC(dComIfGs_getRupee__Fv, dComIfGs_getRupee__Fv,
                  u16, dComIfGs_getRupee, (void))
#endif

LIBTP_DEFINE_FUNC(dComIfGs_onOneZoneSwitch__Fii, dComIfGs_onOneZoneSwitch_int__int_,
                  void, dComIfGs_onOneZoneSwitch, (int, int))

LIBTP_DEFINE_FUNC(dComIfGs_onZoneSwitch__Fii, dComIfGs_onZoneSwitch_int__int_,
                  void, dComIfGs_onZoneSwitch, (int, int))

class dComIfAc_gameInfo {
public:
    u8 field_0x0[4];
    bool freeze;
    u8 field_0x6[3];
};

extern dComIfAc_gameInfo g_dComIfAc_gameInfo;
extern u32 fopAc_ac_c__stopStatus;

#endif /* D_COM_D_COM_INF_GAME_H */
