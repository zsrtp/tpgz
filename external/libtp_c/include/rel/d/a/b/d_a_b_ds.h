#ifndef D_A_B_DS_H_
#define D_A_B_DS_H_

#include "../../../../f_op/f_op_actor.h"

/*
 * Stallord
 * (members wip)
 */
class daB_DS_c : public fopAc_ac_c {
public:
    /* 0x0568 */ u8 field_0x568[0x118];
    /* 0x0680 */ int mActionMode1;
    /* 0x0684 */ int mActionMode2;
    /* 0x0688 */ u8 field_0x688[0x1D8];
    /* 0x0760 */ cXyz field_0x760[2];
    /* 0x0778 */ cXyz field_0x778[2];
    /* 0x0790 */ u8 field_0x790[0x58];
    /* 0x07E8 */ f32 field_0x7e8;  // related to eye color
    /* 0x07EC */ u8 field_0x7ec[0x67];
    /* 0x084F */ u8 field_0x84f;
    /* 0x0850 */ u8 field_0x850;
    /* 0x0850 */ u8 field_0x851;
    /* 0x0852 */ u8 field_0x852;
    /* 0x0853 */ u8 field_0x853;
    /* 0x0854 */ u8 field_0x854[2];
    /* 0x0856 */ u8 mParam1;
    /* 0x0857 */ u8 mParam2;
    /* 0x0858 */ u8 mParam3;
    /* 0x0859 */ u8 mParam4;
};

// setup later
struct daObjSwSpinner_c : public fopAc_ac_c {
    /* 0x568 */ u8 field_0x568[0x5B4 - 0x568];
    /* 0x5B4 */ Mtx mBgMtx;
    /* 0x5E4 */ f32 mHeight;
    /* 0x5E8 */ u8 field_0x5e8;
    /* 0x5E9 */ u8 field_0x5e9;
    /* 0x5EA */ u8 field_0x5ea;
    /* 0x5EB */ u8 field_0x5eb;
    /* 0x5EC */ s16 field_0x5ec;
    /* 0x5EE */ s16 mRotSpeedY;
    /* 0x5F0 */ s16 field_0x5f0;
};

struct daObjLv4Wall_c : public fopAc_ac_c {
    /* 0x568 */ u8 field_0x568[0x94C - 0x568];
    /* 0x94C */ daObjSwSpinner_c* mpSpinnerSw;
    /* 0x950 */ f32 mHeight;
    /* 0x954 */ int field_0x954;
    /* 0x958 */ u16 field_0x958;
    /* 0x95A */ u8 mAction;
};

#endif
