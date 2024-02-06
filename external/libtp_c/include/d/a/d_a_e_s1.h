#ifndef D_A_E_S1_H
#define D_A_E_S1_H

#include "../../f_op/f_op_actor_mng.h"
#include "../cc/d_cc_d.h"

struct e_s1_class : public fopEn_enemy_c {
    /* 0x5AC */ u8 field_0x5ac[0x698 - 0x5AC];
    /* 0x698 */ s16 mAction;
};

#endif /* D_A_E_S1_H */