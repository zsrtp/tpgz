#ifndef C_BG_S_CHK_H
#define C_BG_S_CHK_H

#include "../../dolphin/types.h"

class cBgS_GrpPassChk {
public:
    void* vtable;
};

class cBgS_PolyPassChk;

class cBgS_Chk {
public:
    /* 0x00 */ cBgS_PolyPassChk* mPolyPassChk;
    /* 0x04 */ cBgS_GrpPassChk* mGrpPassChk;
    /* 0x08 */ u32 mActorPid;
    /* 0x0C */ u8 unk_0x0C;
    /* 0x10 */ void* vtable;

    void setActorPid(u32 pid) { mActorPid = pid; }
    u32 GetActorPid() const { return mActorPid; }
    void SetPolyPassChk(cBgS_PolyPassChk* p_chk) { mPolyPassChk = p_chk; }
    void SetGrpPassChk(cBgS_GrpPassChk* p_chk) { mGrpPassChk = p_chk; }
};

static_assert(sizeof(cBgS_Chk) == 0x14);

#endif /* C_BG_S_CHK_H */
