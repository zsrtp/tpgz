#ifndef C_M3D_G_CYL_H
#define C_M3D_G_CYL_H

#include "c_xyz.h"

// Cylinder
struct cM3dGCylS {
    cXyz mCenter;
    float mRadius;
    float mHeight;
};
class cM3dGSph;

class cM3dGCyl : public cM3dGCylS {
public:
    virtual ~cM3dGCyl();
    const cXyz& GetCP(void) const { return mCenter; }
    float GetR(void) const { return mRadius; }
    float GetH(void) const { return mHeight; }
};

#endif /* C_M3D_G_CYL_H */
