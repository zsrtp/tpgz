#ifndef Z2AUDIOMGR_H
#define Z2AUDIOMGR_H

#include "../JSystem/JAudio2/JASAudioReseter.h"
#include "Z2Audience.h"
#include "Z2FxLineMgr.h"
#include "Z2SceneMgr.h"
#include "Z2SeMgr.h"
#include "Z2SeqMgr.h"
#include "Z2SoundMgr.h"
#include "Z2SoundObjMgr.h"
#include "Z2SoundStarter.h"
#include "Z2SpeechMgr2.h"
#include "Z2StatusMgr.h"

#ifdef GCN_PLATFORM
class Z2AudioMgr {
public:
    /* 0x0000 */ Z2SeMgr mSeMgr;
    /* 0x03D0 */ Z2SeqMgr mSeqMgr;
    /* 0x04A4 */ Z2SceneMgr mSceneMgr;
    /* 0x04C4 */ Z2StatusMgr mStatusMgr;
    /* 0x04F4 */ Z2SoundObjMgr mSoundObjMgr;
    /* 0x0514 */ void* vtable;
    /* 0x0518 */ bool mResettingFlag;
    /* 0x0519 */ bool field_0x519;
    /* 0x051C */ JASAudioReseter mAudioReseter;
    /* 0x052C */ Z2SoundStarter mSoundStarter;
    /* 0x0530 */ Z2SoundMgr mSoundMgr;
    /* 0x0D40 */                       // Z2SoundInfo mSoundInfo;
    /* 0x0D40 */ void* mSoundInfo[3];  // remove later
    /* 0x0D4C */ Z2Audience mAudience;
    /* 0x0F2C */ Z2SpeechMgr2 mSpeechMgr;
    /* 0x1370 */ Z2FxLineMgr mFxLineMgr;
};  // Size: 0x138C

static_assert(sizeof(Z2AudioMgr) == 0x138C);
#endif

#ifdef WII_PLATFORM
class Z2AudioMgr {
public:
    /* 0x0000 */ Z2SeMgr mSeMgr;
    /* 0x03E4 */ Z2SeqMgr mSeqMgr;
#ifndef WII_NTSCU_10
    uint8_t _p1[0x4];
#endif
    /* 0x04B4 */ Z2SceneMgr mSceneMgr;
    /* 0x04D4 */ Z2StatusMgr mStatusMgr;
    /* 0x0504 */ Z2SoundObjMgr mSoundObjMgr;
    /* 0x0524 */ void* vtable;
    /* 0x0528 */ bool mResettingFlag;
    /* 0x0529 */ bool field_0x519;
    /* 0x052C */ JASAudioReseter mAudioReseter;
    /* 0x053C */ Z2SoundStarter mSoundStarter;
    /* 0x0540 */ Z2SoundMgr mSoundMgr;
    /* 0x0D58 */                       // Z2SoundInfo mSoundInfo;
    /* 0x0D58 */ void* mSoundInfo[3];  // remove later
    /* 0x0D64 */ Z2Audience mAudience;
    /* 0x0F44 */ Z2SpeechMgr2 mSpeechMgr;
    /* 0x1388 */ Z2FxLineMgr mFxLineMgr;
};
#endif

/* inline Z2AudioMgr* Z2GetAudioMgr() {
    return Z2AudioMgr::getInterface();
} */

#endif /* Z2AUDIOMGR_H */