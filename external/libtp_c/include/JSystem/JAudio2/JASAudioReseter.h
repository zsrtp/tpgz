#ifndef JASAUDIORESETER_H
#define JASAUDIORESETER_H

#include "../../dolphin/types.h"

struct JASAudioReseter {
    /* 0x0 */ u32 field_0x0;
    /* 0x4 */ f32 mDSPLevel;
    /* 0x8 */ s32 mIsDone;
    /* 0xC */ bool field_0xc;
};  // Size: 0x10

#endif /* JASAUDIORESETER_H */