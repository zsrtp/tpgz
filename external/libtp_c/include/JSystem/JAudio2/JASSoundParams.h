#ifndef JASSOUNDPARAMS_H
#define JASSOUNDPARAMS_H

#include <stdint.h>

struct JASSoundParams {
    void initVolume() { mVolume = 1.0f; }
    void initFxMix() { mFxMix = 0.0f; }
    void initPitch() { mPitch = 1.0f; }
    void initPan() { mPan = 0.5f; }
    void initDolby() { mDolby = 0.0f; }
    void init() {
        initVolume();
        initPitch();
        initFxMix();
        initPan();
        initDolby();
    }

    JASSoundParams() { init(); }

    /* 0x00 */ float mVolume;
    /* 0x04 */ float mFxMix;
    /* 0x08 */ float mPitch;
    /* 0x0C */ float mPan;
    /* 0x10 */ float mDolby;
};  // Size: 0x14

#endif /* JASSOUNDPARAMS_H */