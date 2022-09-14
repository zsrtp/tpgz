#ifndef Z2SPEECHMGR2_H
#define Z2SPEECHMGR2_H

#include "../JSystem/JAudio2/JAISoundHandles.h"
#include "Z2SoundStarter.h"
#include "../dolphin/mtx/vec.h"

struct Z2SpeechStarter : public Z2SoundStarter {};

struct Z2SpeechMgr2 {
    /* 0x000 */ JAISoundHandle field_0x0;
    /* 0x004 */ JAISoundHandle field_0x4;
    /* 0x008 */ uint32_t random;
    /* 0x00C */ Z2SpeechStarter mSpeech;
    /* 0x010 */ uint16_t field_0x10[500];
    /* 0x3F8 */ uint16_t field_0x3f8;
    /* 0x3FA */ uint16_t field_0x3fa;
    /* 0x3FC */ uint16_t field_0x3fc;
    /* 0x3FE */ uint8_t field_0x3fe;
    /* 0x3FF */ uint8_t field_0x3ff;
    /* 0x400 */ uint8_t field_0x400;
    /* 0x401 */ uint8_t field_0x401;
    /* 0x402 */ uint8_t field_0x402[64];
};  // Size: 0x444

#endif /* Z2SPEECHMGR2_H */