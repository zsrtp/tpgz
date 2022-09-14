#ifndef D_METER_D_METER_HIO_H
#define D_METER_D_METER_HIO_H

#include <stdint.h>
#include "../../addrs.h"
#include "../../JSystem/JUtility.h"

class dMeter_menuHIO_c {
public:
    /* 0x0 */ void* vtable;
    /* 0x4 */ uint8_t field_0x4[2];
    /* 0x6 */ int16_t mGameover;
};  // Size: 0x8

static_assert(sizeof(dMeter_menuHIO_c) == 8);

class dMeter_drawCollectHIO_c {
public:
    enum {
        /* 0x0 */ VESSEL_HEART,
        /* 0x1 */ VESSEL_DECOR
    };

    /* 0x00 */ void* vtable;
    /* 0x04 */ uint8_t field_0x04[4];
    /* 0x08 */ float mUnselectItemScale;
    /* 0x0C */ float mSelectItemScale;
    /* 0x10 */ float mUnselectSaveOptionScale;
    /* 0x14 */ float mSelectSaveOptionScale;
    /* 0x18 */ float mBlueSmokePosX;
    /* 0x1C */ float mBlueSmokePosY;
    /* 0x20 */ float mBlueSmokeScale;
    /* 0x24 */ float mBlueSmokeAlpha;
    /* 0x28 */ cXyz mMaskMirrorPos;
    /* 0x34 */ float mMaskMirrorScale;
    /* 0x38 */ float mMaskMirrorAnimSpeed;
    /* 0x3C */ float mHeartVesselPosX;
    /* 0x40 */ float mHeartVesselPosY;
    /* 0x44 */ float mHeartVesselScale;
    /* 0x48 */ float mAButtonPosX;
    /* 0x4C */ float mAButtonPosY;
    /* 0x50 */ float mAButtonScale;
    /* 0x54 */ float mBButtonPosX;
    /* 0x58 */ float mBButtonPosY;
    /* 0x5C */ float mBButtonScale;
    /* 0x60 */ float mAButtonTextPosX;
    /* 0x64 */ float mAButtonTextPosY;
    /* 0x68 */ float mAButtonTextScale;
    /* 0x6C */ float mBButtonTextPosX;
    /* 0x70 */ float mBButtonTextPosY;
    /* 0x74 */ float mBButtonTextScale;
    /* 0x78 */ JUtility::TColor mVesselBack[2];
    /* 0x80 */ JUtility::TColor mVesselFront[2];
    /* 0x88 */ float mHeartPiecePosX;
    /* 0x8C */ float mHeartPiecePosY;
    /* 0x90 */ float mHeartPieceScale;
    /* 0x94 */ csXyz mMaskMirrorAngle;
    /* 0x9A */ bool field_0x9a;
    /* 0x9B */ bool mColorDebugON;
    /* 0x9C */ bool mButtonDebugON;
};  // Size = 0xA0

class dMeter_drawOptionHIO_c {
public:
    enum OptionType {
        /* 0x0 */ ATTENTION,
        /* 0x1 */ RUMBLE,
        /* 0x2 */ SOUND
    };

    /* 0x00 */ void* vtable;
    /* 0x04 */ uint8_t field_0x4[4];
    /* 0x08 */ float mArrowSize;
    /* 0x0C */ JUtility::TColor mSelectNameColor;
    /* 0x10 */ JUtility::TColor mSelectColor;
    /* 0x14 */ JUtility::TColor mUnselectColor;
    /* 0x18 */ float mWindowPosX;
    /* 0x1C */ float mWindowPosY;
    /* 0x20 */ float mWindowScale;
    /* 0x24 */ float mOptionTypeBGPosX[4];
    /* 0x34 */ float mTVsettingPosX;
    /* 0x38 */ float mPointerCalibrationPosX;
    /* 0x3C */ float mOptionTypeBGPosY[4];
    /* 0x4C */ float mTVsettingPosY;
    /* 0x50 */ float mPointerCalibrationPosY;
    /* 0x54 */ float mSelectBarScale;
    /* 0x58 */ float mUnselectBarScale;
    /* 0x5C */ float mBackgroundPosY;
    /* 0x60 */ float mArrowOffsetX;
    /* 0x64 */ float mArrowOffsetX_4x3;
    /* 0x68 */ int16_t mOpenFrames;
    /* 0x6A */ int16_t mCloseFrames;
    /* 0x6C */ bool mDebug;
    /* 0x6D */ uint8_t mBackgroundAlpha;
};  // Size: 0x70

class dMeter_drawLetterHIO_c {
public:
    enum {
        /* 0x0 */ WINDOW_FRAME,
        /* 0x1 */ LETTER_FRAME
    };

    /* 0x00 */ void* vtable;
    /* 0x04 */ uint8_t field_0x4[4];
    /* 0x08 */ float mSelectBarScale;
    /* 0x0C */ float mUnselectBarScale;
    /* 0x10 */ float mWindowPosX;
    /* 0x14 */ float mWindowPosY;
    /* 0x18 */ float mWindowScale;
    /* 0x1C */ float mLetterWindowPosX;
    /* 0x20 */ float mLetterWindowPosY;
    /* 0x24 */ float mLetterWindowScale;
    /* 0x28 */ float mLetterLinePosX;
    /* 0x2C */ float mLetterLinePosY;
    /* 0x30 */ int16_t mOpenFrame[2];
    /* 0x34 */ int16_t mCloseFrame[2];
    /* 0x38 */ int16_t mLetterNum;
    /* 0x3A */ uint8_t field_0x3a[2];
    /* 0x3C */ JUtility::TColor mSelectPageIconBack;
    /* 0x40 */ JUtility::TColor mSelectPageIconFront;
    /* 0x44 */ JUtility::TColor mSelectBarBack;
    /* 0x48 */ JUtility::TColor mSelectBarFront;
    /* 0x4C */ JUtility::TColor mSelectTextBack;
    /* 0x50 */ JUtility::TColor mSelectTextFront;
    /* 0x54 */ JUtility::TColor mLetterTextBack;
    /* 0x58 */ JUtility::TColor mLetterTextFront;
    /* 0x5C */ uint8_t mUnselectPageIconAlpha;
    /* 0x5D */ uint8_t mWindowBGAlpha;
    /* 0x5E */ uint8_t mLetterLineAlpha;
    /* 0x5F */ bool mDebugON;
};  // Size: 0x60

class dMeter_drawFishingHIO_c {
public:
    enum {
        /* 0x0 */ HYLIAN_BASS,
        /* 0x1 */ HYLIAN_LOACH,
        /* 0x2 */ HYLIAN_PIKE,
        /* 0x3 */ ORDON_CATFISH,
        /* 0x4 */ REEKFISH,
        /* 0x5 */ GREENGILL
    };

    /* 0x000 */ void* vtable;
    /* 0x004 */ uint8_t field_0x4[4];
    /* 0x008 */ float mFishIconScale[6];
    /* 0x020 */ float mFishIconPosX[6];
    /* 0x038 */ float mFishIconPosY[6];
    /* 0x050 */ float mFishNameScale[6];
    /* 0x068 */ float mFishNamePosX[6];
    /* 0x080 */ float mFishNamePosY[6];
    /* 0x098 */ float mFishLineScale[6];
    /* 0x0B0 */ float mFishLinePosX[6];
    /* 0x0C8 */ float mFishLinePosY[6];
    /* 0x0E0 */ float mFishSizeScale[6];
    /* 0x0F8 */ float mFishSizePosX[6];
    /* 0x110 */ float mFishSizePosY[6];
    /* 0x128 */ float mFishCountScale[6];
    /* 0x140 */ float mFishCountPosX[6];
    /* 0x158 */ float mFishCountPosY[6];
    /* 0x170 */ float mFishCountSizeScale[6];
    /* 0x188 */ float mFishCountSizePosX[6];
    /* 0x1A0 */ float mFishCountSizePosY[6];
    /* 0x1B8 */ float mFishInfoScale[6];
    /* 0x1D0 */ float mFishInfoPosX[6];
    /* 0x1E8 */ float mFishInfoPosY[6];
    /* 0x200 */ float mMaxSizeScale;
    /* 0x204 */ float mCaughtNumScale;
    /* 0x208 */ float mMaxSizePosX;
    /* 0x20C */ float mCaughtNumPosX;
    /* 0x210 */ float mCaughtNumPosX_4x3;
    /* 0x214 */ float mMaxSizePosY;
    /* 0x218 */ float mCaughtNumPosY;
    /* 0x21C */ int16_t mOpenFrames;
    /* 0x21E */ int16_t mCloseFrames;
    /* 0x220 */ int16_t mFishNum[6];
    /* 0x22C */ uint8_t field_0x22c[0x14];
    /* 0x240 */ uint8_t mFishSize[6];
    /* 0x246 */ uint8_t field_0x246[0xA];
    /* 0x250 */ bool mDebug;
};  // Size: 0x254

class dMeter_drawInsectHIO_c {
public:
    enum Type {
        /* 0x0 */ DEFAULT,
        /* 0x1 */ COLLECT,
        /* 0x2 */ AGITHA
    };

