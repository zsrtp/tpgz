#ifndef D_COM_D_COM_INF_GAME_H
#define D_COM_D_COM_INF_GAME_H

#include "../../addrs.h"
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
    int32_t mTimerNowTimeMs;
    int32_t mTimerLimitTimeMs;
    int32_t mTimerMode;
    uint8_t mTimerType;
};

struct camera_class {};

class dComIfG_camera_info_class {
public:
    /* 0x00 */ camera_class* mCamera;
    /* 0x04 */ uint8_t field_0x4;
    /* 0x05 */ uint8_t field_0x5[3];
    /* 0x08 */ uint32_t mCameraAttentionStatus;
    /* 0x0C */ float mCameraZoomScale;
    /* 0x10 */ float mCameraZoomForcus;
    /* 0x14 */ char* mCameraParamFileName;
    /* 0x18 */ cXyz mCameraPos;
    /* 0x24 */ cXyz mCameraTarget;
    /* 0x30 */ float field_0x30;
    /* 0x34 */ int16_t field_0x34;
};

class dComIfG_play_c {
public:
    bool& isPauseFlag() { return mPauseFlag; }
    void* getMsgObjectClass() { return mMsgObjectClass; }
    dStage_roomControl_c& getRoomControl() { return mRoomControl; }
    dEvt_control_c& getEvent() { return mEvent; }
    dEvent_manager_c& getEventManager() { return mEvtManager; }
    void* getPlayerPtr(int idx) { return mPlayerPtr[idx]; }
    uint8_t& getItemLifeCountType() { return mItemLifeCountType; }
    void setItem(uint8_t slot, uint8_t i_no) {
        mItemSlot = slot;
        mItemID = i_no;
    }

