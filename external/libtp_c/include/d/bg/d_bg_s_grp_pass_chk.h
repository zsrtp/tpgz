#ifndef D_BG_D_BG_S_GRP_PASS_CHK_H
#define D_BG_D_BG_S_GRP_PASS_CHK_H

#include "../../dolphin/types.h"

class cBgS_GrpPassChk {
public:
    virtual ~cBgS_GrpPassChk() {}
};

class dBgS_GrpPassChk : public cBgS_GrpPassChk {
public:
    u32 mGrp;
};

#endif /* D_BG_D_BG_S_GRP_PASS_CHK_H */