    /* 0x00 */ void* vtable;
    /* 0x04 */ uint8_t field_0x4[4];
    /* 0x08 */ float mUnselectInsectScale;
    /* 0x0C */ float mSelectInsectScale;
    /* 0x10 */ float mDescWindowPosX;
    /* 0x14 */ float mDescWindowPosY;
    /* 0x18 */ float mGiveOptionPosX_4x3;
    /* 0x1C */ float mGiveOptionPosX;
    /* 0x20 */ float mGiveOptionPosY_4x3;
    /* 0x24 */ float mGiveOptionPosY;
    /* 0x28 */ float mConfirmOptionPosX_4x3;
    /* 0x2C */ float mConfirmOptionPosX;
    /* 0x30 */ float mConfirmOptionPosY_4x3;
    /* 0x34 */ float mConfirmOptionPosY;
    /* 0x38 */ int16_t mOpenFrame;
    /* 0x3A */ int16_t mCloseFrame;
    /* 0x3C */ uint8_t mType;
    /* 0x3D */ bool mDebugON;
};  // Size: 0x40

class dMeter_drawCalibrationHIO_c {
public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ uint8_t field_0x4[4];
    /* 0x08 */ float mCircleScale;
    /* 0x0C */ float mCircleScale2;
    /* 0x10 */ int16_t mOpenFrames;
    /* 0x12 */ int16_t mCloseFrames;
    /* 0x14 */ int16_t mFlashFrameNum;
    /* 0x16 */ bool mDebug;
};  // Size: 0x18

class dMeter_drawSkillHIO_c {
public:
    enum {
        /* 0x0 */ WINDOW,
        /* 0x1 */ SKILL_DESC,
    };

    /* 0x00 */ void* vtable;
    /* 0x04 */ uint8_t field_0x4[4];
    /* 0x08 */ float mSelectBarScale;
    /* 0x0C */ float mUnselectBarScale;
    /* 0x10 */ float mSkillDescPosX;
    /* 0x14 */ float mSkillDescPosY;
    /* 0x18 */ float mSkillDescScale;
    /* 0x1C */ float mSkillTitlePosX;
    /* 0x20 */ float mSkillTitlePosY;
    /* 0x24 */ float mSkillTitleScale;
    /* 0x28 */ float mWindowLinePosX;
    /* 0x2C */ float mWindowLinePosY;
    /* 0x30 */ int16_t mOpenFrame[2];
    /* 0x34 */ int16_t mCloseFrame[2];
    /* 0x38 */ JUtility::TColor mSelectScrollIconBlack;
    /* 0x3C */ JUtility::TColor mSelectScrollIconWhite;
    /* 0x40 */ JUtility::TColor mUnselectScrollIconBlack;
    /* 0x44 */ JUtility::TColor mUnselectScrollIconWhite;
    /* 0x48 */ JUtility::TColor mSelectBarBlack;
    /* 0x4C */ JUtility::TColor mSelectBarWhite;
    /* 0x50 */ JUtility::TColor mSelectTextBlack;
    /* 0x54 */ JUtility::TColor mSelectTextWhite;
    /* 0x58 */ uint8_t field_0x58;
    /* 0x59 */ uint8_t mWindowBGalpha;
    /* 0x5A */ uint8_t mWindowLineAlpha;
    /* 0x5B */ bool mDebug;
};  // Size: 0x5C

class dMeter_drawEmpButtonHIO_c {
public:
    /* 0x000 */ void* vtable;
    /* 0x004 */ uint8_t field_0x4[4];
    /* 0x008 */ float mEmpButtonPosX;
    /* 0x00C */ float mEmpButtonPosY;
    /* 0x010 */ float mEmpButtonScale;
    /* 0x014 */ float mAButtonPosX;
    /* 0x018 */ float mAButtonPosY;
    /* 0x01C */ float mAButtonScale;
    /* 0x020 */ float mBButtonPosX;
    /* 0x024 */ float mBButtonPosY;
    /* 0x028 */ float mBButtonScale;
    /* 0x02C */ float mRButtonPosX;
    /* 0x030 */ float mRButtonPosY;
    /* 0x034 */ float mRButtonScale;
    /* 0x038 */ float mZButtonPosX;
    /* 0x03C */ float mZButtonPosY;
    /* 0x040 */ float mZButtonScale;
    /* 0x044 */ float m3DButtonPosX;
    /* 0x048 */ float m3DButtonPosY;
    /* 0x04C */ float m3DButtonScale;
    /* 0x050 */ float mCButtonPosX;
    /* 0x054 */ float mCButtonPosY;
    /* 0x058 */ float mCButtonScale;
    /* 0x05C */ float mSButtonPosX;
    /* 0x060 */ float mSButtonPosY;
    /* 0x064 */ float mSButtonScale;
    /* 0x068 */ float mXButtonPosX;
    /* 0x06C */ float mXButtonPosY;
    /* 0x070 */ float mXButtonScale;
    /* 0x074 */ float mYButtonPosX;
    /* 0x078 */ float mYButtonPosY;
    /* 0x07C */ float mYButtonScale;
    /* 0x080 */ float mNunchukPosX;
    /* 0x084 */ float mNunchukPosY;
    /* 0x088 */ float mNunchukScale;
    /* 0x08C */ float mWiimotePosX;
    /* 0x090 */ float mWiimotePosY;
    /* 0x094 */ float mWiimoteScale;
    /* 0x098 */ float mWiimoteLRPosX;
    /* 0x09C */ float mWiimoteLRPosY;
    /* 0x0A0 */ float mWiimoteLRScale;
    /* 0x0A4 */ float mNunchukZButtonPosX;
    /* 0x0A8 */ float mNunchukZButtonPosY;
    /* 0x0AC */ float mNunchukZButtonScale;
    /* 0x0B0 */ float mNunchukCButtonPosX;
    /* 0x0B4 */ float mNunchukCButtonPosY;
    /* 0x0B8 */ float mNunchukCButtonScale;
    /* 0x0BC */ float mWiimoteAPosX;
    /* 0x0C0 */ float mWiimoteAPosY;
    /* 0x0C4 */ float mWiimoteAScale;
    /* 0x0C8 */ float m3DBButtonPosX;
    /* 0x0CC */ float m3DBButtonPosY;
    /* 0x0D0 */ float m3DBButtonScale;
    /* 0x0D4 */ float mNunchukWiimotePosX;
    /* 0x0D8 */ float mNunchukWiimotePosY;
    /* 0x0DC */ float mNunchukWiimoteScale;
    /* 0x0E0 */ float mNunchukWiimoteRealPosX;
    /* 0x0E4 */ float mNunchukWiimoteRealPosY;
    /* 0x0E8 */ float mNunchukWiimoteRealScale;
    /* 0x0EC */ float mNunchukRealPosX;
    /* 0x0F0 */ float mNunchukRealPosY;
    /* 0x0F4 */ float mNunchukRealScale;
    /* 0x0F8 */ float mNunchukAttackPosX;
    /* 0x0FC */ float mNunchukAttackPosY;
    /* 0x100 */ float mNunchukAttackScale;
    /* 0x104 */ float mABButtonPosX;
    /* 0x108 */ float mABButtonPosY;
    /* 0x10C */ float mABButtonScale;
    /* 0x110 */ float mBottleIconPosX;
    /* 0x114 */ float mBottleIconPosY;
    /* 0x118 */ float mBottleIconScale;
    /* 0x11C */ float mViewChangePosX;
    /* 0x120 */ float mViewChangePosY;
    /* 0x124 */ float mViewChangeScale;
    /* 0x128 */ float mText1PosX;
    /* 0x12C */ float mText2PosX;
    /* 0x130 */ float mText1PosY;
    /* 0x134 */ float mText2PosY;
    /* 0x138 */ float mText1Scale;
    /* 0x13C */ float mText2Scale;
    /* 0x140 */ float mItemPosX;
    /* 0x144 */ float mItemPosY;
    /* 0x148 */ float mItemScale;
    /* 0x14C */ float mMidnaIconPosX;
    /* 0x150 */ float mMidnaIconPosY;
    /* 0x154 */ float mMidnaIconScale;
    /* 0x158 */ float mHawkeyePosX;
    /* 0x15C */ float mHawkeyePosY;
    /* 0x160 */ float mHawkeyeTextPosX;
    /* 0x164 */ float mHawkeyePlusPosX;
    /* 0x168 */ float mHawkeyeMinusPosX;
    /* 0x16C */ float mHawkeyeTextPosY[3];
    /* 0x178 */ float mHawkeyeZoomPosX;
    /* 0x17C */ float mHawkeyeZoomPosY;
    /* 0x180 */ float mHawkeyeZoomScale;
    /* 0x184 */ float mHawkeyeZoomScale_4x3;
    /* 0x188 */ float mHawkeyeTextIconPosX;
    /* 0x18C */ float mHawkeyeZoomTextPosX;
    /* 0x190 */ float mHawkeyeIconPosX;
    /* 0x194 */ float mHawkeyeTextIconPosY_4x3;
    /* 0x198 */ float mHawkeyeTextPosY_4x3;
    /* 0x19C */ float mHawkeyeIconPosY_4x3;
    /* 0x1A0 */ float mHawkeyeTextIconPosY;
    /* 0x1A4 */ float mHawkeyeZoomTextPosY;
    /* 0x1A8 */ float mHawkeyeIconPosY;
    /* 0x1AC */ float mHawkeyeTextIconScale;
    /* 0x1B0 */ float mHawkeyeTextScale;
    /* 0x1B4 */ float mHawkeyeIconScale;
    /* 0x1B8 */ JUtility::TColor mPointerONBlack[2];
    /* 0x1C0 */ JUtility::TColor mPointerONWhite[2];
    /* 0x1C8 */ JUtility::TColor mPointerOFFBlack;
    /* 0x1CC */ JUtility::TColor mPointerOFFWhite;
    /* 0x1D0 */ float mPointerONScale;
    /* 0x1D4 */ float mPointerOFFScale;
    /* 0x1D8 */ int16_t mPointerONAnimFrame;
    /* 0x1DC */ float mHighlightScale;
    /* 0x1E0 */ JUtility::TColor mHighlightFrontInner;
    /* 0x1E4 */ JUtility::TColor mHighlightFrontOuter;
    /* 0x1E8 */ JUtility::TColor mHighlightBackInner;
    /* 0x1EC */ JUtility::TColor mHighlightBackOuter;
    /* 0x1F0 */ float mHighlightAnimSpeed;
    /* 0x1F4 */ float mHighlightFastScale;
    /* 0x1F8 */ JUtility::TColor mHighlightFastFrontInner;
    /* 0x1FC */ JUtility::TColor mHighlightFastFrontOuter;
    /* 0x200 */ JUtility::TColor mHighlightFastBackInner;
    /* 0x204 */ JUtility::TColor mHighlightFastBackOuter;
    /* 0x208 */ float mHighlightFastAnimSpeed;
    /* 0x20C */ float mHighlightListenScale;
    /* 0x210 */ JUtility::TColor mHighlightListenFrontInner;
    /* 0x214 */ JUtility::TColor mHighlightListenFrontOuter;
    /* 0x218 */ JUtility::TColor mHighlightListenBackInner;
    /* 0x21C */ JUtility::TColor mHighlightListenBackOuter;
    /* 0x220 */ float mHighlightListenAnimSpeed;
    /* 0x224 */ float mHighlightRepeatHitScale;
    /* 0x228 */ JUtility::TColor mHighlightRepeatHitFrontInner;
    /* 0x22C */ JUtility::TColor mHighlightRepeatHitFrontOuter;
    /* 0x230 */ JUtility::TColor mHighlightRepeatHitBackInner;
    /* 0x234 */ JUtility::TColor mHighlightRepeatHitBackOuter;
    /* 0x238 */ float mHighlightRepeatHitAnimSpeed;
    /* 0x23C */ float mRepeatHitScale;
    /* 0x240 */ int16_t mRepeatHitFrameNum;
    /* 0x244 */ float mDisplaySpace;
    /* 0x248 */ uint8_t mDebugDisplayButton[17];
    /* 0x259 */ bool mHawkeyeDebugON;
    /* 0x25A */ bool mHawkeyeZoomDebugON;
};  // Size: 0x25C

