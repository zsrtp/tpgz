#ifndef Z2AUDIENCE_H
#define Z2AUDIENCE_H

#include "../JSystem/JAudio2/JAIAudience.h"
#include "../JSystem/JGeometry.h"
#include "../dolphin/mtx/vec.h"

struct Z2Audible;

struct Z2AudioCamera {
    /* 0x00 */ uint8_t field_0x0[0x30];  // set up JGeometry::TPosition3
    /* 0x30 */ JGeometry::TVec3<float> mVel;
    /* 0x3C */ JGeometry::TVec3<float> mPos;
    /* 0x48 */ JGeometry::TVec3<float> field_0x48;
    /* 0x54 */ float mFovySin;
    /* 0x58 */ float mVolCenterZ;
    /* 0x5C */ float mTargetVolume;
    /* 0x60 */ float mDolbyCenterZ;
    /* 0x64 */ float mCamDist;
    /* 0x68 */ float field_0x68;
    /* 0x6C */ float field_0x6c;
    /* 0x70 */ bool mSetMainCamera;
};  // Size: 0x74

struct Z2SpotMic {
    /* 0x00 */ float field_0x0;
    /* 0x04 */ float field_0x4;
    /* 0x08 */ float field_0x8;
    /* 0x0C */ float field_0xc;
    /* 0x10 */ int field_0x10[1];
    /* 0x14 */ Vec* mPosPtr;
    /* 0x18 */ float field_0x18[1];
    /* 0x1C */ float field_0x1c;
    /* 0x20 */ float field_0x20[1];
    /* 0x24 */ bool mIgnoreIfOut;
    /* 0x25 */ bool mMicOn;
    /* 0x26 */ uint8_t field_0x26[1];
};  // Size: 0x28

struct Z2Audience3DSetting {
    /* 0x000 */ float field_0x0;
    /* 0x004 */ float field_0x4;
    /* 0x008 */ float field_0x8;
    /* 0x00C */ float field_0xc;
    /* 0x010 */ float field_0x10;
    /* 0x014 */ float field_0x14;
    /* 0x018 */ float field_0x18;
    /* 0x01C */ float field_0x1c;
    /* 0x020 */ float field_0x20;
    /* 0x024 */ float field_0x24;
    /* 0x028 */ float field_0x28;
    /* 0x02C */ float field_0x2c;
    /* 0x030 */ float field_0x30;
    /* 0x034 */ float field_0x34;
    /* 0x038 */ float field_0x38;
    /* 0x03C */ float field_0x3c;
    /* 0x040 */ float field_0x40;
    /* 0x044 */ float field_0x44;
    /* 0x048 */ float field_0x48;
    /* 0x04C */ float field_0x4c;
    /* 0x050 */ float field_0x50;
    /* 0x054 */ float field_0x54;
    /* 0x058 */ float field_0x58;
    /* 0x05C */ float field_0x5c;
    /* 0x060 */ float field_0x60;
    /* 0x064 */ int field_0x64;
    /* 0x068 */ float field_0x68;
    /* 0x06C */ float field_0x6c;
    /* 0x070 */ float field_0x70[15];
    /* 0x0AC */ float field_0xac[15];
    /* 0x0E8 */ float field_0xe8[15];
    /* 0x124 */ bool mVolumeDistInit;
    /* 0x125 */ bool mDolbyDistInit;
};  // Size: 0x128

struct Z2AudibleChannel {};

struct Z2Audience : public JAIAudience {
    /* 0x004 */ float field_0x4;
    /* 0x008 */ uint8_t field_0x8;
    /* 0x00C */ Z2Audience3DSetting mSetting;
    /* 0x134 */ Z2AudioCamera mAudioCamera[1];
    /* 0x1A8 */ Z2SpotMic mSpotMic[1];
    /* 0x1D0 */ Z2SpotMic* mLinkMic;
    /* 0x1D4 */ int mNumPlayers;
    /* 0x1D8 */ uint8_t field_0x1d8[4];
    /* 0x1DC */ bool mUsingOffMicVol;
};  // Size: 0x1E0

#endif /* Z2AUDIENCE_H */