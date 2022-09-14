#ifndef D_CC_D_CC_S_H
#define D_CC_D_CC_S_H

#include "../../SSystem/SComponent/c_cc_s.h"
#include "d_cc_d.h"
#include "d_cc_mass_s.h"

class dCcS : public cCcS {
public:
    /* 0x284C */ dCcMassS_Mng mMass_Mng;
};  // Size = 0x2AC4

static_assert(sizeof(dCcS) == 0x2AC4);

#endif /* D_CC_D_CC_S_H */
