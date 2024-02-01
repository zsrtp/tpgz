#ifndef Z2FXLINEMGR_H
#define Z2FXLINEMGR_H

#include "../dolphin/types.h"

struct Z2FxLineEditNode {};

struct Z2FxLineConfig {};

struct Z2FxLineMgr {
    /* 0x00 */ int field_0x0;
    /* 0x04 */ void* mFxLineBuffer[4];
    /* 0x14 */ s8 mLineID;
    /* 0x15 */ s8 mFxDataNum;
    /* 0x16 */ bool mSetUnderWaterFx;
    /* 0x18 */ Z2FxLineEditNode* mHIOEdit;
};  // Size: 0x1C

#endif /* Z2FXLINEMGR_H */