class dMeter_drawMiniGameHIO_c {
public:
    /* 0x000 */ void* vtable;
    /* 0x004 */ uint8_t field_0x4[4];
    /* 0x008 */ float field_0x8;
    /* 0x00C */ float mRiverRideTargetCounterSizeY;
    /* 0x010 */ float field_0x10;
    /* 0x014 */ float field_0x14;
    /* 0x018 */ float mRiverRideTargetCounterPosX;
    /* 0x01C */ float field_0x1c;
    /* 0x020 */ float field_0x20;
    /* 0x024 */ float mRiverRideTargetCounterPosY;
    /* 0x028 */ float field_0x28;
    /* 0x02C */ float field_0x2c;
    /* 0x030 */ float mRiverRideTargetCounterAlpha;
    /* 0x034 */ float field_0x34;
    /* 0x038 */ float mGoatTimerSizeX;
    /* 0x03C */ float field_0x3c;
    /* 0x040 */ float field_0x40;
    /* 0x044 */ float mGoatTimerSizeY;
    /* 0x048 */ float field_0x48;
    /* 0x04C */ float field_0x4c;
    /* 0x050 */ float mGoatTimerPosX;
    /* 0x054 */ float field_0x54;
    /* 0x058 */ float field_0x58;
    /* 0x05C */ float mGoatTimerPosY;
    /* 0x060 */ float field_0x60;
    /* 0x064 */ float field_0x64;
    /* 0x068 */ float mGoatTimerAlpha;
    /* 0x06C */ float field_0x6c;
    /* 0x070 */ float field_0x70;
    /* 0x074 */ float mGoatCounterSizeX;
    /* 0x078 */ float mRiverRideCounterSizeX;
    /* 0x07C */ float mRiderGameCounterSizeX;
    /* 0x080 */ float mGoatCounterSizeY;
    /* 0x084 */ float mRiverRideCounterSizeY;
    /* 0x088 */ float mRiderGameCounterSizeY;
    /* 0x08C */ float mGoatCounterPosX;
    /* 0x090 */ float mRiverRideCounterPosX;
    /* 0x094 */ float mRiderGameCounterPosX;
    /* 0x098 */ float mGoatCounterPosY;
    /* 0x09C */ float mRiverRideCounterPosY;
    /* 0x0A0 */ float mRiderGameCounterPosY;
    /* 0x0A4 */ float mGoatCounterAlpha;
    /* 0x0A8 */ float mRiverRideCounterAlpha;
    /* 0x0AC */ float mRiderGameCounterAlpha;
    /* 0x0B0 */ float mGoatIconSizeX;
    /* 0x0B4 */ float mRiverRideTargetIconSizeX;
    /* 0x0B8 */ float mRiderGameIconSizeX;
    /* 0x0BC */ float mGoatIconSizeY;
    /* 0x0C0 */ float mRiverRideTargetIconSizeY;
    /* 0x0C4 */ float mRiderGameIconSizeY;
    /* 0x0C8 */ float mGoatIconPosX;
    /* 0x0CC */ float mRiverRideTargetIconPosX;
    /* 0x0D0 */ float mRiderGameIconPosX;
    /* 0x0D4 */ float mGoatIconPosY;
    /* 0x0D8 */ float mRiverRideTargetIconPosY;
    /* 0x0DC */ float mRiderGameIconPosY;
    /* 0x0E0 */ float mGoatIconAlpha;
    /* 0x0E4 */ float mRiverRideTargetIconAlpha;
    /* 0x0E8 */ float mRiderGameIconAlpha;
    /* 0x0EC */ float mGoatTimerSizeX_4x3;
    /* 0x0F0 */ float mGoatTimerSizeY_4x3;
    /* 0x0F4 */ float mGoatTimerPosX_4x3;
    /* 0x0F8 */ float mGoatTimerPosY_4x3;
    /* 0x0FC */ float mGoatIconPosX_4x3;
    /* 0x100 */ float mRiverRideIconPosX_4x3;
    /* 0x104 */ float mRiderGameIconPosX_4x3;
    /* 0x108 */ float mGetInTextSizeX;
    /* 0x10C */ float mGetInTextSizeY;
    /* 0x110 */ float mGetInTextPosX;
    /* 0x114 */ float mGetInTextPosY;
    /* 0x118 */ float mGetInTextAnimSpeed;
    /* 0x11C */ int16_t mGetInTextWaitFrames;
    /* 0x11E */ int16_t mGetInTextAlphaFrames;
    /* 0x120 */ float mGetInHighlightScale;
    /* 0x124 */ JUtility::TColor mGetInHighlightFrontInner;
    /* 0x128 */ JUtility::TColor mGetInHighlightFrontOuter;
    /* 0x12C */ JUtility::TColor mGetInHighlightBackInner;
    /* 0x130 */ JUtility::TColor mGetInHighlightBackOuter;
    /* 0x134 */ float mGetInHighlightAnimSpeed;
    /* 0x138 */ int16_t mGetInHighlightAppearFrames;
    /* 0x13A */ uint8_t mGetInTextLocation;
    /* 0x13C */ float mStartHighlightScale;
    /* 0x140 */ JUtility::TColor mStartHighlightFrontInner;
    /* 0x144 */ JUtility::TColor mStartHighlightFrontOuter;
    /* 0x148 */ JUtility::TColor mStartHighlightBackInner;
    /* 0x14C */ JUtility::TColor mStartHighlightBackOuter;
    /* 0x150 */ float mStartHighlightAnimSpeed;
    /* 0x154 */ int16_t mStartHighlightAppearFrames;
    /* 0x156 */ int16_t mStartHighlightDisplayFrames;
    /* 0x158 */ int16_t mReadyGo;
    /* 0x15A */ int16_t field_0x15a;
    /* 0x15C */ float mReadyFightTextSizeX;
    /* 0x160 */ float mReadyFightTextSizeY;
    /* 0x164 */ float mReadyFightTextPosX;
    /* 0x168 */ float mReadyFightTextPosY;
    /* 0x16C */ float mReadyFightTextAnimSpeed;
    /* 0x170 */ int16_t mReadyFightTextWaitFrames;
    /* 0x172 */ int16_t field_0x172;
    /* 0x174 */ float mReadyFightHighlightScale;
    /* 0x178 */ JUtility::TColor mReadyFightHighlightFrontInner;
    /* 0x17C */ JUtility::TColor mReadyFightHighlightFrontOuter;
    /* 0x180 */ JUtility::TColor mReadyFightHighlightBackInner;
    /* 0x184 */ JUtility::TColor mReadyFightHighlightBackOuter;
    /* 0x188 */ float mReadyFightHighlightAnimSpeed;
    /* 0x18C */ int16_t mReadyFightHighlightAppearFrames;
};  // Size: 0x190

