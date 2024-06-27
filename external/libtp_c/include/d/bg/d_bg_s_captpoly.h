#ifndef D_BG_S_CAPTPOLY_H
#define D_BG_S_CAPTPOLY_H

#include "d_bg_s_chk.h"
#include "d_bg_w.h"
#include "../../SSystem/SComponent/c_m3d_g_aab.h"
#include "../../SSystem/SComponent/c_bg_s_chk.h"

class cM3dGPla;

struct cBgD_Vtx_t {
    Vec vertex;
};

typedef int (*dBgS_CaptCallback)(dBgS_CaptPoly*, cBgD_Vtx_t*, int, int, int, cM3dGPla*);

class dBgS_CaptPoly {
public:
    dBgS_CaptPoly() {
        field_0x00.SetPolyPassChk(&field_0x14.mPolyPassChkInfo);
        field_0x00.SetGrpPassChk(&field_0x14.mGrpPassChkInfo);
        mpCallback = NULL;
    }

    /* 0x00 */ cBgS_Chk field_0x00;
    /* 0x14 */ dBgS_Chk field_0x14;
    /* 0x2C */ cM3dGAab mAab;
    /* 0x48 */ dBgS_CaptCallback mpCallback;
};

static_assert(sizeof(dBgS_CaptPoly) == 0x4C);

#endif /* D_BG_S_CAPTPOLY_H */
