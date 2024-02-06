#ifndef C_BG_S_GND_CHK_H
#define C_BG_S_GND_CHK_H

#include "c_bg_s_chk.h"
#include "c_bg_s_poly_info.h"
#include "c_xyz.h"

class cBgS_GndChk : public cBgS_Chk {
public:
    /* 0x14 */ cBgS_PolyInfo mPolyInfo;
    /* 0x24 */ cXyz m_pos;
    /* 0x30 */ int field_0x30;
    /* 0x34 */ f32 mNowY;
    /* 0x38 */ void* mWallPrecheck;
};

#endif /* C_BG_S_GND_CHK_H */