class dMeter_drawLightDropHIO_c {
public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ uint8_t field_0x4[4];
    /* 0x08 */ float mVesselScale;
    /* 0x0C */ float mVesselTalkScale;
    /* 0x10 */ float mVesselPosX;
    /* 0x14 */ float mVesselTalkPosX;
    /* 0x18 */ float mVesselPosY;
    /* 0x1C */ float mVesselTalkPosY;
    /* 0x20 */ float mVesselPosX_4x3;
    /* 0x24 */ float mVesselPosY_4x3;
    /* 0x28 */ float mVesselAlpha;
    /* 0x2C */ float mVesselTalkAlpha;
    /* 0x30 */ float mVesselDecorAlpha;
    /* 0x34 */ float mDropAlpha;
    /* 0x38 */ JUtility::TColor mDropOnColorWhite;
    /* 0x3C */ JUtility::TColor mDropOnColorBlack;
    /* 0x40 */ JUtility::TColor mDropOffColorWhite;
    /* 0x44 */ JUtility::TColor mDropOffColorBlack;
    /* 0x48 */ float mDropScale;
    /* 0x4C */ float mDropGetScale;
    /* 0x50 */ int16_t mDropGetScaleAnimFrameNum;
    /* 0x52 */ int16_t mHighlightInterval;
    /* 0x54 */ int16_t field_0x54;
    /* 0x56 */ int16_t field_0x56;
    /* 0x58 */ JUtility::TColor mDropHighlightFrontInner;
    /* 0x5C */ JUtility::TColor mDropHighlightFrontOuter;
    /* 0x60 */ JUtility::TColor mDropHighlightBackInner;
    /* 0x64 */ JUtility::TColor mDropHighlightBackOuter;
    /* 0x68 */ float mDropHighlightAnimSpeed;
    /* 0x6C */ float mDropHighlightAnimSpeed_Completed;
    /* 0x70 */ JUtility::TColor mHighlightLoopFrontInner[2];
    /* 0x78 */ JUtility::TColor mHighlightLoopFrontOuter[2];
    /* 0x80 */ JUtility::TColor mHighlightLoopBackInner[2];
    /* 0x88 */ JUtility::TColor mHighlightLoopBackOuter[2];
    /* 0x90 */ float mHighlightLoopAnimSpeed;
    /* 0x94 */ float mHighlightLoopBackStopFrame;
    /* 0x98 */ float mHighlightScaleNormal;
    /* 0x9C */ float mHighlightScaleComplete;
    /* 0xA0 */ float mHighlightLoopScale;
    /* 0xA4 */ float mHighlightLoopBackScale;
    /* 0xA8 */ uint8_t mAnimDebug;
};  // Size: 0xAC

