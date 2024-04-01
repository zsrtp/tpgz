#ifndef C_M3D_G_CYL_H
#define C_M3D_G_CYL_H

#include "c_xyz.h"

// Cylinder
struct cM3dGCylS {
    cXyz mCenter;
    f32 mRadius;
    f32 mHeight;
};
class cM3dGSph;

class cM3dGCyl : public cM3dGCylS {
public:
    void* vtable;
    const cXyz& GetCP(void) const { return mCenter; }
    f32 GetR(void) const { return mRadius; }
    f32 GetH(void) const { return mHeight; }
};

#endif /* C_M3D_G_CYL_H */