    void setZStatus(uint8_t status, uint8_t flag) {
        mZStatus = status;
        mZSetFlag = flag;
    }
    void setRStatus(uint8_t status, uint8_t flag) {
        mRStatus = status;
        mRSetFlag = flag;
    }
    void setDoStatus(uint8_t status, uint8_t flag) {
        mDoStatus = status;
        mDoSetFlag = flag;
    }
    void setAStatus(uint8_t status, uint8_t flag) {
        mAStatus = status;
        mASetFlag = flag;
    }
    void setBottleStatus(uint8_t status, uint8_t flag) {
        mBottleStatus = status;
        mBottleSetFlag = flag;
    }
    void setItemLifeCount(float hearts, uint8_t type) {
        mItemLifeCount += hearts;
        mItemLifeCountType = type;
    }
    void setItemRupeeCount(int rupees) { mItemRupeeCount += rupees; }
    void setItemMagicCount(int16_t magic) { mItemMagicCount += magic; }
    void setItemMaxMagicCount(int16_t max) { mItemMaxMagicCount += max; }
    void setItemArrowNumCount(int16_t arrows) { mItemArrowNumCount += arrows; }
    void setItemPachinkoNumCount(int16_t seeds) { mItemPachinkoNumCount += seeds; }
    void setItemKeyNumCount(int16_t keys) { mItemKeyNumCount += keys; }
    void setItemMaxLifeCount(int16_t max) { mItemMaxLifeCount += max; }
    void setOxygen(int oxygen) { mOxygen = oxygen; }
    void setNowOxygen(int oxygen) { mNowOxygen = oxygen; }
    void setMaxOxygen(int max) { mMaxOxygen = max; }
    uint8_t getDoStatus(void) { return mDoStatus; }
    uint8_t getRStatus(void) { return mRStatus; }
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
    /* 0x04CA0 */ uint8_t field_0x4ca0[12];
#endif
    /* 0x04C9C */ dVibration_c mVibration; /* Wii: +0x10 */
    /* 0x04D2C */ uint8_t field_0x4d2c[4];
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
    /* 0x04E0C */ uint8_t mWindowNum;
    /* 0x04E0D */ uint8_t mLayerOld;
    /* 0x04E0E */ uint16_t mStatus;
    /* 0x04E10 */ dDlst_window_c mWindow[1];
    /* 0x04E3C */ dComIfG_camera_info_class mCameraInfo[1];
    /* 0x04E74 */ daAlink_c* mPlayer[1];
    /* 0x04E78 */ int8_t mPlayerCameraID[4];
    /* 0x04E7C */ void* mPlayerPtr[2];
    /* 0x04E84 */ void* mMsgObjectClass;
    /* 0x04E88 */ float mItemLifeCount;
    /* 0x04E8C */ int mItemRupeeCount;
    /* 0x04E90 */ int16_t mItemKeyNumCount;
    /* 0x04E92 */ int16_t mItemMaxLifeCount;
    /* 0x04E94 */ int16_t mItemMagicCount;
    /* 0x04E96 */ int16_t mItemNowMagicCount;
    /* 0x04E98 */ int16_t mItemMaxMagicCount;
    /* 0x04E9A */ int16_t field_0x4e9a;
    /* 0x04E9C */ int mItemOilCount;
    /* 0x04EA0 */ int mItemNowOil;
    /* 0x04EA4 */ int mItemMaxOilCount;
    /* 0x04EA8 */ int mOxygen;
    /* 0x04EAC */ int mNowOxygen;
    /* 0x04EB0 */ int mMaxOxygen;
    /* 0x04EB4 */ int mOxygenCount;
    /* 0x04EB8 */ int mMaxOxygenCount;
    /* 0x04EBC */ int16_t mItemArrowNumCount;
    /* 0x04EBE */ int16_t mItemPachinkoNumCount;
    /* 0x04EC0 */ int16_t mItemMaxArrowNumCount;
    /* 0x04EC2 */ int16_t mItemBombNumCount[3];
    /* 0x04EC8 */ uint8_t field_0x4ec8[4];
    /* 0x04ECC */ int16_t mItemMaxBombNumCount1;
    /* 0x04ECE */ int16_t mItemMaxBombNumCount2;
    /* 0x04ED0 */ uint8_t field_0x4ed0[6];
    /* 0x04ED6 */ int16_t mItemMaxBombNumCount3;
    /* 0x04ED8 */ uint8_t field_0x4ed8[6];
    /* 0x04EDE */ uint16_t mItemNowLife;
    /* 0x04EE0 */ uint8_t field_0x4ee0[2];
    /* 0x04EE2 */ uint8_t mMesgStatus;
    /* 0x04EE3 */ uint8_t field_0x4ee3;
    /* 0x04EE4 */ uint8_t mRStatus;
    /* 0x04EE5 */ uint8_t mAStatus;  // B button
    /* 0x04EE6 */ uint8_t field_0x4ee6;
    /* 0x04EE7 */ uint8_t mNunStatus;
    /* 0x04EE8 */ uint8_t mBottleStatus;
    /* 0x04EE9 */ uint8_t mRemoConStatus;
    /* 0x04EEA */ uint8_t field_0x4eea[2];
    /* 0x04EEC */ uint8_t mDoStatus;  // A button
    /* 0x04EED */ uint8_t field_0x4eed;
    /* 0x04EEE */ uint8_t m3DStatus;
    /* 0x04EEF */ uint8_t field_0x4eef;  // related to NunStatusForce
    /* 0x04EF0 */ uint8_t field_0x4ef0;  // related to NunStatus
    /* 0x04EF1 */ uint8_t field_0x4ef1;  // related to RemoConStatusForce
    /* 0x04EF2 */ uint8_t field_0x4ef2;  // related to RemoConStatus
    /* 0x04EF3 */ uint8_t field_0x4ef3[2];
    /* 0x04EF5 */ uint8_t m3DDirection;
    /* 0x04EF6 */ uint8_t m3DDirectionForce;
    /* 0x04EF7 */ uint8_t mCStickStatus;
    /* 0x04EF8 */ uint8_t mCStickDirection;
    /* 0x04EF9 */ uint8_t mCStickDirectionForce;
    /* 0x04EFA */ uint8_t mSButtonStatus;
    /* 0x04EFB */ uint8_t mZStatus;
    /* 0x04EFC */ uint8_t mRStatusForce;
    /* 0x04EFD */ uint8_t mAStatusForce;
    /* 0x04EFE */ uint8_t field_0x4efe;
    /* 0x04EFF */ uint8_t field_0x4eff;  // related to NunStatusForce
    /* 0x04F00 */ uint8_t mBottleStatusForce;
    /* 0x04F01 */ uint8_t field_0x4f01;  // related to RemoConStatusForce
    /* 0x04F02 */ uint8_t field_0x4f02[2];
    /* 0x04F04 */ uint8_t mDoStatusForce;
    /* 0x04F05 */ uint8_t mTouchStatusForce;
    /* 0x04F06 */ uint8_t m3DStatusForce;
    /* 0x04F07 */ uint8_t mCStickStatusForce;
    /* 0x04F08 */ uint8_t mSButtonStatusForce;
    /* 0x04F09 */ uint8_t mZStatusForce;
    /* 0x04F0A */ uint8_t mRSetFlag;
    /* 0x04F0B */ uint8_t mASetFlag;
    /* 0x04F0C */ uint8_t field_0x4f0c;
    /* 0x04F0D */ uint8_t mNunSetFlag;
    /* 0x04F0E */ uint8_t mBottleSetFlag;
    /* 0x04F0F */ uint8_t mRemoConSetFlag;
    /* 0x04F10 */ uint8_t field_0x4f10[2];
    /* 0x04F12 */ uint8_t mDoSetFlag;
    /* 0x04F13 */ uint8_t m3DSetFlag;
    /* 0x04F14 */ uint8_t mCStickSetFlag;
    /* 0x04F15 */ uint8_t mSButtonSetFlag;
    /* 0x04F16 */ uint8_t mZSetFlag;
    /* 0x04F17 */ uint8_t mRSetFlagForce;
    /* 0x04F18 */ uint8_t mASetFlagForce;
    /* 0x04F19 */ uint8_t field_0x4f19;
    /* 0x04F1A */ uint8_t field_0x4f1a;  // related to NunStatusForce
    /* 0x04F1B */ uint8_t mBottleSetFlagForce;
    /* 0x04F1C */ uint8_t field_0x4f1c;  // related to RemoConStatusForce
    /* 0x04F1D */ uint8_t field_0x4f1d[2];
    /* 0x04F1F */ uint8_t mDoSetFlagForce;
    /* 0x04F20 */ uint8_t m3DSetFlagForce;
    /* 0x04F21 */ uint8_t mCStickSetFlagForce;
    /* 0x04F22 */ uint8_t mSButtonSetFlagForce;
    /* 0x04F23 */ uint8_t mZSetFlagForce;
    /* 0x04F24 */ uint8_t mXStatus;
    /* 0x04F25 */ uint8_t mXStatusForce;
    /* 0x04F26 */ uint8_t field_0x4fbe;  // related to XStatus
    /* 0x04F27 */ uint8_t mXSetFlagForce;
    /* 0x04F28 */ uint8_t mYStatus;
    /* 0x04F29 */ uint8_t mYStatusForce;
    /* 0x04F2A */ uint8_t mYSetFlag;
    /* 0x04F2B */ uint8_t mYSetFlagForce;
    /* 0x04F2C */ uint8_t mNunZStatus;
    /* 0x04F2D */ uint8_t mNunZSetFlag;
    /* 0x04F2E */ uint8_t field_0x4fc6;  // related to NunZStatusForce
    /* 0x04F2F */ uint8_t field_0x4fc7;  // related to NunZStatusForce
    /* 0x04F30 */ uint8_t mNunCStatus;
    /* 0x04F31 */ uint8_t mNunCSetFlag;
    /* 0x04F32 */ uint8_t field_0x4fca;  // related to NunCStatusForce
    /* 0x04F33 */ uint8_t field_0x4fcb;  // related to NunCStatusForce
    /* 0x04F34 */ uint8_t mSelectItem[8];
    /* 0x04F3C */ uint8_t mSelectEquip[6];
    /* 0x04F42 */ uint8_t mBaseAnimeID;
    /* 0x04F43 */ uint8_t mFaceAnimeID;
    /* 0x04F44 */ uint8_t mNowAnimeID;
    /* 0x04F45 */ uint8_t mItemSlot;
    /* 0x04F46 */ uint8_t mItemID;
    /* 0x04F47 */ uint8_t field_0x4f47[2];
    /* 0x04F49 */ uint8_t mDirection;
    /* 0x04F4A */ uint8_t field_0x4f4a;
    /* 0x04F4B */ uint8_t field_0x4f4b;  // related to itemInit
    /* 0x04F4C */ uint8_t field_0x4f4c;  // related to itemInit
    /* 0x04F4D */ uint8_t field_0x4f4d;
    /* 0x04F4E */ uint8_t mMesgCancelButton;
    /* 0x04F4F */ uint8_t field_0x4f4f[2];
    /* 0x04F51 */ uint8_t mGameoverStatus;
    /* 0x04F52 */ uint8_t field_0x4f52[5];
    /* 0x04F57 */ uint8_t mHeapLockFlag;
    /* 0x04F58 */ uint8_t mSubHeapLockFlag[2];
    /* 0x04F5A */ uint8_t mNowVibration;
    /* 0x04F5B */ uint8_t field_0x4f5b[2];
    /* 0x04F5D */ uint8_t mWolfAbility;
    /* 0x04F5E */ uint8_t field_0x4f5e[11];
    /* 0x04F69 */ uint8_t mNeedLightDropNum;
    /* 0x04F6A */ uint8_t field_0x4f6a[18];
    /* 0x04F7C */ uint8_t mMesgBgm;
    /* 0x04F7D */ bool mPauseFlag;
    /* 0x04F7E */ uint8_t mItemLifeCountType;
    /* 0x04F7F */ uint8_t mOxygenShowFlag;
    /* 0x04F80 */ uint8_t mShow2D;
    /* 0x04F81 */ uint8_t field_0x4f81[3];
    /* 0x04F84 */ JKRExpHeap* mExpHeap2D;
    /* 0x04F88 */ JKRExpHeap* mSubExpHeap2D[2];
    /* 0x04F90 */ JKRExpHeap* mMsgExpHeap;
    /* 0x04F94 */ char field_0x4F94[8];  // related to setWarpItemData
    /* 0x04F9C */ cXyz field_0x4f9c;     // related to setWarpItemData
    /* 0x04FA8 */ int16_t field_0x4fa8;
    /* 0x04FAA */ int8_t field_0x4faa;   // related to setWarpItemData
    /* 0x04FAB */ uint8_t field_0x4fab;  // related to setWarpItemData
    /* 0x04FAC */ uint8_t field_0x4fac;  // related to setWarpItemData
    /* 0x04FAD */ uint8_t field_0x4fad[3];
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
    /* 0x04FE4 */ uint8_t field_0x4fe4[0x14];
    /* 0x04FF8 */ __d_timer_info_c mTimerInfo;
    /* 0x0500C */ dDlst_window_c* mCurrentWindow;
    /* 0x05010 */ void* mCurrentView;
    /* 0x05014 */ void* mCurrentViewport;
    /* 0x05018 */ J2DGrafContext* mCurrentGrafPort;
    /* 0x0501C */ void* mItemTable;
    /* 0x0501D */ uint8_t field_0x501d[4];
    /* 0x05024 */ char mLastPlayStageName[8];
};

