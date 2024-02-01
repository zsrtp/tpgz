#ifndef D_A_E_ZS_H
#define D_A_E_ZS_H

#include "../../f_op/f_op_actor_mng.h"
#include "../cc/d_cc_d.h"

struct daE_ZS_c : public fopEn_enemy_c {
    /* 0x5AC */ u8 field_0x5ac[0x660 - 0x5AC];
    /* 0x660 */ int mAction;
    /* 0x664 */ int mMode;
    /* 0x668 */ u8 field_0x668[0x8C8 - 0x668];
    /* 0x8C8 */ dCcD_Cyl mCyl;
};

#endif /* D_A_E_ZS_H */