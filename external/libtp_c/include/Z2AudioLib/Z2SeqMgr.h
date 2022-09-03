#ifndef Z2SEQMGR_H
#define Z2SEQMGR_H

#include "../JSystem/JAudio2/JAISound.h"

// move TTransition / Z2SoundFader ?
struct TTransition {
    /* 0x0 */ float field_0x0;
    /* 0x4 */ float field_0x4;
    /* 0x8 */ uint32_t mCount;
};  // Size = 0xC

struct Z2SoundFader {
    void move(float vol, uint32_t count) {
        mIntensity = vol;
        mTransition.zero();
    }

    /* 0x0 */ float mIntensity;
    /* 0x4 */ JAISoundParamsTransition::TTransition mTransition;
};  // Size = 0x10

class Z2SeqMgr {
public:
    void i_setTwilightGateVol(float vol) { mTwilightGateVol = vol; }

    void i_setWindStoneVol(float vol, uint32_t count) { field_0x94.move(vol, count); }

    void i_bgmAllUnMute(uint32_t count) { mBgmAll.move(1.0f, count); }

    void i_unMuteSceneBgm(uint32_t count) {
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
    /* 0xB4 */ float mTwilightGateVol;
    /* 0xB8 */ uint16_t field_0xb8;
    /* 0xBA */ uint8_t field_0xba;
    /* 0xBB */ uint8_t field_0xbb;
    /* 0xBC */ uint8_t field_0xbc;
    /* 0xBD */ uint8_t field_0xbd;
    /* 0xBE */ uint8_t field_0xbe;
    /* 0xBF */ uint8_t field_0xbf;
    /* 0xC0 */ uint8_t field_0xc0;
#ifdef GCN_PLATFORM
    /* 0xC1 */ uint8_t field_0xc1;
    /* 0xC2 */ uint8_t field_0xc2;
    /* 0xC3 */ uint8_t field_0xc3;
    /* 0xC4 */ uint8_t field_0xc4;
#endif
    /* 0xC8 */ float field_0xc8;
    /* 0xCC */ float field_0xcc;
    /* 0xD0 */ uint8_t mFlags;
};  // Size = 0xD4

#endif /* Z2SEQMGR_H */