class dMeter_drawHIO_c {
public:
    /* 0x000 */ void* vtable;
    /* 0x004 */ uint8_t field_0x04[4];
    /* 0x008 */ float mLifeTopPosX;
    /* 0x00C */ float mLifeTopPosY;
    /* 0x010 */ float mNoMagicPosY;
    /* 0x014 */ float mHUDScale;
    /* 0x018 */ float mHUDAlpha;
    /* 0x01C */ float mLifeGaugeScale;
    /* 0x020 */ float mLifeGaugeHeartAlpha;
    /* 0x024 */ float mLifeGaugeBaseAlpha;
    /* 0x028 */ float mLifeGaugePosX;
    /* 0x02C */ float mLifeGaugePosY;
    /* 0x030 */ float mHeartScale;
    /* 0x034 */ float mHeartAlpha;
    /* 0x038 */ float mLargeHeartScale;
    /* 0x03C */ float mLargeHeartAlpha;
    /* 0x040 */ float mMagicMeterScale;
    /* 0x044 */ float mMagicMeterAlpha;
    /* 0x048 */ float mMagicMeterFrameAlpha;
    /* 0x04C */ float mMagicMeterPosX;
    /* 0x050 */ float mMagicMeterPosY;
    /* 0x054 */ float mLanternMeterScale;
    /* 0x058 */ float mLanternMeterAlpha;
    /* 0x05C */ float mLanternMeterFrameAlpha;
    /* 0x060 */ float mLanternMeterPosX;
    /* 0x064 */ float mLanternMeterPosY;
    /* 0x068 */ float mOxygenMeterScale;
    /* 0x06C */ float mOxygenMeterAlpha;
    /* 0x070 */ float mOxygenMeterFrameAlpha;
    /* 0x074 */ float mOxygenMeterPosX;
    /* 0x078 */ float mOxygenMeterPosY;
    /* 0x07C */ float mMainHUDButtonsScale;
    /* 0x080 */ float mRingHUDButtonsScale;
    /* 0x084 */ float mMainHUDButtonsAlpha;
    /* 0x088 */ float mRingHUDButtonsAlpha;
    /* 0x08C */ float mMainHUDButtonsPosX;
    /* 0x090 */ float mRingHUDButtonsPosX;
    /* 0x094 */ float mMainHUDButtonsPosY;
    /* 0x098 */ float mRingHUDButtonsPosY;
    /* 0x09C */ float mButtonDisplayBackScale;
    /* 0x0A0 */ float mButtonDisplayBackAlpha;
    /* 0x0A4 */ float mAButtonScale;
    /* 0x0A8 */ float mAButtonAlpha;
    /* 0x0AC */ float mAButtonPosX;
    /* 0x0B0 */ float mAButtonPosY;
    /* 0x0B4 */ float mAButtonTalkScale;
    /* 0x0B8 */ float mAButtonFontTalkScale;
    /* 0x0BC */ float mAButtonTalkPosX;
    /* 0x0C0 */ float mAButtonFontTalkPosX;
    /* 0x0C4 */ float mAButtonTalkPosY;
    /* 0x0C8 */ float mAButtonFontTalkPosY;
    /* 0x0CC */ float mAButtonTalkAScale;
    /* 0x0D0 */ float mAButtonFontTalkAScale;
    /* 0x0D4 */ float mAButtonTalkAPosX;
    /* 0x0D8 */ float mAButtonFontTalkAPosX;
    /* 0x0DC */ float mAButtonTalkAPosY;
    /* 0x0E0 */ float mAButtonFontTalkAPosY;
    /* 0x0E4 */ float mAButtonVesselPosX;
    /* 0x0E8 */ float mAButtonVesselPosY;
    /* 0x0EC */ float mBButtonScale;
    /* 0x0F0 */ float mBButtonAlpha;
    /* 0x0F4 */ float mBButtonPosX;
    /* 0x0F8 */ float mBButtonPosY;
    /* 0x0FC */ float mBButtonTalkScale;
    /* 0x100 */ float mBButtonFontTalkScale;
    /* 0x104 */ float mBButtonTalkPosX;
    /* 0x108 */ float mBButtonFontTalkPosX;
    /* 0x10C */ float mBButtonTalkPosY;
    /* 0x110 */ float mBButtonFontTalkPosY;
    /* 0x114 */ float mBButtonWolfPosX;
    /* 0x118 */ float mBButtonWolfPosY;
    /* 0x11C */ float mBButtonVesselPosX;
    /* 0x120 */ float mBButtonVesselPosY;
    /* 0x124 */ float mMidnaIconScale;
    /* 0x128 */ float mMidnaIconAlpha;
    /* 0x12C */ float mMidnaIconPosX;
    /* 0x130 */ float mMidnaIconPosY;
    /* 0x134 */ float field_0x134;
    /* 0x138 */ float field_0x138;
    /* 0x13C */ float field_0x13c;
    /* 0x140 */ float field_0x140;
    /* 0x144 */ float mXButtonScale;
    /* 0x148 */ float mXButtonAlpha;
    /* 0x14C */ float mXButtonPosX;
    /* 0x150 */ float mXButtonPosY;
    /* 0x154 */ float mYButtonScale;
    /* 0x158 */ float mYButtonAlpha;
    /* 0x15C */ float mYButtonPosX;
    /* 0x160 */ float mYButtonPosY;
    /* 0x164 */ float field_0x164;
    /* 0x168 */ float field_0x168;
    /* 0x16C */ float field_0x16c;
    /* 0x170 */ float field_0x170;
    /* 0x174 */ float mZButtonScale;
    /* 0x178 */ float mZButtonAlpha;
    /* 0x17C */ float mZButtonPosX;
    /* 0x180 */ float mZButtonPosY;
    /* 0x184 */ float mBButtonItemPosX;
    /* 0x188 */ float mBButtonSwordPosX;
    /* 0x18C */ float mBButtonFishingPosX;
    /* 0x190 */ float mBButtonItemPosY;
    /* 0x194 */ float mBButtonSwordPosY;
    /* 0x198 */ float mBButtonFishingPosY;
    /* 0x19C */ float mBButtonItemRotation;
    /* 0x1A0 */ float mBButtonSwordRotation;
    /* 0x1A4 */ float mBButtonFishingRotation;
    /* 0x1A8 */ float mBButtonItemScale;
    /* 0x1AC */ float mBButtonSwordScale;
    /* 0x1B0 */ float mBButtonFishingScale;
    /* 0x1B4 */ float mXButtonItemPosX;
    /* 0x1B8 */ float mXButtonItemPosY;
    /* 0x1BC */ float mXButtonItemScale;
    /* 0x1C0 */ float mYButtonItemPosX;
    /* 0x1C4 */ float mYButtonItemPosY;
    /* 0x1C8 */ float mYButtonItemScale;
    /* 0x1CC */ float field_0x1cc;
    /* 0x1D0 */ float field_0x1d0;
    /* 0x1D4 */ float field_0x1d4;
    /* 0x1D8 */ float mZButtonItemPosX;
    /* 0x1DC */ float mZButtonItemPosY;
    /* 0x1E0 */ float mZButtonItemScale;
    /* 0x1E4 */ float mButtonItemRotation[3];
    /* 0x1F0 */ float mXItemNumPosX;
    /* 0x1F4 */ float mYItemNumPosX;
    /* 0x1F8 */ float field_0x1f8;
    /* 0x1FC */ float mBItemNumPosX;
    /* 0x200 */ float mXItemNumPosY;
    /* 0x204 */ float mYItemNumPosY;
    /* 0x208 */ float field_0x208;
    /* 0x20C */ float mBItemNumPosY;
    /* 0x210 */ float mXItemNumScale;
    /* 0x214 */ float mYItemNumScale;
    /* 0x218 */ float field_0x218;
    /* 0x21C */ float mBItemNumScale;
    /* 0x220 */ float mBItemBaseScale[2];
    /* 0x228 */ float mBItemBasePosX[2];
    /* 0x230 */ float mBItemBasePosY[2];
    /* 0x238 */ float mBItemBaseAlpha;
    /* 0x23C */ float field_0x23c;
    /* 0x240 */ float mXButtonItemBaseScale;
    /* 0x244 */ float mXButtonItemBaseNoItemScale;
    /* 0x248 */ float mXButtonItemBasePosX;
    /* 0x24C */ float mXButtonItemBaseNoItemPosX;
    /* 0x250 */ float mXButtonItemBasePosY;
    /* 0x254 */ float mXButtonItemBaseNoItemPosY;
    /* 0x258 */ float mXButtonItemBaseAlpha;
    /* 0x25C */ float mXButtonItemBaseNoItemAlpha;
    /* 0x260 */ float mYButtonItemBaseScale;
    /* 0x264 */ float mYButtonItemBaseNoItemScale;
    /* 0x268 */ float mYButtonItemBasePosX;
    /* 0x26C */ float mYButtonItemBaseNoItemPosX;
    /* 0x270 */ float mYButtonItemBasePosY;
    /* 0x274 */ float mYButtonItemBaseNoItemPosY;
    /* 0x278 */ float mYButtonItemBaseAlpha;
    /* 0x27C */ float mYButtonItemBaseNoItemAlpha;
    /* 0x280 */ float field_0x280;
    /* 0x284 */ float field_0x284;
    /* 0x288 */ float field_0x288;
    /* 0x28C */ float field_0x28c;
    /* 0x290 */ float field_0x290;
    /* 0x294 */ float field_0x294;
    /* 0x298 */ float field_0x298;
    /* 0x29C */ float field_0x29c;
    /* 0x2A0 */ float mZButtonItemBaseScale;
    /* 0x2A4 */ float mZButtonItemBasePosX;
    /* 0x2A8 */ float mZButtonItemBasePosY;
    /* 0x2AC */ float mZButtonItemBaseAlpha;
    /* 0x2B0 */ float mButtonBaseAlpha;
    /* 0x2B4 */ float mAButtonFontScale;
    /* 0x2B8 */ float mAButtonFontPosX;
    /* 0x2BC */ float mAButtonFontPosY;
    /* 0x2C0 */ JUtility::TColor mAButtonFontColor;
    /* 0x2C4 */ float mAButtonFontSpacing;
    /* 0x2C8 */ int32_t mAButtonFontActionID;
    /* 0x2CC */ uint32_t field_0x2cc;
    /* 0x2D0 */ bool mAButtonTextDebug;
    /* 0x2D4 */ float mBButtonFontScale;
    /* 0x2D8 */ float mBButtonFontPosX;
    /* 0x2DC */ float mBButtonFontPosY;
    /* 0x2E0 */ JUtility::TColor mBButtonFontColor;
    /* 0x2E4 */ float field_0x2e4;
    /* 0x2E8 */ float field_0x2e8;
    /* 0x2EC */ float field_0x2ec;
    /* 0x2F0 */ JUtility::TColor field_0x2f0;
    /* 0x2F4 */ float mXYButtonFontScale;
    /* 0x2F8 */ float mXYButtonFontPosX;
    /* 0x2FC */ float mXYButtonFontPosY;
    /* 0x300 */ JUtility::TColor mXYButtonFontColor;
    /* 0x304 */ float field_0x304;
    /* 0x308 */ float field_0x308;
    /* 0x30C */ float field_0x30c;
    /* 0x310 */ JUtility::TColor field_0x310;
    /* 0x314 */ float field_0x314;
    /* 0x318 */ float field_0x318;
    /* 0x31C */ float field_0x31c;
    /* 0x320 */ float field_0x320;
    /* 0x324 */ float field_0x324;
    /* 0x328 */ float field_0x328;
    /* 0x32C */ float mZButtonFontScale;
    /* 0x330 */ float mZButtonFontPosX;
    /* 0x334 */ float mZButtonFontPosY;
    /* 0x338 */ JUtility::TColor mZButtonFontColor;
    /* 0x33C */ float mRupeeKeyScale;
    /* 0x340 */ float mRupeeKeyPosX;
    /* 0x344 */ float mRupeeKeyPosY;
    /* 0x348 */ float mRupeeKeyAlpha;
    /* 0x34C */ float mRupeeScale;
    /* 0x350 */ float mRupeePosX;
    /* 0x354 */ float mRupeePosY;
    /* 0x358 */ float mRupeeAlpha;
    /* 0x35C */ float mKeyScale;
    /* 0x360 */ float mKeyPosX;
    /* 0x364 */ float mKeyPosY;
    /* 0x368 */ float mKeyAlpha;
    /* 0x36C */ float mRupeeFrameScale;
    /* 0x370 */ float mRupeeFramePosX;
    /* 0x374 */ float mRupeeFramePosY;
    /* 0x378 */ float mRupeeFrameAlpha;
    /* 0x37C */ float mRupeeCountScale;
    /* 0x380 */ float mRupeeCountPosX;
    /* 0x384 */ float mRupeeCountPosY;
    /* 0x388 */ float mRupeeCountAlpha;
    /* 0x38C */ float mKeyNumScale;
    /* 0x390 */ float mKeyNumPosX;
    /* 0x394 */ float mKeyNumPosY;
    /* 0x398 */ float mKeyNumAlpha;
    /* 0x39C */ float mSpurIconScale;
    /* 0x3A0 */ float mSpurIconAlpha;
    /* 0x3A4 */ float mUsedSpurIconScale;
    /* 0x3A8 */ float mUsedSpurIconAlpha;
    /* 0x3AC */ float mSpurBarScale;
    /* 0x3B0 */ float mSpurBarPosX;
    /* 0x3B4 */ float mSpurBarPosY;
    /* 0x3B8 */ float mAButtonHorsePosX;
    /* 0x3BC */ float mAButtonHorsePosY;
    /* 0x3C0 */ float mAButtonHorseScale;
    /* 0x3C4 */ float mAButtonHighlightScale;
    /* 0x3C8 */ float mBButtonHighlightScale;
    /* 0x3CC */ float field_0x3cc;
    /* 0x3D0 */ float field_0x3d0;
    /* 0x3D4 */ float field_0x3d4;
    /* 0x3D8 */ float mZButtonHighlightScale;
    /* 0x3DC */ float mXYButtonHighlightScale;
    /* 0x3E0 */ float mSpurIconHighlightScale;
    /* 0x3E4 */ float mSpurIconReviveHighlightScale;
    /* 0x3E8 */ float mMidnaIconHighlightScale;
    /* 0x3EC */ int16_t mMidnaIconFlashRate;
    /* 0x3F0 */ float field_0x3f0;
    /* 0x3F4 */ float field_0x3f4;
    /* 0x3F8 */ float field_0x3f8;
    /* 0x3FC */ float mDPadButtonScale;
    /* 0x400 */ float mDPadButtonOFFPosX;
    /* 0x404 */ float mDPadButtonOFFPosY;
    /* 0x408 */ float mDPadButtonONPosX;
    /* 0x40C */ float mDPadButtonONPosY;
    /* 0x410 */ float mDPadButtonLetterSpacing;
    /* 0x414 */ float mDPadButtonAlpha;
    /* 0x418 */ float mDPadButtonITEMAlpha;
    /* 0x41C */ float mDPadButtonMAPAlpha;
    /* 0x420 */ int16_t mDPadButtonMoveFrame;
    /* 0x422 */ int16_t field_0x422;
    /* 0x424 */ int16_t field_0x424;
    /* 0x426 */ bool mButtonDebug[4];
    /* 0x42A */ uint8_t mXYButtonsItemDimAlpha;
    /* 0x42B */ uint8_t mXYButtonsBaseDimAlpha;
    /* 0x42C */ uint8_t field_0x42c;
    /* 0x42D */ uint8_t mMaxSpurAmount;
    /* 0x42E */ bool mSpurDebug;
    /* 0x42F */ bool field_0x42f;
    /* 0x430 */ JUtility::TColor mSpurIconHighlightFrontInner;
    /* 0x434 */ JUtility::TColor mSpurIconHighlightFrontOuter;
    /* 0x438 */ JUtility::TColor mSpurIconHighlightBackInner;
    /* 0x43C */ JUtility::TColor mSpurIconHighlightBackOuter;
    /* 0x440 */ float mSpurIconHighlightAnimSpeed;
    /* 0x444 */ JUtility::TColor mSpurIconReviveHighlightFrontInner;
    /* 0x448 */ JUtility::TColor mSpurIconReviveHighlightFrontOuter;
    /* 0x44C */ JUtility::TColor mSpurIconReviveHighlightBackInner;
    /* 0x450 */ JUtility::TColor mSpurIconReviveHighlightBackOuter;
    /* 0x454 */ float mSpurIconReviveHighlightAnimSpeed;
    /* 0x458 */ JUtility::TColor mZButtonHighlightFrontInner;
    /* 0x45C */ JUtility::TColor mZButtonHighlightFrontOuter;
    /* 0x460 */ JUtility::TColor mZButtonHighlightBackInner;
    /* 0x464 */ JUtility::TColor mZButtonHighlightBackOuter;
    /* 0x468 */ float mZButtonHighlightAnimSpeed;
    /* 0x46C */ JUtility::TColor mXYButtonHighlightFrontInner;
    /* 0x470 */ JUtility::TColor mXYButtonHighlightFrontOuter;
    /* 0x474 */ JUtility::TColor mXYButtonHighlightBackInner;
    /* 0x478 */ JUtility::TColor mXYButtonHighlightBackOuter;
    /* 0x47C */ float mXYButtonHighlightAnimSpeed;
    /* 0x480 */ JUtility::TColor mAButtonHighlightFrontInner;
    /* 0x484 */ JUtility::TColor mAButtonHighlightFrontOuter;
    /* 0x488 */ JUtility::TColor mAButtonHighlightBackInner;
    /* 0x48C */ JUtility::TColor mAButtonHighlightBackOuter;
    /* 0x490 */ float mAButtonHighlightAnimSpeed;
    /* 0x494 */ JUtility::TColor mBButtonHighlightFrontInner;
    /* 0x498 */ JUtility::TColor mBButtonHighlightFrontOuter;
    /* 0x49C */ JUtility::TColor mBButtonHighlightBackInner;
    /* 0x4A0 */ JUtility::TColor mBButtonHighlightBackOuter;
    /* 0x4A4 */ float mBButtonHighlightAnimSpeed;
    /* 0x4A8 */ JUtility::TColor field_0x4a8;
    /* 0x4AC */ JUtility::TColor field_0x4ac;
    /* 0x4B0 */ JUtility::TColor field_0x4b0;
    /* 0x4B4 */ JUtility::TColor field_0x4b4;
    /* 0x4B8 */ float field_0x4b8;
    /* 0x4BC */ JUtility::TColor field_0x4bc;
    /* 0x4C0 */ JUtility::TColor field_0x4c0;
    /* 0x4C4 */ JUtility::TColor field_0x4c4;
    /* 0x4C8 */ JUtility::TColor field_0x4c8;
    /* 0x4CC */ float field_0x4cc;
    /* 0x4D0 */ JUtility::TColor field_0x4d0;
    /* 0x4D4 */ JUtility::TColor field_0x4d4;
    /* 0x4D8 */ JUtility::TColor field_0x4d8;
    /* 0x4DC */ JUtility::TColor field_0x4dc;
    /* 0x4E0 */ float field_0x4e0;
    /* 0x4E4 */ JUtility::TColor mMidnaIconHighlightFrontInner;
    /* 0x4E8 */ JUtility::TColor mMidnaIconHighlightFrontOuter;
    /* 0x4EC */ JUtility::TColor mMidnaIconHighlightBackInner;
    /* 0x4F0 */ JUtility::TColor mMidnaIconHighlightBackOuter;
    /* 0x4F4 */ float mMidnaIconHighlightAnimSpeed;
    /* 0x4F8 */ float mScrollArrowScaleX;
    /* 0x4FC */ float mScrollArrowScaleY;
    /* 0x500 */ float mScrollArrowBPKAnimSpeed;
    /* 0x504 */ float mScrollArrowBCKAnimSpeed;
    /* 0x508 */ float mScrollArrowBTKAnimSpeed;
    /* 0x50C */ float mScrollArrowTopBottomPosX;
    /* 0x510 */ float mScrollArrowLeftRightPosX;
    /* 0x514 */ float mScrollArrowTopBottomPosY;
    /* 0x518 */ float mScrollArrowLeftRightPosY;
    /* 0x51C */ float mScrollArrowCenterPosX;
    /* 0x520 */ float mScrollArrowCenterPosY;
    /* 0x524 */ bool mScrollArrowDisplayAll;
    /* 0x528 */ float mWiiLockArrowScaleX;
    /* 0x52C */ float mWiiLockArrowScaleY;
    /* 0x530 */ float mWiiLockArrowBPKAnimSpeed;
    /* 0x534 */ float mWiiLockArrowBCKAnimSpeed;
    /* 0x538 */ float mWiiLockArrowBTKAnimSpeed;
    /* 0x53C */ float mWiiLockArrowTopBottomPosX;
    /* 0x540 */ float mWiiLockArrowLeftRightPosX;
    /* 0x544 */ float mWiiLockArrowTopBottomPosY;
    /* 0x548 */ float mWiiLockArrowLeftRightPosY;
    /* 0x54C */ float field_0x54c;
    /* 0x550 */ bool mWiiLockArrowDisplayAll;
    /* 0x554 */ float mFloatingMessagePosX;
    /* 0x558 */ float mFloatingMessagePosY;
    /* 0x55C */ uint32_t mMessageID;
    /* 0x560 */ uint32_t mFlowID;
    /* 0x564 */ int16_t mMessageDuration;
    /* 0x566 */ bool mMessageDebug;
    /* 0x567 */ bool mFlowDebug;
    /* 0x568 */ bool mItemScaleAdjustON;
    /* 0x569 */ uint8_t mItemScalePercent;
    /* 0x56C */ float mTouchAreaUnselectScale[5];
    /* 0x580 */ float mTouchAreaSelectScale[5];
    /* 0x594 */ float mTouchAreaScale[5];
    /* 0x5A8 */ float mTouchAreaAlpha[5];
    /* 0x5BC */ float mTouchAreaPosX[5];
    /* 0x5D0 */ float mTouchAreaPosY[5];
    /* 0x5E4 */ float mDpadMAPScale;
    /* 0x5E8 */ float mDpadMAPPosX;
    /* 0x5EC */ float mDpadMAPPosY;
    /* 0x5F0 */ JUtility::TColor mTouchAreaSelectWhite[3];
    /* 0x5FC */ JUtility::TColor mTouchAreaSelectBlack[3];
    /* 0x608 */ int16_t mTouchAreaSelectFrameNum;
    /* 0x60A */ bool field_0x60a;
    /* 0x60C */ float mLanternIconMeterPosX;
    /* 0x610 */ float mLanternIconMeterPosY;
    /* 0x614 */ float mLanternIconMeterSize;
    /* 0x618 */ dMeter_drawCollectHIO_c mCollectScreen;
    /* 0x6B8 */ dMeter_drawOptionHIO_c mOptionScreen;
    /* 0x728 */ dMeter_drawLetterHIO_c mLetterSelectScreen;
    /* 0x788 */ dMeter_drawFishingHIO_c mFishListScreen;
    /* 0x9DC */ dMeter_drawInsectHIO_c mInsectListScreen;
    /* 0xA1C */ dMeter_drawCalibrationHIO_c mCalibration;
    /* 0xA34 */ dMeter_drawSkillHIO_c mSkillListScreen;
    /* 0xA90 */ dMeter_drawMiniGameHIO_c mMiniGame;
    /* 0xC20 */ dMeter_drawEmpButtonHIO_c mEmpButton;
    /* 0xE7C */ dMeter_drawLightDropHIO_c mLightDrop;
};  // Size = 0xF28

