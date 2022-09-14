#ifndef Z2CREATURE_H
#define Z2CREATURE_H

#include "../SSystem/SComponent/c_xyz.h"
#include "Z2SoundObject.h"

class Z2Creature {
public:
    Z2Creature();
    ~Z2Creature();

    virtual void deleteObject();

private:
    /* 0x04 */ int field_0x04;
    /* 0x08 */ Z2SoundObjAnime mSoundObjAnime;
    /* 0x50 */ Z2SoundObjSimple mSoundObjSimple1;
    /* 0x70 */ Z2SoundObjSimple mSoundObjSimple2;
};

struct Z2LinkSoundStarter : public Z2SoundStarter {
    Z2LinkSoundStarter(void);
    ~Z2LinkSoundStarter();
};

#pragma pack(push, 1)
class Z2CreatureLink : public Z2Creature {
public:
    Z2CreatureLink(void);
    ~Z2CreatureLink();

    /* 0x90 */ Z2LinkSoundStarter mLinkSoundStarter;
    /* 0x94 */ Z2SoundObjSimple mSoundObjSimple;
    /* 0xB4 */ cXyz field_0xb4;
    /* 0xC0 */ uint8_t mLinkState;
    /* 0xC1 */ uint8_t unk193;
    /* 0xC2 */ uint8_t unk194;
    /* 0xC3 */ uint8_t mLinkHp;
    /* 0xC4 */ uint8_t mBootsType;
    /* 0xC5 */ uint8_t mLanternState;
    /* 0xC6 */ uint8_t unk198;
    /* 0xC7 */ uint8_t unk199;
    /* 0xC8 */ uint8_t unk200;
    /* 0xC9 */ uint8_t unk201;
    /* 0xCA */ uint8_t mSinkDepth;
    /* 0xCB */ uint8_t flags1;
    /* 0xCC */ uint8_t flags2;
};
#pragma pack(pop)

class Z2CreatureRide {
public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ uint8_t Z2Creature_members[140];
    /* 0x90 */ uint8_t Z2RideSoundStarter[8];
    /* 0x98 */ bool mLinkRiding;
    /* 0x99 */ uint8_t padding[3];
};

#endif /* Z2CREATURE_H */
