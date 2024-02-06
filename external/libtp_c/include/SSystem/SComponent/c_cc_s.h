#ifndef C_CC_S_H
#define C_CC_S_H

#include "c_cc_d.h"

class cCcS {
public:
    /* 0x0000 */ cCcD_Obj* mpObjAt[0x100];
    /* 0x0400 */ cCcD_Obj* mpObjTg[0x300];
    /* 0x1000 */ cCcD_Obj* mpObjCo[0x100];
    /* 0x1400 */ cCcD_Obj* mpObj[0x500];
    /* 0x2800 */ u16 mObjAtCount;
    /* 0x2802 */ u16 mObjTgCount;
    /* 0x2804 */ u16 mObjCoCount;
    /* 0x2806 */ u16 mObjCount;
    /* 0x2808 */ cCcD_DivideArea mDivideArea;
    /* 0x2848 */ void* vtable;
};  // Size = 0x284C

static_assert(sizeof(cCcS) == 0x284C);

#endif /* C_CC_S_H */
