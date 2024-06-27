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
    void* vtable;

    void CalcVec(Vec* pOut) const { PSVECSubtract(&this->mEnd, &this->mStart, pOut); }

    const cXyz& GetStartP(void) const { return mStart; }
    cXyz& GetStartP(void) { return mStart; }
    const cXyz& GetEndP(void) const { return mEnd; }
    cXyz& GetEndP(void) { return mEnd; }
    f32 GetLen() const { return PSVECDistance(&mStart, &mEnd); }
};

static_assert(0x1C == sizeof(cM3dGLin));

#endif /* C_M3D_G_LIN_H */