class dComIfG_inf_c {
public:
    /* 0x00000 */ dSv_info_c info;
    /* 0x00F38 */ dComIfG_play_c play;
    /* 0x05F64 */ uint8_t field_0x5F64[0x17EAC];
};  // Size: 0x1DE10

#ifdef GCN_PLATFORM
static_assert(sizeof(dComIfG_inf_c) == 0x1DE10);
#endif

extern dComIfG_inf_c g_dComIfG_gameInfo;

extern volatile uint8_t bossFlags;

struct TitleScreenPtr {
    uint8_t _p0[0x59];             // 0x00
    uint8_t trigger_on_next_load;  // 0x59
};
struct TitleScreenInfo {
    TitleScreenPtr* title_screen_info;
};
extern TitleScreenInfo l_fpcNdRq_Queue;

LIBTP_DEFINE_FUNC(getLayerNo_common_common__14dComIfG_play_cFPCcii,
                  dComIfG_play_c__getLayerNo_common_common_char_const____int__int_, int,
                  tp_getLayerNo, (const char* stageName, int roomId, int layerOverride))

// Inline Functions
inline void dComIfGs_setItem(int slot_no, uint8_t item_no) {
    dSv_player_item_c__setItem(&g_dComIfG_gameInfo.info.getPlayer().getItem(), slot_no, item_no);
}
inline uint8_t dComIfGs_getItem(int slot_no, bool is_combo_item) {
    return dSv_player_item_c__getItem(&g_dComIfG_gameInfo.info.getPlayer().getItem(), slot_no,
                                      is_combo_item);
}
inline void dComIfGp_setRStatus(uint8_t status, uint8_t flag) {
    g_dComIfG_gameInfo.play.setRStatus(status, flag);
}
inline void dComIfGp_setDoStatus(uint8_t status, uint8_t flag) {
    g_dComIfG_gameInfo.play.setDoStatus(status, flag);
}
inline void dComIfGp_setAStatus(uint8_t status, uint8_t flag) {
    g_dComIfG_gameInfo.play.setAStatus(status, flag);
}
inline void dComIfGp_setZStatus(uint8_t status, uint8_t flag) {
    g_dComIfG_gameInfo.play.setZStatus(status, flag);
}
inline void dComIfGp_setItemMagicCount(int16_t amount) {
    g_dComIfG_gameInfo.play.setItemMagicCount(amount);
}
inline void dComIfGp_setItemMaxMagicCount(int16_t max) {
    g_dComIfG_gameInfo.play.setItemMaxMagicCount(max);
}
inline void dComIfGp_setItemArrowNumCount(int16_t amount) {
    g_dComIfG_gameInfo.play.setItemArrowNumCount(amount);
}
inline void dComIfGp_setItemPachinkoNumCount(int16_t amount) {
    g_dComIfG_gameInfo.play.setItemPachinkoNumCount(amount);
}
inline void dComIfGp_setItemKeyNumCount(int16_t amount) {
    g_dComIfG_gameInfo.play.setItemKeyNumCount(amount);
}
inline void dComIfGp_setItemMaxLifeCount(int16_t max) {
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
inline void dComIfGs_setOil(uint16_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setOil(amount);
}
inline void dComIfGs_setMaxOil(uint16_t max) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMaxOil(max);
}
inline void dComIfGs_setWalletSize(uint8_t size) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setWalletSize(size);
}
inline void dComIfGs_setMagic(uint8_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMagic(amount);
}
inline void dComIfGs_setMaxMagic(uint8_t max) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMaxMagic(max);
}
inline void dComIfGs_setRupee(uint16_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setRupee(amount);
}
inline void dComIfGs_setLife(uint16_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setLife(amount);
}
inline void dComIfGs_setMaxLife(uint8_t max) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setMaxLife(max);
}
/*
inline void dComIfGs_onDungeonItemBossKey(void) {
    g_dComIfG_gameInfo.info.getMemory().getBit().onDungeonItemBossKey();
}
inline void dComIfGs_setCollectSword(uint8_t sword_id) {
    g_dComIfG_gameInfo.info.getSavedata().getCollect().setCollect(COLLECT_SWORD, sword_id);
}
inline void dComIfGs_setCollectShield(uint8_t shield_id) {
    g_dComIfG_gameInfo.info.getSavedata().getCollect().setCollect(COLLECT_SHIELD, shield_id);
}
inline void dComIfGs_setCollectClothes(uint8_t clothes_id) {
    g_dComIfG_gameInfo.info.getSavedata().getCollect().setCollect(COLLECT_CLOTHING, clothes_id);
}
inline void dComIfGs_setRodTypeLevelUp(void) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setRodTypeLevelUp();
}*/
inline void dComIfGs_setArrowNum(uint8_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setArrowNum(amount);
}
inline void dComIfGs_setPachinkoNum(uint8_t amount) {
    g_dComIfG_gameInfo.info.getPlayer().getItemRecord().setPachinkoNum(amount);
}
inline void dComIfGs_setArrowMax(uint8_t max) {
    g_dComIfG_gameInfo.info.getPlayer().getItemMax().setArrowNum(max);
}
inline uint8_t dComIfGs_getPachinkoNum() {
    return g_dComIfG_gameInfo.info.getPlayer().getItemRecord().getPachinkoNum();
}
inline uint8_t dComIfGs_getPachinkoMax(void) {
    return 50;
}
/*
inline void dComIfGs_setEmptyBombBag(void) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBombBag();
}
inline void dComIfGs_setEmptyBombBag(uint8_t type, uint8_t amount) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBombBag(type, amount);
}
inline void dComIfGs_setEmptyBombBagItemIn(uint8_t type, bool unk) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBombBagItemIn(type, unk);
}
inline void dComIfGs_setEmptyBottle(void) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBottle();
}
inline void dComIfGs_setEmptyBottle(uint8_t type) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBottle(type);
}
inline void dComIfGs_setEmptyBottleItemIn(uint8_t type) {
    g_dComIfG_gameInfo.info.getSavedata().getItem().setEmptyBottleItemIn(type);
}
inline void dComIfGs_onEventBit(uint16_t id) {
    g_dComIfG_gameInfo.info.getSavedata().getEventFlags().onEventBit(id);
}
inline void dComIfGs_onLightDropFlag(uint8_t area_id) {
    g_dComIfG_gameInfo.info.getSavedata().getLightDrop().onLightDropGetFlag(area_id);
}
inline void dComIfGs_onSwitch(int param1, int param2) {
    g_dComIfG_gameInfo.getInfo().onSwitch(param1, param2);
}
inline int dComIfGs_isCollectSword(uint8_t sword_id) {
    return g_dComIfG_gameInfo.info.getSavedata().getCollect().isCollect(COLLECT_SWORD, sword_id);
}
inline int dComIfGs_isCollectClothing(uint8_t clothing_id) {
    return g_dComIfG_gameInfo.info.getSavedata().getCollect().isCollect(COLLECT_CLOTHING,
                                                                         clothing_id);
}
inline uint8_t dComIfGs_checkBottle(uint8_t type) {
    return g_dComIfG_gameInfo.info.getSavedata().getItem().checkBottle(type);
}
inline int dComIfGs_isLightDropGetFlag(uint8_t area_id) {
    return g_dComIfG_gameInfo.info.getSavedata().getLightDrop().isLightDropGetFlag(area_id);
}*/
inline uint8_t dComIfGs_getArrowMax(void) {
    return g_dComIfG_gameInfo.info.getSavedata().getPlayer().getItemMax().getArrowNum();
}
inline uint8_t dComIfGs_getCollectSmell(void) {
    return g_dComIfG_gameInfo.info.getSavedata().getPlayer().getPlayerStatusA().getSelectEquip(3);
}
inline uint8_t dComIfGs_getPohSpiritNum(void) {
    return g_dComIfG_gameInfo.info.getSavedata().getPlayer().getCollect().getPohNum();
}
inline void dComIfGs_setPohSpiritNum(uint8_t num) {
    return g_dComIfG_gameInfo.info.getSavedata().getPlayer().getCollect().setPohNum(num);
}
inline uint8_t dComIfGs_getKeyNum(void) {
    return g_dComIfG_gameInfo.info.getMemory().getBit().getKeyNum();
}
/*
inline void dComIfGs_onItemFirstBit(uint8_t i_no) {
    g_dComIfG_gameInfo.info.getSavedata().getGetItem().onFirstBit(i_no);
}*/
inline uint16_t dComIfGs_getMaxLife(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getMaxLife();
}
/*
inline void dComIfGs_offEventBit(uint16_t event) {
    g_dComIfG_gameInfo.info.getSavedata().getEventFlags().offEventBit(event);
}*/
inline const char* dComIfGs_getLastWarpMarkStageName(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerLastMarkInfo().getName();
}
inline cXyz dComIfGs_getLastWarpMarkPlayerPos(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerLastMarkInfo().getPos();
}
inline int16_t dComIfGs_getLastWarpMarkPlayerAngleY(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerLastMarkInfo().getAngleY();
}
inline int8_t dComIfGs_getLastWarpMarkRoomNo(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerLastMarkInfo().getRoomNo();
}
inline char dComIfGs_getLastWarpAcceptStage(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerLastMarkInfo().getWarpAcceptStage();
}
inline uint8_t dComIfGs_getSelectEquipClothes(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectEquip(COLLECT_CLOTHING);
}
inline uint8_t dComIfGs_getSelectEquipSword(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectEquip(COLLECT_SWORD);
}
inline uint8_t dComIfGs_getSelectEquipShield(void) {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getSelectEquip(COLLECT_SHIELD);
}
/*
inline uint8_t dComIfGs_getLightDropNum(uint8_t area_id) {
    return g_dComIfG_gameInfo.info.getSavedata().getLightDrop().getLightDropNum(area_id);
}*/
inline uint8_t dComIfGs_getSelectItemIndex(int idx) {
    return dSv_player_status_a_c__getSelectItemIndex(
        &g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA(), idx);
}