static_assert(sizeof(dMeter_drawHIO_c) == 3880);

class dMeter_ringHIO_c {
public:
    enum {
        /* 0x0 */ SET_ITEM,
        /* 0x1 */ DIRECT_SELECT,
        /* 0x3 */ ROTATE = 3,
        /* 0x4 */ COMBO_ITEM
    };

    enum {
        /* 0x0 */ SELECT_FRAME,
        /* 0x1 */ UNSELECT_FRAME
    };

    /* 0x000 */ void* vtable;
    /* 0x004 */ uint8_t field_0x4[4];
    /* 0x008 */ float mRingRadiusH;
    /* 0x00C */ float mRingRadiusV;
    /* 0x010 */ float field_0x10;
    /* 0x014 */ float mSelectItemScale;
    /* 0x018 */ float mSelectButtonScale;
    /* 0x01C */ float mUnselectItemScale;
    /* 0x020 */ float mUnselectButtonScale;
    /* 0x024 */ float mInactiveItemScale;
    /* 0x028 */ float mCursorScale;
    /* 0x02C */ float mItemNamePosX;
    /* 0x030 */ float mItemNamePosY;
    /* 0x034 */ float mItemNameScale;
    /* 0x038 */ float mCenterPosX;
    /* 0x03C */ float mCenterPosY;
    /* 0x040 */ float mCenterScale;
    /* 0x044 */ float field_0x44;
    /* 0x048 */ float field_0x48;
    /* 0x04C */ float field_0x4c;
    /* 0x050 */ float mOverlayAlpha;
    /* 0x054 */ float mGuidePosX[10];
    /* 0x07C */ float mGuidePosY[10];
    /* 0x0A4 */ float mGuideScale[10];
    /* 0x0CC */ float mHighlightScale;
    /* 0x0D0 */ JUtility::TColor mHighlightFrontInner;
    /* 0x0D4 */ JUtility::TColor mHighlightFrontOuter;
    /* 0x0D8 */ JUtility::TColor mHighlightBackInner;
    /* 0x0DC */ JUtility::TColor mHighlightBackOuter;
    /* 0x0E0 */ float mHighlightAnimSpeed;
    /* 0x0E4 */ float mSelectPosX;
    /* 0x0E8 */ float mSelectPosY;
    /* 0x0EC */ float mSelectScaleX;
    /* 0x0F0 */ float mSelectScaleY;
    /* 0x0F4 */ float mItemDescPosX;
    /* 0x0F8 */ float mItemDescPosY;
    /* 0x0FC */ float mItemDescScale;
    /* 0x100 */ float mItemDescAlpha;
    /* 0x104 */ float mItemDescTitlePosX;
    /* 0x108 */ float mItemDescTitlePosY;
    /* 0x10C */ float mItemDescTitleScale;
    /* 0x110 */ float mItemRingPosX;
    /* 0x114 */ float mItemRingPosY;
    /* 0x118 */ float mRingPosX;
    /* 0x11C */ float mRingPosY;
    /* 0x120 */ float mRingAlpha;
    /* 0x124 */ float mRingAlpha_Wolf;
    /* 0x128 */ float mRingScaleH;
    /* 0x12C */ float mRingScaleV;
    /* 0x130 */ JUtility::TColor mItemFrame[2];
    /* 0x138 */ int16_t mItemAlphaFlashDuration;
    /* 0x13A */ int16_t mOpenFrames;
    /* 0x13C */ int16_t mCloseFrames;
    /* 0x13E */ int16_t field_0x13e;
    /* 0x140 */ int16_t field_0x140;
    /* 0x142 */ int16_t field_0x142;
    /* 0x144 */ int16_t mCursorMax;
    /* 0x146 */ int16_t mCursorInitSpeed;
    /* 0x148 */ int16_t mCursorAccel;
    /* 0x14A */ int16_t mCursorChangeWaitFrames;
    /* 0x14C */ int16_t mDirectSelectWaitFrames;
    /* 0x14E */ uint8_t mOffsetLineDisplay;
    /* 0x14F */ uint8_t mItemNum;
    /* 0x150 */ uint8_t field_0x150;
    /* 0x151 */ uint8_t mItemIconAlpha;
    /* 0x152 */ uint8_t mItemIconAlpha_Wolf;
    /* 0x153 */ uint8_t field_0x153;
    /* 0x154 */ uint8_t field_0x154;
    /* 0x155 */ uint8_t mItemAlphaMin;
    /* 0x156 */ uint8_t mItemAlphaMax;
};  // Size: 0x158

