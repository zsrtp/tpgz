#ifndef C_M3D_G_CPS_H
#define C_M3D_G_CPS_H

#include "c_m3d_g_lin.h"
#include "c_xyz.h"

struct cM3dGCpsS {
    Vec mStart;
    Vec mEnd;
    f32 mRadius;
};

class cM3dGCps : public cM3dGLin {
public:
    f32 mRadius;

    f32 GetR() const { return mRadius; }
};

static_assert(0x20 == sizeof(cM3dGCps));

#endif /* C_M3D_G_CPS_H */
