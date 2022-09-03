#ifndef Z2SOUNDMGR_H
#define Z2SOUNDMGR_H

#include "../JSystem/JAudio2/JAISeMgr.h"
#include "../JSystem/JAudio2/JAISeqMgr.h"
#include "../JSystem/JAudio2/JAISound.h"
#include "../JSystem/JAudio2/JAIStreamMgr.h"

#ifdef GCN_PLATFORM
class Z2SoundMgr {
public:
    /* 0x000 */ void* vtable;
    /* 0x004 */ JAISeMgr mSeMgr;
    /* 0x728 */ JAISeqMgr mSeqMgr;
    /* 0x79C */ JAIStreamMgr mStreamMgr;
    /* 0x80C */ JAISoundID field_0x80c;
};  // Size: 0x810

static_assert(sizeof(Z2SoundMgr) == 0x810);
#endif

#ifdef WII_PLATFORM
class Z2SoundMgr {
public:
    /* 0x000 */ void* vtable;
    /* 0x004 */ JAISeMgr mSeMgr;
    /* 0x728 */ uint8_t field_0x728[4];
    /* 0x72C */ JAISeqMgr mSeqMgr;
    /* 0x7A0 */ uint8_t field_0x7a0[4];
    /* 0x7A4 */ JAIStreamMgr mStreamMgr;
    /* 0x814 */ JAISoundID field_0x80c;
};
#endif

#endif /* Z2SOUNDMGR_H */