static_assert(sizeof(dMeter_ringHIO_c) == 344);

class dMeter_mapIconHIO_c {
public:
    enum {
        /* 0x00 */ ICON_PORTAL,
        /* 0x01 */ ICON_LINK,
        /* 0x02 */ ICON_DUNGEON_WARP,
        /* 0x03 */ ICON_DESTINATION,
        /* 0x04 */ ICON_BOSS,
        /* 0x05 */ ICON_GANON,
        /* 0x06 */ ICON_LIGHT_DROP,
        /* 0x07 */ ICON_SOL,
        /* 0x08 */ ICON_CANNON_BALL,
        /* 0x09 */ ICON_YETO,
        /* 0x0A */ ICON_YETA,
        /* 0x0B */ ICON_GOLD_WOLF,
        /* 0x0C */ ICON_MONKEY,
        /* 0x0D */ ICON_OOCCOO_SR,
        /* 0x0E */ ICON_OOCCOO_JR,
        /* 0x0F */ ICON_COPY_STATUE,
        /* 0x10 */ ICON_WAGON,
        /* 0x11 */ ICON_SMALL_KEY,
        /* 0x12 */ ICON_CHEST,
        /* 0x13 */ ICON_STAGE_ENTRANCE,
        /* 0x14 */ ICON_ROOM_ENTRANCE,
        /* 0x15 */ ICON_LV8_ENTRANCE,
    };

    /* 0x000 */ void* vtable;
    /* 0x004 */ uint8_t field_0x4[4];
    /* 0x008 */ float mPortalCursorScale;
    /* 0x00C */ float mPortalIconScale;
    /* 0x010 */ float mDestinationScale;
    /* 0x014 */ float mDungeonDestScale;
    /* 0x018 */ float mDestinationZoomScale;
    /* 0x01C */ float mDungeonDestZoomScale;
    /* 0x020 */ float field_0x20;
    /* 0x024 */ float mBossScale;
    /* 0x028 */ float field_0x28;
    /* 0x02C */ float mBossZoomScale;
    /* 0x030 */ float field_0x30;
    /* 0x034 */ float mGanonScale;
    /* 0x038 */ float field_0x38;
    /* 0x03C */ float mGanonZoomScale;
    /* 0x040 */ float mDungeonEntranceScale;
    /* 0x044 */ float mDungeonExitScale;
    /* 0x048 */ float mDungeonEntranceZoomScale;
    /* 0x04C */ float mDungeonExitZoomScale;
    /* 0x050 */ float field_0x50;
    /* 0x054 */ float mSmallKeyScale;
    /* 0x058 */ float field_0x58;
    /* 0x05C */ float mSmallKeyZoomScale;
    /* 0x060 */ float field_0x60;
    /* 0x064 */ float mChestScale;
    /* 0x068 */ float field_0x68;
    /* 0x06C */ float mChestZoomScale;
    /* 0x070 */ float mYetoScale;
    /* 0x074 */ float field_0x74;
    /* 0x078 */ float mYetoZoomScale;
    /* 0x07C */ float field_0x7c;
    /* 0x080 */ float mYetaScale;
    /* 0x084 */ float field_0x84;
    /* 0x088 */ float mYetaZoomScale;
    /* 0x08C */ float field_0x8c;
    /* 0x090 */ float mGoldWolfScale;
    /* 0x094 */ float field_0x94;
    /* 0x098 */ float mGoldWolfZoomScale;
    /* 0x09C */ float field_0x9c;
    /* 0x0A0 */ float field_0xa0;
    /* 0x0A4 */ float mMonkeyScale;
    /* 0x0A8 */ float field_0xa8;
    /* 0x0AC */ float mMonkeyZoomScale;
    /* 0x0B0 */ float field_0xb0;
    /* 0x0B4 */ float mOoccooScale;
    /* 0x0B8 */ float field_0xb8;
    /* 0x0BC */ float mOoccooZoomScale;
    /* 0x0C0 */ float field_0xc0;
    /* 0x0C4 */ float mOoccooPotScale;
    /* 0x0C8 */ float field_0xc8;
    /* 0x0CC */ float mOoccooPotZoomScale;
    /* 0x0D0 */ float field_0xd0;
    /* 0x0D4 */ float mCopyRodStatueScale;
    /* 0x0D8 */ float field_0xd8;
    /* 0x0DC */ float mCopyRodStatueZoomScale;
    /* 0x0E0 */ float mWagonScale;
    /* 0x0E4 */ float field_0xe4;
    /* 0x0E8 */ float mWagonZoomScale;
    /* 0x0EC */ float field_0xec;
    /* 0x0F0 */ float mLinkScale;
    /* 0x0F4 */ float mDungeonLinkScale;
    /* 0x0F8 */ float mLinkZoomScale;
    /* 0x0FC */ float mDungeonLinkZoomScale;
    /* 0x100 */ float mRoomEntranceScale;
    /* 0x104 */ float mDungeonSpawnScale;
    /* 0x108 */ float mRoomEntranceZoomScale;
    /* 0x10C */ float mDungeonSpawnZoomScale;
    /* 0x110 */ float mLV8EntranceScale;
    /* 0x114 */ float field_0x114;
    /* 0x118 */ float mLV8EntranceZoomScale;
    /* 0x11C */ float field_0x11c;
    /* 0x120 */ float field_0x120;
    /* 0x124 */ float mDungeonWarpScale;
    /* 0x128 */ float field_0x128;
    /* 0x12C */ float mDungeonWarpZoomScale;
    /* 0x130 */ float mLightDropScale;
    /* 0x134 */ float field_0x134;
    /* 0x138 */ float mLightDropZoomScale;
    /* 0x13C */ float field_0x13c;
    /* 0x140 */ float field_0x140;
    /* 0x144 */ float mLightOrbScale;
    /* 0x148 */ float field_0x148;
    /* 0x14C */ float mLightOrbZoomScale;
    /* 0x150 */ float field_0x150;
    /* 0x154 */ float mCannonBallScale;
    /* 0x158 */ float field_0x158;
    /* 0x15C */ float mCannonBallZoomScale;
    /* 0x160 */ float mLightDropFlashStartScaleOut;
    /* 0x164 */ float mLightDropFlashStartScaleIn;
    /* 0x168 */ float mLightDropFlashEndScaleOut;
    /* 0x16C */ float mLightDropFlashEndScaleIn;
    /* 0x170 */ int16_t mLightDropFlashFrameNum;
    /* 0x172 */ uint8_t mLightDropFlashStartAlphaOut;
    /* 0x173 */ uint8_t mLightDropFlashStartAlphaIn;
    /* 0x174 */ uint8_t mLightDropFlashEndAlphaOut;
    /* 0x175 */ uint8_t mLightDropFlashEndAlphaIn;
    /* 0x176 */ bool mLV5DungeonItemDebug;
    /* 0x177 */ uint8_t mLV5DungeonItem;
    /* 0x178 */ bool mIconDebug;
    /* 0x179 */ bool mIconDisplay[22];
};  // Size: 0x190

