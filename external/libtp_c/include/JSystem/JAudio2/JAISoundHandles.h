#ifndef JAISOUNDHANDLES_H
#define JAISOUNDHANDLES_H

#include <cstddef>

class JAISound;
class JAISoundID;

class JAISoundHandle {
public:
    bool isSoundAttached() const { return sound_ != NULL; }
    operator bool() const { return isSoundAttached(); }
    JAISound* getSound() { return sound_; }

    JAISound* sound_;
};

class JAISoundHandles {
public:
    JAISoundHandles(JAISoundHandle* pHandle, int param_1) {
        *mSoundHandle = pHandle;
        numHandles_ = param_1;
    };

    JAISoundHandle** mSoundHandle;
    int numHandles_;
};

#endif /* JAISOUNDHANDLES_H */