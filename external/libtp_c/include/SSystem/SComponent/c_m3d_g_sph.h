#ifndef C_M3D_G_SPH_H_
#define C_M3D_G_SPH_H_

#include "c_m3d_g_cyl.h"
#include "c_xyz.h"

struct cM3dGSphS {
    Vec mCenter;
    float mRadius;
};

class cM3dGSph {
private:
public:
    cXyz mCenter;
    float mRadius;

    virtual ~cM3dGSph();
    const cXyz& GetC(void) const { return mCenter; }
    const float GetR(void) const { return mRadius; }
    float GetCX(void) const { return mCenter.GetX(); }
    float GetCY(void) const { return mCenter.GetY(); }
    float GetCZ(void) const { return mCenter.GetZ(); }
};

#endif