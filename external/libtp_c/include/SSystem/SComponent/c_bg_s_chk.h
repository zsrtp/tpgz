#ifndef C_BG_S_CHK_H
#define C_BG_S_CHK_H

#include "../../dolphin/types.h"

class cBgS_Chk {
public:
    /* 0x0 */ u32 mPolyPassChk;
    /* 0x4 */ u32 mGrpPassChk;
    /* 0x8 */ u32 mActorPid;
    /* 0xC */ u8 unk_0x0C;
    /* 0x10 */ void* vtable;
};

#endif /* C_BG_S_CHK_H */
