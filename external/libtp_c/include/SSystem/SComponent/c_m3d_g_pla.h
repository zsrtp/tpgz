#ifndef C_M3C_G_PLA_H_
#define C_M3C_G_PLA_H_

#include "c_xyz.h"

// Plane with a normal
class cM3dGPla {
public:
    cXyz mNormal;
    float mD;
    cM3dGPla();
    cM3dGPla(const cXyz*, float);
    virtual ~cM3dGPla();

    const cXyz& GetNP() const { return mNormal; }
    float GetD() const { return mD; }
};

#endif