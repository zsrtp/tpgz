#include "utils/audio.h"

void GZ_enableBGM() {
    g_mDoAud_zelAudio.mAudioMgr.mSeqMgr.mHeightVol.mIntensity = 1.0f;  // BG Audio
#ifndef WII_PLATFORM
    g_mDoAud_zelAudio.mAudioMgr.mSoundMgr.mSeqMgr.mMove.mParams.mVolume = 1.0f;
    g_mDoAud_zelAudio.mAudioMgr.mSoundMgr.mStreamMgr.mParams.mParams.mVolume = 1.0f;
#endif
}

void GZ_disableBGM() {
    g_mDoAud_zelAudio.mAudioMgr.mSeqMgr.mHeightVol.mIntensity = 0.0f;  // BG Audio
#ifndef WII_PLATFORM
    g_mDoAud_zelAudio.mAudioMgr.mSoundMgr.mSeqMgr.mMove.mParams.mVolume = 0.0f;
    g_mDoAud_zelAudio.mAudioMgr.mSoundMgr.mStreamMgr.mParams.mParams.mVolume = 0.0f;
#endif
}

void GZ_disableSFX() {
    for (int i = 0; i < 16; i++) {
        g_mDoAud_zelAudio.mAudioMgr.mSoundMgr.mSeMgr.mCategoryMgrs[i].mParams.mParams.mVolume =
            0.0f;
    }

    g_mDoAud_zelAudio.mAudioMgr.mSoundMgr.mSeMgr.mParams.mParams.mVolume = 0.0f;
}

void GZ_enableSFX() {
    for (int i = 0; i < 16; i++) {
        g_mDoAud_zelAudio.mAudioMgr.mSoundMgr.mSeMgr.mCategoryMgrs[i].mParams.mParams.mVolume =
            1.0f;
    }

    g_mDoAud_zelAudio.mAudioMgr.mSoundMgr.mSeMgr.mParams.mParams.mVolume = 1.0f;
}