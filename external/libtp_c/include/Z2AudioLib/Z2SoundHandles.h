#ifndef Z2SOUNDHANDLES_H
#define Z2SOUNDHANDLES_H

#include "../JSystem/JAudio2/JAISound.h"
#include "../JSystem/JSupport/JSUList.h"

class Z2SoundHandlePool : public JAISoundHandle, JSULink<Z2SoundHandlePool> {};

class Z2SoundHandles : protected JSUList<Z2SoundHandlePool> {
public:
    uint32_t getNumHandles() const { return this->getNumLinks(); }

private:
    uint8_t mNumHandles;
};

#endif /* Z2SOUNDHANDLES_H */
