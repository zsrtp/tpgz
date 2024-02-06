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
    /* 0xC0 */ u8 mLinkState;
    /* 0xC1 */ u8 unk193;
    /* 0xC2 */ u8 unk194;
    /* 0xC3 */ u8 mLinkHp;
    /* 0xC4 */ u8 mBootsType;
    /* 0xC5 */ u8 mLanternState;
    /* 0xC6 */ u8 unk198;
    /* 0xC7 */ u8 unk199;
    /* 0xC8 */ u8 unk200;
    /* 0xC9 */ u8 unk201;
    /* 0xCA */ u8 mSinkDepth;
    /* 0xCB */ u8 flags1;
    /* 0xCC */ u8 flags2;
};
#pragma pack(pop)

class Z2CreatureRide {
public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ u8 Z2Creature_members[140];
    /* 0x90 */ u8 Z2RideSoundStarter[8];
    /* 0x98 */ bool mLinkRiding;
    /* 0x99 */ u8 padding[3];
};

#endif /* Z2CREATURE_H */
