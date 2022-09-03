#ifndef Z2SOUNDOBJMGR_H
#define Z2SOUNDOBJMGR_H

#include "../JSystem/JSupport/JSUList.h"

struct Z2CreatureEnemy;

class Z2SoundObjMgr : protected JSUList<Z2CreatureEnemy> {
public:
    bool isForceBattle() { return mForceBattle; }

    /* 0x0C */ uint8_t field_0xc[2];
    /* 0x0E */ uint16_t field_0xe;
    /* 0x10 */ uint16_t field_0x10;
    /* 0x12 */ uint16_t field_0x12;
    /* 0x14 */ uint8_t field_0x14;
    /* 0x15 */ uint8_t mEnemyNumNear;
    /* 0x16 */ uint8_t field_0x16;
    /* 0x17 */ uint8_t mEnemyNumVeryFar;
    /* 0x18 */ uint8_t field_0x18;
    /* 0x19 */ uint8_t mGhostEnemyState;
    /* 0x1A */ bool field_0x1a;
    /* 0x1B */ bool mTwilightBattle;
    /* 0x1C */ bool mForceBattle;
};  // Size = 0x20

#endif /* Z2SOUNDOBJMGR_H */