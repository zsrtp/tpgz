#ifndef D_BG_D_BG_S_LIN_CHK_H
#define D_BG_D_BG_S_LIN_CHK_H

#include "../../SSystem/SComponent/c_bg_s_lin_chk.h"
#include "d_bg_s_chk.h"
#include "../../f_op/f_op_actor.h"

class dBgS_LinChk {
public:
    /* 0x00 */ cBgS_LinChk mLinChk;
    /* 0x58 */ dBgS_Chk mChk;
};

class dBgS_LinkLinChk : dBgS_LinChk {
public:
};

class dBgS_RopeLinChk : dBgS_LinChk {};

class dBgS_BoomerangLinChk : dBgS_LinChk {};

class dBgS_ArrowLinChk : dBgS_LinChk {
    /* 800781D8 */ dBgS_ArrowLinChk();
    /* 80078240 */ ~dBgS_ArrowLinChk();
};

class dBgS_ObjLinChk : dBgS_LinChk {
    /* 80077F5C */ dBgS_ObjLinChk();
    /* 80077FB8 */ ~dBgS_ObjLinChk();
};

#endif /* D_BG_D_BG_S_LIN_CHK_H */
