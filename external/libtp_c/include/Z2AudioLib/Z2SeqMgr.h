#ifndef Z2SEQMGR_H
#define Z2SEQMGR_H

#include "../JSystem/JAudio2/JAISound.h"

// move TTransition / Z2SoundFader ?
struct TTransition {
    /* 0x0 */ f32 field_0x0;
    /* 0x4 */ f32 field_0x4;
    /* 0x8 */ u32 mCount;
};  // Size = 0xC

struct Z2SoundFader {
    void move(f32 vol, u32 count) {
        mIntensity = vol;
        mTransition.zero();
    }

    /* 0x0 */ f32 mIntensity;
    /* 0x4 */ JAISoundParamsTransition::TTransition mTransition;
};  // Size = 0x10

class Z2SeqMgr {
public:
    void i_setTwilightGateVol(f32 vol) { mTwilightGateVol = vol; }

    void i_setWindStoneVol(f32 vol, u32 count) { field_0x94.move(vol, count); }

    void i_bgmAllUnMute(u32 count) { mBgmAll.move(1.0f, count); }

    void i_unMuteSceneBgm(u32 count) {
        field_0x34.move(1.0f, 0);
        field_0x44.move(1.0f, count);
    }

    /* 0x00 */ JAISoundHandle mMainBgmHandle;
    /* 0x04 */ JAISoundHandle mSubBgmHandle;
    /* 0x08 */ JAISoundHandle field_0x08;
    /* 0x0C */ JAISoundHandle field_0x0c;
    /* 0x10 */ JAISoundID field_0x10;
    /* 0x14 */ Z2SoundFader field_0x14;
    /* 0x24 */ Z2SoundFader field_0x24;
    /* 0x34 */ Z2SoundFader field_0x34;
    /* 0x44 */ Z2SoundFader field_0x44;
    /* 0x54 */ Z2SoundFader field_0x54;
    /* 0x64 */ Z2SoundFader field_0x64;
    /* 0x74 */ Z2SoundFader mBgmAll;
    /* 0x84 */ Z2SoundFader mHeightVol;
    /* 0x94 */ Z2SoundFader field_0x94;
    /* 0xA4 */ Z2SoundFader field_0xa4;
    /* 0xB4 */ f32 mTwilightGateVol;
    /* 0xB8 */ u16 field_0xb8;
    /* 0xBA */ u8 field_0xba;
    /* 0xBB */ u8 field_0xbb;
    /* 0xBC */ u8 field_0xbc;
    /* 0xBD */ u8 field_0xbd;
    /* 0xBE */ u8 field_0xbe;
    /* 0xBF */ u8 field_0xbf;
    /* 0xC0 */ u8 field_0xc0;
#ifdef GCN_PLATFORM
    /* 0xC1 */ u8 field_0xc1;
    /* 0xC2 */ u8 field_0xc2;
    /* 0xC3 */ u8 field_0xc3;
    /* 0xC4 */ u8 field_0xc4;
#endif
    /* 0xC8 */ f32 field_0xc8;
    /* 0xCC */ f32 field_0xcc;
    /* 0xD0 */ u8 mFlags;
};  // Size = 0xD4

#endif /* Z2SEQMGR_H */