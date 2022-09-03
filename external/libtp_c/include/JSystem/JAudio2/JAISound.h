#ifndef JAISOUND_H
#define JAISOUND_H

#include "../JGeometry.h"
#include "JAISoundHandles.h"
#include "JAISoundParams.h"
#include <cstddef>

class JAISoundID {
public:
    operator uint32_t() const { return this->mId; }
    JAISoundID(uint32_t pId) { mId = pId; };
    JAISoundID() {}

private:
    uint32_t mId;
};

struct JASTrack {};

struct JAISoundStatus_ {
    void init() {
        field_0x0 = 0;
        field_0x1 = 0;
        *((uint16_t*)(this) + 2) = 0;
        user_data = 0;
    }

    /* 0x0 */ uint8_t field_0x0;
    /* 0x1 */ uint8_t field_0x1;
    /* 0x2 */ uint8_t state[2];  // debug accesses like "state.flags.calcedOnce"
    /* 0x4 */ uint32_t user_data;
};  // Size: 0x6

struct JAISoundFader {
    void forceIn() {
        mIntensity = 1.0f;
        field_0x4.zero();
    }

    /* 0x00 */ float mIntensity;
    /* 0x04 */ JAISoundParamsTransition::TTransition field_0x4;
};  // Size: 0x10

class JAISoundHandle;
class JAIAudible;
class JAIAudience;
class JAISound {
public:
    uint32_t getUserData() const { return status_.user_data; }
    bool isHandleAttached() const { return handle_ != NULL; }

    /* 0x00 */ void* vtable;
    /* 0x04 */ JAISoundHandle* handle_;
    /* 0x08 */ JAIAudible* audible_;
    /* 0x0C */ JAIAudience* audience_;
    /* 0x10 */ int32_t lifeTime;
    /* 0x14 */ int32_t prepareCount;
    /* 0x18 */ JAISoundID soundID;
    /* 0x1C */ JAISoundStatus_ status_;
    /* 0x24 */ JAISoundFader fader;
    /* 0x34 */ int32_t field_0x34;
    /* 0x38 */ int32_t mCount;
    /* 0x3C */ JAISoundParams params;
};  // Size: 0x98

class JAISoundActivity {
public:
    void init() { field_0x0 = 0; }

    /* 0x0 */ uint8_t field_0x0;
};

#endif /* JAISOUND_H */
