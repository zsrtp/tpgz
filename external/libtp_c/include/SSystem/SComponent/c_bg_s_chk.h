#ifndef C_BG_S_CHK_H
#define C_BG_S_CHK_H

#include <stdint.h>

class cBgS_Chk {
public:
    /* 0x0 */ uint32_t mPolyPassChk;
    /* 0x4 */ uint32_t mGrpPassChk;
    /* 0x8 */ uint32_t mActorPid;
    /* 0xC */ uint8_t unk_0x0C;
    /* 0x10 */ void* vtable;
};

#endif /* C_BG_S_CHK_H */
