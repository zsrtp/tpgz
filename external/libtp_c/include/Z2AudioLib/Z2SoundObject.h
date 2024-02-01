#ifndef Z2SOUNDOBJECT_H
#define Z2SOUNDOBJECT_H

#include "Z2SoundHandles.h"
#include "Z2SoundStarter.h"
#include "../dolphin/mtx/vec.h"

struct JAUSoundAnimationSound {};

class Z2SoundObjBase : protected Z2SoundHandles {
public:
    bool isAlive() const { return mIsInitialized; }

    /* 0x10 */ void* vtable;
    /* 0x14 */ Z2SoundStarter* mSoundStarter;
    /* 0x18 */ Vec* mSoundPos;
    /* 0x1C */ u16 field_0x1c;
    /* 0x1E */ u8 field_0x1e;
    /* 0x1F */ bool mIsInitialized;
};

class Z2SoundObjSimple : protected Z2SoundObjBase {
public:
};

class Z2SoundObjAnime : protected Z2SoundObjBase {
public:
    /* 0x20 */ void* field_0x20;  // JAUSoundAnimation*
    /* 0x24 */ int field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ int field_0x34;
    /* 0x38 */ int field_0x38;
    /* 0x3C */ int field_0x3c;
    /* 0x40 */ int field_0x40;
    /* 0x44 */ bool field_0x44;
};

class Z2DopplerSoundObjBase : protected Z2SoundHandles {};

#endif /* Z2SOUNDOBJECT_H */
