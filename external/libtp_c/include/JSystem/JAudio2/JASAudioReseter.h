#ifndef JASAUDIORESETER_H
#define JASAUDIORESETER_H

#include <stdint.h>

struct JASAudioReseter {
    /* 0x0 */ uint32_t field_0x0;
    /* 0x4 */ float mDSPLevel;
    /* 0x8 */ int32_t mIsDone;
    /* 0xC */ bool field_0xc;
};  // Size: 0x10

#endif /* JASAUDIORESETER_H */