#ifndef C_M3D_G_LIN_H
#define C_M3D_G_LIN_H

#include "c_xyz.h"
#include "../../dolphin/mtx/vec.h"

// Line
class cM3dGLin {
    // private:
public:
    cXyz mStart;
    cXyz mEnd;

    virtual ~cM3dGLin() {}
    const cXyz& GetStartP(void) const { return mStart; }
    cXyz& GetStartP(void) { return mStart; }
    const cXyz& GetEndP(void) const { return mEnd; }
    cXyz& GetEndP(void) { return mEnd; }
};

#endif /* C_M3D_G_LIN_H */
