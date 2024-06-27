#ifndef JPAPARTICLE_H
#define JPAPARTICLE_H

#include "../../dolphin/types.h"
#include "../../dolphin/gx/gx.h"

class JPABaseParticle;

struct JPABaseEmitter {};

class JPAParticleCallBack {
public:
    virtual void draw(JPABaseEmitter*, JPABaseParticle*);
};

#endif /* JPAPARTICLE_H */
