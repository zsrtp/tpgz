#ifndef M_DO_M_DO_MTX_H
#define M_DO_M_DO_MTX_H

#include "../dolphin/types.h"
#include "../dolphin/mtx/mtx.h"
#include "../defines.h"

extern "C" void PSMTXConcat(const Mtx, const Mtx, Mtx);
extern "C" void PSMTXScale(Mtx, f32, f32, f32);
extern "C" void PSMTXTrans(Mtx matrix, f32 x_trans, f32 y_trans, f32 z_trans);

#ifndef WII_PLATFORM
#define mDoMtx_stack_c__now now__14mDoMtx_stack_c
#endif
extern Mtx mDoMtx_stack_c__now;

LIBTP_DEFINE_FUNC(mDoMtx_XYZrotM__FPA4_fsss, mDoMtx_XYZrotM_float,
                  void, mDoMtx_XYZrotM, (Mtx, short, short, short))

LIBTP_DEFINE_FUNC(scaleM__14mDoMtx_stack_cFfff, mDoMtx_stack_c__scaleM_float_,
                  void, mDoMtx_stack_c__scaleM, (f32, f32, f32))

class mDoMtx_stack_c {
public:
    static MtxP get() { return mDoMtx_stack_c__now; }
    static void transS(f32 x, f32 y, f32 z) { PSMTXTrans(mDoMtx_stack_c__now, x, y, z); }
    static void scaleS(f32 x, f32 y, f32 z) { PSMTXScale(mDoMtx_stack_c__now, x, y, z); }
    static void XYZrotM(short x, short y, short z) { mDoMtx_XYZrotM(mDoMtx_stack_c__now, x, y, z); }
    static void revConcat(MtxP mtx) { PSMTXConcat(mtx, mDoMtx_stack_c__now, mDoMtx_stack_c__now); }
};

#endif /* M_DO_M_DO_MTX_H */