LIBTP_DEFINE_FUNC(dComIfGs_setSelectItemIndex__FiUc,
                  dComIfGs_setSelectItemIndex_int__unsigned_char_, void,
                  dComIfGs_setSelectItemIndex, (int32_t idx, uint8_t item))

LIBTP_DEFINE_FUNC(dComIfGs_getMixItemIndex__Fi, dComIfGs_getMixItemIndex_int_, uint8_t,
                  dComIfGs_getMixItemIndex, (int32_t idx))

LIBTP_DEFINE_FUNC(dComIfGs_setMixItemIndex__FiUc, dComIfGs_setMixItemIndex_int__unsigned_char_,
                  void, dComIfGs_setMixItemIndex, (int32_t idx, uint8_t item))

LIBTP_DEFINE_FUNC(setRoom__13dSv_restart_cFRC4cXyzsSc, 
                  setRoom__13dSv_restart_cFRC4cXyzsSc, // wrong, fix later
                  void, dSv_restart_c__setRoom, (const cXyz& i_position, int16_t i_angleY, int8_t i_roomNo))

inline void dComIfGp_setItem(uint8_t slot, uint8_t i_no) {
    g_dComIfG_gameInfo.play.setItem(slot, i_no);
}
/*
inline uint32_t dComIfGp_getNowVibration(void) {
    return g_dComIfG_gameInfo.play.getNowVibration();
}
inline char* dComIfGp_getStartStageName(void) {
    return g_dComIfG_gameInfo.play.getStartStageName();
}*/

