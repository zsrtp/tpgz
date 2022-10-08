#ifndef M_DO_M_DO_MTX_H
#define M_DO_M_DO_MTX_H

#include <stdint.h>
#include "../dolphin/mtx/mtx.h"
#include "../defines.h"

extern "C" void PSMTXConcat(const Mtx, const Mtx, Mtx);
extern "C" void PSMTXScale(Mtx, float, float, float);
extern "C" void PSMTXTrans(Mtx matrix, float x_trans, float y_trans, float z_trans);

#ifndef WII_PLATFORM
#define mDoMtx_stack_c__now now__14mDoMtx_stack_c
#endif
extern Mtx mDoMtx_stack_c__now;

LIBTP_DEFINE_FUNC(mDoMtx_XYZrotM__FPA4_fsss, mDoMtx_XYZrotM_float, void, mDoMtx_XYZrotM,
                  (Mtx, short, short, short))

LIBTP_DEFINE_FUNC(scaleM__14mDoMtx_stack_cFfff, mDoMtx_stack_c__scaleM_float_, void,
                  mDoMtx_stack_c__scaleM, (float, float, float))

class mDoMtx_stack_c {
public:
    static MtxP get() { return mDoMtx_stack_c__now; }
    static void transS(float x, float y, float z) { PSMTXTrans(mDoMtx_stack_c__now, x, y, z); }
    static void scaleS(float x, float y, float z) { PSMTXScale(mDoMtx_stack_c__now, x, y, z); }
    static void XYZrotM(short x, short y, short z) { mDoMtx_XYZrotM(mDoMtx_stack_c__now, x, y, z); }
    static void revConcat(MtxP mtx) { PSMTXConcat(mtx, mDoMtx_stack_c__now, mDoMtx_stack_c__now); }
};

#endif /* M_DO_M_DO_MTX_H */
