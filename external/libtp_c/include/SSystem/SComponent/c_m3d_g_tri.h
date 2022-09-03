#ifndef C_M3D_G_TRI_H_
#define C_M3D_G_TRI_H_

#include "c_m3d_g_pla.h"
#include "c_xyz.h"

class cM3dGTri {
    // private:
public:
    cM3dGPla mPlane;
    cXyz mA;
    cXyz mB;
    cXyz mC;
};

#endif