inline void dComIfGs_setStartPoint(int16_t point) {
    g_dComIfG_gameInfo.info.getRestart().setStartPoint(point);
}

inline void dComIfGs_setRestartRoom(const cXyz& i_position, s16 i_angle, s8 i_roomNo) {
    g_dComIfG_gameInfo.info.getRestart().setRoom(i_position, i_angle, i_roomNo);
}

inline void dComIfGp_setNextStage(const char* stage, int8_t room, int16_t point, int8_t layer,
                                  int8_t wipe, uint8_t wipe_speed) {
    dStage_nextStage_c__set(&g_dComIfG_gameInfo.play.mNextStage, stage, room, point, layer, wipe,
                            wipe_speed);
}

inline void dComIfGs_setTransformStatus(uint8_t status) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().setTransformStatus(status);
}

inline uint8_t dComIfGs_getTransformStatus() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getTransformStatus();
}

inline daAlink_c* dComIfGp_getPlayer() {
    return g_dComIfG_gameInfo.play.mPlayer[0];
}

inline uint8_t dComIfGs_getLightDropNum(uint8_t area) {
    return dSv_light_drop_c__getLightDropNum(&g_dComIfG_gameInfo.info.getPlayer().getLightDrop(),
                                             area);
}

inline void dComIfGs_setLightDropNum(uint8_t area, uint8_t num) {
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

LIBTP_DEFINE_FUNC(dComIfGp_getEvent__Fv, dComIfGp_getEvent__Fv, dEvt_control_c&, dComIfGp_getEvent,
                  (void))

LIBTP_DEFINE_FUNC(dComIfGp_getEventManager__Fv, , dEvent_manager_c&, dComIfGp_getEventManager,
                  (void))
#endif

inline void dComIfGs_setTime(float pTime) {
    g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().setTime(pTime);
}

inline float dComIfGs_getTime() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB().getTime();
}

