#ifndef D_PARTICLE_D_PARTICLE_H
#define D_PARTICLE_D_PARTICLE_H

#include "../../JSystem/JParticle/JPAParticle.h"
#include "../../f_op/f_op_actor.h"

class JPAEmitterCallBack {
public:
};

class dPa_levelEcallBack : public JPAEmitterCallBack {
public:
};

class dPa_hermiteEcallBack_c : public dPa_levelEcallBack {
public:
    /* 0x00 */ void* vtable;
    /* 0x04 */ f32 mRate;
    /* 0x08 */ int mMaxCnt;
    /* 0x0C */ cXyz* field_0xc;
    /* 0x10 */ cXyz* field_0x10;
    /* 0x14 */ cXyz* field_0x14;
};

#endif /* D_PARTICLE_D_PARTICLE_H */
