#ifndef D_METER_D_METER2_INFO_H
#define D_METER_D_METER2_INFO_H

#include "../msg/d_msg_flow.h"
#include "../menu/d_menu_window.h"

class dMeterMap_c {};

struct CPaneMgr {};

class dMeter2_c {};

class dMeter2Info_c {
public:
    class WarpInfo_c {
    public:
        /* 0x00 */ char mStageName[8];
        /* 0x08 */ cXyz pos;
        /* 0x14 */ s16 mAngle;
        /* 0x16 */ u8 mRoomNo;
        /* 0x17 */ u8 unk79;
        /* 0x18 */ u8 mWarpPlayerNo;
    };

    u8& getDirectUseItem() { return mDirectUseItem; }
    dMeterMap_c* getMeterMapClass() { return mMeterMap; }
    void offUseButton(int pButton) { mUseButton &= ~(u16)pButton; }

    /* 0x00 */ void* vtable;
    /* 0x04 */ u8 unk4[4];
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u32 unk12;
    /* 0x10 */ void* mMsgResource;
    /* 0x14 */ void* mStageMsgResource;
    /* 0x18 */ void* mMsgUnitResource;
    /* 0x1C */ dMeter2_c* mMeterClass;
    /* 0x20 */ dMeterMap_c* mMeterMap;
    /* 0x24 */ dMw_c* mMenuWindowClass;
    /* 0x28 */ CPaneMgr* mMeterItemPanePtr[4];
    /* 0x38 */ WarpInfo_c mWarpInfo;
    /* 0x54 */ f32 unk84;
    /* 0x58 */ f32 unk88;
    /* 0x5C */ f32 unk92;
    /* 0x60 */ f32 unk96;
    /* 0x64 */ f32 unk100;
    /* 0x68 */ f32 unk104;
    /* 0x6C */ f32 unk108;
    /* 0x70 */ f32 m2DWidth;
    /* 0x74 */ f32 m2DHeight;
    /* 0x78 */ f32 m2DPosH;
    /* 0x7C */ f32 m2DPosV;
    /* 0x80 */ f32 unk128;
    /* 0x84 */ u32 mTimeMs;
    /* 0x88 */ u32 mMsgTimeMs;
    /* 0x8C */ u32 mMeterString;
    /* 0x90 */ u32 mTempBits;
    /* 0x94 */ s16 mMsgKeyWaitTimer;
    /* 0x96 */ u16 mHorseLifeCount;
    /* 0x98 */ u16 unk152;
    /* 0x9A */ u16 mHotSpringTimer[4];
    /* 0xA2 */ u16 mSub2DStatus;
    /* 0xA4 */ u16 mFloatingFlowID;
    /* 0xA6 */ u16 mFloatingMessageID;
    /* 0xA8 */ s16 mFloatingMessageTimer;
    /* 0xAA */ u16 mMapKeyDirection;
    /* 0xAC */ u16 mBlinkButton;
    /* 0xAE */ u16 mUseButton;
    /* 0xB0 */ u16 mGameStatus;
    /* 0xB2 */ u16 mTouchKeyCheck;
    /* 0xB4 */ u16 mWindowAccept;
    /* 0xB6 */ u16 mOilGaugeBackUp;
    /* 0xB8 */ u8 mDirectUseItem;
    /* 0xB9 */ u8 mWindowStatus;
    /* 0xBA */ u8 unk186;
    /* 0xBB */ u8 mMaxCount;
    /* 0xBC */ u8 mNowCount;
    /* 0xBD */ u8 mShopTalkFlag;
    /* 0xBE */ u8 unk190;
    /* 0xBF */ u8 mMapStatus;
    /* 0xC0 */ u8 mWarpStatus;
    /* 0xC1 */ u8 mPauseStatus;
    /* 0xC2 */ u8 mGameOverType;
    /* 0xC3 */ u8 mInsectSelectType;
    /* 0xC4 */ u32 unk196;
    /* 0xC8 */ u32 unk200;
    /* 0xCC */ u8 unk204;
    /* 0xCD */ u8 unk205;
    /* 0xCE */ u8 unk206;
    /* 0xCF */ u8 unk207;
    /* 0xD0 */ double unk208;
    /* 0xD8 */ u8 unk216;
    /* 0xD9 */ u8 unk217;
    /* 0xDA */ u8 unk218;
    /* 0xDB */ u8 unk219;
    /* 0xDC */ u8 mRentalBombBag;
    /* 0xDD */ u8 mMiniGameItemSetFlag;
    /* 0xDE */ u8 mMiniGameCount;
    /* 0xDF */ u8 mCollectCursorPosX;
    /* 0xE0 */ u8 mCollectCursorPosY;
    /* 0xE1 */ u8 mTableMapRegionNo;
    /* 0xE2 */ u8 mGoldWolfMapType;
    /* 0xE3 */ u8 mLightDropGetFlag[3];
    /* 0xE6 */ u8 mLifeGaugeSE;
    /* 0xE7 */ u8 unk231;
    /* 0xE8 */ u8 mItemExplainWindowStatus;
    /* 0xE9 */ char mSaveStageName[8];
    /* 0xF1 */ u8 mFloatingMessageWakuVisible;
    /* 0xF2 */ u8 mMapDrugFlag;
    /* 0xF3 */ u8 unk243[5];
};

extern dMeter2Info_c g_meter2_info;

inline dMeterMap_c* dMeter2Info_getMeterMapClass() {
    return g_meter2_info.getMeterMapClass();
}

#endif /* D_METER_D_METER2_INFO_H */