inline dSv_save_c& dComIfGs_getSavedata() {
    return g_dComIfG_gameInfo.info.mSavedata;
}

inline uint16_t dComIfGs_getLife() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getLife();
}

inline void dComIfGs_setBombNum(uint8_t idx, uint8_t num) {
    dSv_player_item_record_c__setBombNum(&g_dComIfG_gameInfo.info.getPlayer().getItemRecord(), idx,
                                         num);
}

#ifdef WII_PLATFORM
inline bool dComIfGs_isItemFirstBit(uint8_t flag) {
    return dSv_player_get_item_c__isFirstBit_unsigned_char__const(
        &g_dComIfG_gameInfo.info.getPlayer().getGetItem(), flag);
}
#else

LIBTP_DEFINE_FUNC(dComIfGs_isItemFirstBit__FUc, dComIfGs_isItemFirstBit__FUc, bool,
                  dComIfGs_isItemFirstBit, (uint8_t item))
#endif

inline uint8_t dComIfGs_getWalletSize() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getWalletSize();
}

inline void dComIfGs_onItemFirstBit(uint8_t item) {
    dSv_player_get_item_c__onFirstBit(&g_dComIfG_gameInfo.info.getPlayer().getGetItem(), item);
}

inline void dComIfGs_offItemFirstBit(uint8_t item) {
    dSv_player_get_item_c__offFirstBit(&g_dComIfG_gameInfo.info.getPlayer().getGetItem(), item);
}

