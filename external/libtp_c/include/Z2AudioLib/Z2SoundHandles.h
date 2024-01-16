#ifndef Z2SOUNDHANDLES_H
#define Z2SOUNDHANDLES_H

#include "../JSystem/JAudio2/JAISound.h"
#include "../JSystem/JSupport/JSUList.h"

class Z2SoundHandlePool : public JAISoundHandle, JSULink<Z2SoundHandlePool> {};

class Z2SoundHandles : protected JSUList<Z2SoundHandlePool> {
public:
    u32 getNumHandles() const { return this->getNumLinks(); }

private:
    u8 mNumHandles;
};

#endif /* Z2SOUNDHANDLES_H */
