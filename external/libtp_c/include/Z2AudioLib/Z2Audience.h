#ifndef Z2AUDIENCE_H
#define Z2AUDIENCE_H

#include "../JSystem/JAudio2/JAIAudience.h"
#include "../JSystem/JGeometry.h"
#include "../dolphin/mtx/vec.h"

struct Z2Audible;

struct Z2AudioCamera {
    /* 0x00 */ u8 field_0x0[0x30];  // set up JGeometry::TPosition3
    /* 0x30 */ JGeometry::TVec3<f32> mVel;
    /* 0x3C */ JGeometry::TVec3<f32> mPos;
    /* 0x48 */ JGeometry::TVec3<f32> field_0x48;
    /* 0x54 */ f32 mFovySin;
    /* 0x58 */ f32 mVolCenterZ;
    /* 0x5C */ f32 mTargetVolume;
    /* 0x60 */ f32 mDolbyCenterZ;
    /* 0x64 */ f32 mCamDist;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6c;
    /* 0x70 */ bool mSetMainCamera;
};  // Size: 0x74

struct Z2SpotMic {
    /* 0x00 */ f32 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xc;
    /* 0x10 */ int field_0x10[1];
    /* 0x14 */ Vec* mPosPtr;
    /* 0x18 */ f32 field_0x18[1];
    /* 0x1C */ f32 field_0x1c;
    /* 0x20 */ f32 field_0x20[1];
    /* 0x24 */ bool mIgnoreIfOut;
    /* 0x25 */ bool mMicOn;
    /* 0x26 */ u8 field_0x26[1];
};  // Size: 0x28

struct Z2Audience3DSetting {
    /* 0x000 */ f32 field_0x0;
    /* 0x004 */ f32 field_0x4;
    /* 0x008 */ f32 field_0x8;
    /* 0x00C */ f32 field_0xc;
    /* 0x010 */ f32 field_0x10;
    /* 0x014 */ f32 field_0x14;
    /* 0x018 */ f32 field_0x18;
    /* 0x01C */ f32 field_0x1c;
    /* 0x020 */ f32 field_0x20;
    /* 0x024 */ f32 field_0x24;
    /* 0x028 */ f32 field_0x28;
    /* 0x02C */ f32 field_0x2c;
    /* 0x030 */ f32 field_0x30;
    /* 0x034 */ f32 field_0x34;
    /* 0x038 */ f32 field_0x38;
    /* 0x03C */ f32 field_0x3c;
    /* 0x040 */ f32 field_0x40;
    /* 0x044 */ f32 field_0x44;
    /* 0x048 */ f32 field_0x48;
    /* 0x04C */ f32 field_0x4c;
    /* 0x050 */ f32 field_0x50;
    /* 0x054 */ f32 field_0x54;
    /* 0x058 */ f32 field_0x58;
    /* 0x05C */ f32 field_0x5c;
    /* 0x060 */ f32 field_0x60;
    /* 0x064 */ int field_0x64;
    /* 0x068 */ f32 field_0x68;
    /* 0x06C */ f32 field_0x6c;
    /* 0x070 */ f32 field_0x70[15];
    /* 0x0AC */ f32 field_0xac[15];
    /* 0x0E8 */ f32 field_0xe8[15];
    /* 0x124 */ bool mVolumeDistInit;
    /* 0x125 */ bool mDolbyDistInit;
};  // Size: 0x128

struct Z2AudibleChannel {};

struct Z2Audience : public JAIAudience {
    /* 0x004 */ f32 field_0x4;
    /* 0x008 */ u8 field_0x8;
    /* 0x00C */ Z2Audience3DSetting mSetting;
    /* 0x134 */ Z2AudioCamera mAudioCamera[1];
    /* 0x1A8 */ Z2SpotMic mSpotMic[1];
    /* 0x1D0 */ Z2SpotMic* mLinkMic;
    /* 0x1D4 */ int mNumPlayers;
    /* 0x1D8 */ u8 field_0x1d8[4];
    /* 0x1DC */ bool mUsingOffMicVol;
};  // Size: 0x1E0

#endif /* Z2AUDIENCE_H */