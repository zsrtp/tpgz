#ifndef C_M3D_G_AAB_H
#define C_M3D_G_AAB_H

#include "c_xyz.h"

// Axis aligned bounding box
class cM3dGAab {
private:
public:
    cXyz mMin;
    cXyz mMax;

    virtual ~cM3dGAab();
    const cXyz& getMaxP(void) const { return mMax; }
    const cXyz& getMinP(void) const { return mMin; }
    const float GetMaxX(void) const { return mMax.GetX(); }
    const float GetMaxY(void) const { return mMax.GetY(); }
    const float GetMaxZ(void) const { return mMax.GetZ(); }
    const float GetMinX(void) const { return mMin.GetX(); }
    const float GetMinY(void) const { return mMin.GetY(); }
    const float GetMinZ(void) const { return mMin.GetZ(); }
};  // Size = 0x1C

#endif /* C_M3D_G_AAB_H */
