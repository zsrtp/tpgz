#ifndef D_BG_D_BG_S_GRP_PASS_CHK_H
#define D_BG_D_BG_S_GRP_PASS_CHK_H

#include "../../dolphin/types.h"
#include "../../SSystem/SComponent/c_bg_s_chk.h"

class dBgS_GrpPassChk : public cBgS_GrpPassChk {
public:
    dBgS_GrpPassChk() {
        mGrp = 1;
    }

    enum {
        /* 0x1 */ NORMAL_GRP = 1,
        /* 0x2 */ WATER_GRP
    };

    void OnWaterGrp() { mGrp |= WATER_GRP; }
    void OnSpl() { mGrp |= WATER_GRP; }
    void OnNormalGrp() { mGrp |= NORMAL_GRP; }
    void OffNormalGrp() { mGrp &= ~NORMAL_GRP; }
    void OnFullGrp() { mGrp |= 3; }

private:
    u32 mGrp;
};

#endif /* D_BG_D_BG_S_GRP_PASS_CHK_H */