inline bool dComIfGs_isEventBit(uint16_t flag) {
    return dSv_event_c__isEventBit(&g_dComIfG_gameInfo.info.mSavedata.mEvent, flag);
}

inline void dComIfGs_onEventBit(uint16_t flag) {
    dSv_event_c__onEventBit(&g_dComIfG_gameInfo.info.mSavedata.mEvent, flag);
}

inline void dComIfGs_offEventBit(uint16_t flag) {
    dSv_event_c__offEventBit(&g_dComIfG_gameInfo.info.mSavedata.mEvent, flag);
}

inline void dComIfGs_setKeyNum(uint8_t num) {
    g_dComIfG_gameInfo.info.getMemory().getBit().setKeyNum(num);
}

inline bool dComIfGs_isTransformLV(int32_t flag) {
    return dSv_player_status_b_c__isTransformLV(
        &g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB(), flag);
}

inline void dComIfGs_onTransformLV(int32_t flag) {
    dSv_player_status_b_c__onTransformLV(&g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusB(),
                                         flag);
}

inline void dComIfGs_offTransformLV(int32_t flag) {
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

inline uint8_t dComIfGs_getArrowNum() {
    return g_dComIfG_gameInfo.info.getSavedata().getPlayer().getItemRecord().getArrowNum();
}

inline uint8_t dComIfGs_getBombNum(uint8_t bagIdx) {
    return dSv_player_item_record_c__getBombNum(
        &g_dComIfG_gameInfo.info.getPlayer().getItemRecord(), bagIdx);
}

#ifdef WII_PLATFORM
inline uint16_t dComIfGs_getRupee() {
    return g_dComIfG_gameInfo.info.getPlayer().getPlayerStatusA().getRupee();
}
#else

LIBTP_DEFINE_FUNC(dComIfGs_getRupee__Fv, dComIfGs_getRupee__Fv, uint16_t, dComIfGs_getRupee, (void))
#endif

LIBTP_DEFINE_FUNC(dComIfGs_onOneZoneSwitch__Fii, dComIfGs_onOneZoneSwitch_int__int_, void,
                  dComIfGs_onOneZoneSwitch, (int, int))

LIBTP_DEFINE_FUNC(dComIfGs_onZoneSwitch__Fii, dComIfGs_onZoneSwitch_int__int_, void,
                  dComIfGs_onZoneSwitch, (int, int))

class dComIfAc_gameInfo {
public:
    uint8_t field_0x0[4];
    bool freeze;
    uint8_t field_0x6[3];
};

extern dComIfAc_gameInfo g_dComIfAc_gameInfo;
extern uint32_t fopAc_ac_c__stopStatus;

#endif /* D_COM_D_COM_INF_GAME_H */
