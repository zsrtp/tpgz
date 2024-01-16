#ifndef C_M3C_G_PLA_H_
#define C_M3C_G_PLA_H_

#include "c_xyz.h"

// Plane with a normal
class cM3dGPla {
public:
    cXyz mNormal;
    f32 mD;
    cM3dGPla();
    cM3dGPla(const cXyz*, f32);
    virtual ~cM3dGPla();

    const cXyz& GetNP() const { return mNormal; }
    f32 GetD() const { return mD; }
};

#endif