class dMeter_fmapHIO_c {
public:
    enum {
        /* 0x0 */ REGION_ORDONA,
        /* 0x1 */ REGION_FARON,
        /* 0x2 */ REGION_ELDIN,
        /* 0x3 */ REGION_LANAYRU,
        /* 0x4 */ REGION_GERUDO,
        /* 0x5 */ REGION_SNOWPEAK,
        /* 0x6 */ REGION_CASTLE,
    };

    enum {
        /* 0x0 */ WORLD_VIEW,
        /* 0x1 */ REGION_VIEW,
        /* 0x2 */ ZOOM_VIEW
    };

    enum {
        /* 0x0 */ TYPE_DEFAULT,
        /* 0x1 */ TYPE_OVERWORLD,
        /* 0x3 */ TYPE_DUNGEON,
        /* 0x2 */ TYPE_HYRULE_CASTLE,
    };

    struct BlinkAnime {
        /* 0x0 */ JUtility::TColor mBlack;
        /* 0x4 */ JUtility::TColor mWhite;
        /* 0x8 */ int16_t mBlinkSpeed;
        /* 0xA */ uint8_t mMax;
        /* 0xB */ uint8_t mMin;
    };  // Size: 0xC

    struct MapBlinkAnime {
        MapBlinkAnime();

        /* 0x00 */ BlinkAnime mSelectedRegion;
        /* 0x0C */ BlinkAnime mUnselectedRegion;
        /* 0x18 */ JUtility::TColor mUnreachedRegionBlack;
        /* 0x1C */ JUtility::TColor mUnreachedRegionWhite;
        /* 0x20 */ JUtility::TColor field_0x20;
        /* 0x24 */ JUtility::TColor field_0x24;
    };  // Size: 0x28

    /* 0x000 */ void* vtable;
    /* 0x004 */ uint8_t field_0x4[4];
    /* 0x008 */ JKRArchive* field_0x8;
    /* 0x00C */ void* field_0xc;
    /* 0x010 */ void* field_0x10;
    /* 0x014 */ void* field_0x14;
    /* 0x018 */ void* field_0x18;
    /* 0x01C */ MapBlinkAnime mMapBlink[3];
    /* 0x094 */ int16_t mDisplayFrameNum;
    /* 0x096 */ int16_t mUndisplayFrameNum;
    /* 0x098 */ uint8_t field_0x98[4];
    /* 0x09C */ float mRegionZoomRange;
    /* 0x0A0 */ float mStageZoomScale;
    /* 0x0A4 */ float mWorldGridWidth;
    /* 0x0A8 */ float mRegionGridWidth;
    /* 0x0AC */ float mMapTopLeftPosX;
    /* 0x0B0 */ float mMapTopLeftPosY;
    /* 0x0B4 */ float mMapScale;
    /* 0x0B8 */ float mBackgroundAlpha;
    /* 0x0BC */ float mBackgroundFrontAlpha;
    /* 0x0C0 */ float mScrollSpeedRegionFast;
    /* 0x0C4 */ float mScrollSpeedRegionZoomFast;
    /* 0x0C8 */ float mScrollSpeedWorldFast;
    /* 0x0CC */ float mScrollSpeedDungeonMapFast;
    /* 0x0D0 */ float mScrollSpeedRegionSlow;
    /* 0x0D4 */ float mScrollSpeedRegionZoomSlow;
    /* 0x0D8 */ float mScrollSpeedWorldSlow;
    /* 0x0DC */ float mScrollSpeedDungeonMapSlow;
    /* 0x0E0 */ float mScrollSpeedSlowBound;
    /* 0x0E4 */ float mScrollSpeedFastBound;
    /* 0x0E8 */ float mTitlePosX;
    /* 0x0EC */ float mTitlePosY;
    /* 0x0F0 */ float mTitleScale;
    /* 0x0F4 */ float mSubTitlePosX;
    /* 0x0F8 */ float mSubTitlePosY;
    /* 0x0FC */ float mSubTitleScale;
    /* 0x100 */ float mAreaMovementPosX;
    /* 0x104 */ float mAreaMovementPosY;
    /* 0x108 */ float mAreaMovementScale;
    /* 0x10C */ float mClosingPosX;
    /* 0x110 */ float mClosingPosY;
    /* 0x114 */ float mClosingScale;
    /* 0x118 */ float mDoIconPosX;
    /* 0x11C */ float mDoIconPosY;
    /* 0x120 */ float mDoIconScale;
    /* 0x124 */ float mZButtonPosX;
    /* 0x128 */ float mZButtonPosY;
    /* 0x12C */ float mZButtonScale;
    /* 0x130 */ float mAButtonPosX;
    /* 0x134 */ float mAButtonPosY;
    /* 0x138 */ float mAButtonScale;
    /* 0x13C */ float mBButtonPosX;
    /* 0x140 */ float mBButtonPosY;
    /* 0x144 */ float mBButtonScale;
    /* 0x148 */ float mZButtonTextPosX;
    /* 0x14C */ float mZButtonTextPosY;
    /* 0x150 */ float mZButtonTextScale;
    /* 0x154 */ float mAButtonTextPosX;
    /* 0x158 */ float mAButtonTextPosY;
    /* 0x15C */ float mAButtonTextScale;
    /* 0x160 */ float mBButtonTextPosX;
    /* 0x164 */ float mBButtonTextPosY;
    /* 0x168 */ float mBButtonTextScale;
    /* 0x16C */ float mRegionImagePosX[8];
    /* 0x18C */ float mRegionImagePosZ[8];
    /* 0x1AC */ float mRegionImageScale[8];
    /* 0x1CC */ float mRegionScrollRangeMinX[8];
    /* 0x1EC */ float mRegionScrollRangeMinZ[8];
    /* 0x20C */ float mRegionScrollRangeMaxX[8];
    /* 0x22C */ float mRegionScrollRangeMaxZ[8];
    /* 0x24C */ float mCursorScale;
    /* 0x250 */ float mCursorSpeed;
    /* 0x254 */ JUtility::TColor mCursorBlack;
    /* 0x258 */ JUtility::TColor mCursorWhite;
    /* 0x25C */ cXyz field_0x25c[12];
    /* 0x2EC */ bool mCursorDebugON;
    /* 0x2ED */ bool mButtonDebugON;
    /* 0x2EE */ uint8_t field_0x2ee[4];
    /* 0x2F2 */ uint8_t mMapType;
    /* 0x2F3 */ bool mDisplayWorldOrigin;
    /* 0x2F4 */ bool mDisplayRegionOrigin;
    /* 0x2F5 */ bool mDisplayStageOrigin;
    /* 0x2F6 */ bool mDisplayWorldGrid;
    /* 0x2F7 */ bool mDisplayRegionGrid;
    /* 0x2F8 */ bool mDisplayReferenceArea;
    /* 0x2F9 */ uint8_t field_0x2f9;
    /* 0x2FA */ bool mTerminalOutput;
    /* 0x2FB */ bool mPortalDataTerminalOutput;
    /* 0x2FC */ bool mAllRegionsUnlocked;
    /* 0x2FD */ bool mDisplayAllPaths;
    /* 0x2FE */ bool mRegionPrintGlobalScroll;
    /* 0x2FF */ bool mRangeCheck;
    /* 0x300 */ bool mRangeCheckDrawPriority;
    /* 0x301 */ bool mPortalWarpON;
    /* 0x302 */ bool mDrawBackground;
    /* 0x303 */ uint8_t field_0x303;
    /* 0x304 */ uint8_t mRangeCheckInterval;
    /* 0x305 */ uint8_t field_0x305;
    /* 0x306 */ bool mScrollRangeDebugON;
    /* 0x307 */ bool mScrollRangeDisplay;
    /* 0x308 */ bool field_0x308;  // related to scroll range display
    /* 0x309 */ bool mRegionImageDebug;
    /* 0x30A */ bool mRegionBitTerminalOutput;
    /* 0x30B */ bool mDebugRegionBits[8];
    /* 0x314 */ dMeter_mapIconHIO_c mMapIconHIO;
};  // Size: 0x4A4

static_assert(sizeof(dMeter_fmapHIO_c) == 1188);

class dMeter_cursorHIO_c {
public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ uint8_t field_0x4[4];
    /* 0x08 */ cXyz mSeraShopObjZoom;
    /* 0x14 */ cXyz mObjZoom;
    /* 0x20 */ cXyz mMagicArmorObjZoom;
    /* 0x2C */ float mShopCursorScale;
    /* 0x30 */ float mShopCursorOffsetY;
    /* 0x34 */ float mMagicArmorCursorOffsetX;
    /* 0x38 */ float mMagicArmorCursorOffsetY;
    /* 0x3C */ int16_t mSeraShopObjZoomAngleX;
    /* 0x3E */ int16_t mShopObjZoomAngleX;
    /* 0x40 */ int16_t mMagicArmorObjZoomAngleX;
};

static_assert(sizeof(dMeter_cursorHIO_c) == 68);

extern "C" {
extern dMeter_drawHIO_c g_drawHIO;
}

#endif /* D_METER_D_METER_HIO_H */
