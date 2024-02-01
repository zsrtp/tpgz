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

#endif
