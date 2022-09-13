#ifndef C_BG_S_LIN_CHK_H
#define C_BG_S_LIN_CHK_H

#include "c_bg_s_chk.h"
#include "c_bg_s_poly_info.h"
#include "c_m3d_g_lin.h"
#include "c_xyz.h"
#include <stdint.h>

class cBgS_LinChk {
public:
    /* 0x000 */ cBgS_Chk mChk;
    /* 0x014 */ cBgS_PolyInfo mPolyInfo;
    /* 0x024 */ cM3dGLin mLin;
    /* 0x040 */ cXyz field_0x40;
    /* 0x04C */ int field_0x4c;
    /* 0x050 */ uint8_t mPreWallChk;
    /* 0x051 */ uint8_t mPreGroundChk;
    /* 0x052 */ uint8_t mPreRoofChk;
    /* 0x053 */ uint8_t mFrontFlag;
    /* 0x054 */ uint8_t mBackFlag;
};

#endif /* C_BG_S_LIN_CHK_H */
