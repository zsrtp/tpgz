#ifndef D_BG_D_BG_S_GND_CHK_H
#define D_BG_D_BG_S_GND_CHK_H

#include "../../SSystem/SComponent/c_bg_s_gnd_chk.h"
#include "d_bg_s_chk.h"

class dBgS_GndChk : public cBgS_GndChk {
public:
    /* 0x3C */ dBgS_Chk mChk;
};  // Size = 0x54

class dBgS_LinkGndChk : dBgS_GndChk {};

class dBgS_ObjGndChk : dBgS_GndChk {};

#endif /* D_BG_D_BG_S_GND_CHK_H */
