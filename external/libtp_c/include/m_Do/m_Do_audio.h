#ifndef M_DO_M_DO_AUDIO_H
#define M_DO_M_DO_AUDIO_H

#include "../dolphin/types.h"
#include "../Z2AudioLib/Z2AudioMgr.h"

class mDoAud_zelAudio_c {
public:
    Z2AudioMgr mAudioMgr;
};

extern "C" {
extern mDoAud_zelAudio_c g_mDoAud_zelAudio;
}

// Functions
#ifdef GCN_PLATFORM
typedef void (*mDoAud_seStartLevel_t)(u32, Vec const*, u32, s8);
#define mDoAud_seStartLevel ((mDoAud_seStartLevel_t)mDoAud_seStartLevel_addr)

#endif

#endif /* M_DO_M_DO_AUDIO_H */
