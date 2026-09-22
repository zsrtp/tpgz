#ifndef D_A_E_ZS_H
#define D_A_E_ZS_H

#include "../../f_op/f_op_actor_mng.h"
#include "../cc/d_cc_d.h"

struct daE_ZS_c : public fopEn_enemy_c {
    /* 0x5AC */ u8 field_0x5ac[0x65C - 0x5AC];
    /* 0x65C */ f32 field_0x65c;
    /* 0x660 */ int mAction;
    /* 0x664 */ int mMode;
    /* 0x668 */ int mResIndex;
    /* 0x66c */ u32 mShadowKey;
    /* 0x670 */ u8 field_0x670;
    /* 0x671 */ u8 field_0x671;
    /* 0x672 */ u8 field_0x672;
    /* 0x673 */ u8 field_0x673;
    /* 0x668 */ u8 field_0x668[0x8C8 - 0x674];
    /* 0x8C8 */ dCcD_Cyl mCyl;
};

LIBTP_DEFINE_FUNC(setBck__8daE_ZS_cFiUcff, daE_ZS_c__setBck_int__unsigned_char__float__float_, void, daE_ZS_c__setBck_void_, (daE_ZS_c*, s32, u8, f32, f32))

#endif /* D_A_E_ZS_H */