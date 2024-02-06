#ifndef C_M3D_G_SPH_H_
#define C_M3D_G_SPH_H_

#include "c_m3d_g_cyl.h"
#include "c_xyz.h"

struct cM3dGSphS {
    Vec mCenter;
    f32 mRadius;
};

class cM3dGSph {
private:
public:
    cXyz mCenter;
    f32 mRadius;

    virtual ~cM3dGSph();
    const cXyz& GetC(void) const { return mCenter; }
    const f32 GetR(void) const { return mRadius; }
    f32 GetCX(void) const { return mCenter.x; }
    f32 GetCY(void) const { return mCenter.y; }
    f32 GetCZ(void) const { return mCenter.z; }
};

#endif