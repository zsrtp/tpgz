#ifndef C_M3D_G_AAB_H
#define C_M3D_G_AAB_H

#include "c_xyz.h"

// Axis aligned bounding box
class cM3dGAab {
public:
    cXyz mMin;
    cXyz mMax;
    void* vtable;

    const cXyz& getMaxP(void) const { return mMax; }
    const cXyz& getMinP(void) const { return mMin; }
    const f32 GetMaxX(void) const { return mMax.x; }
    const f32 GetMaxY(void) const { return mMax.y; }
    const f32 GetMaxZ(void) const { return mMax.z; }
    const f32 GetMinX(void) const { return mMin.x; }
    const f32 GetMinY(void) const { return mMin.y; }
    const f32 GetMinZ(void) const { return mMin.z; }
};  // Size = 0x1C

static_assert(sizeof(cM3dGAab) == 0x1C);

#endif /* C_M3D_G_AAB_H */
