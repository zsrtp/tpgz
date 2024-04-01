#ifndef M_DO_M_DO_MTX_H
#define M_DO_M_DO_MTX_H

#include "../dolphin/types.h"
#include "../dolphin/mtx/mtx.h"
#include "../defines.h"

extern "C" {
void PSMTXConcat(const Mtx, const Mtx, Mtx);
void PSMTXScale(Mtx, f32, f32, f32);
void PSMTXTrans(Mtx matrix, f32 x_trans, f32 y_trans, f32 z_trans);
void PSMTXCopy(const Mtx src, Mtx dst);
}

#ifndef WII_PLATFORM
#define mDoMtx_stack_c__now now__14mDoMtx_stack_c
#endif
extern Mtx mDoMtx_stack_c__now;

LIBTP_DEFINE_FUNC(mDoMtx_XYZrotM__FPA4_fsss, mDoMtx_XYZrotM_float,
                  void, mDoMtx_XYZrotM, (Mtx, short, short, short))

LIBTP_DEFINE_FUNC(scaleM__14mDoMtx_stack_cFfff, mDoMtx_stack_c__scaleM_float_,
                  void, mDoMtx_stack_c__scaleM, (f32, f32, f32))

LIBTP_DEFINE_FUNC(transM__14mDoMtx_stack_cFfff, mDoMtx_stack_c__transM_float__float__float_,
                  void, mDoMtx_stack_c__transM, (f32, f32, f32))

LIBTP_DEFINE_FUNC(mDoMtx_inverseTranspose__FPA4_CfPA4_f, mDoMtx_inverseTranspose_float_const_____4___float_____4__,
                  bool, mDoMtx_inverseTranspose, (const Mtx, Mtx))

LIBTP_DEFINE_FUNC(mDoMtx_XrotM__FPA4_fs, mDoMtx_XrotM_float_____4___short_,
                  void, mDoMtx_XrotM, (Mtx, s16))

class mDoMtx_stack_c {
public:
    static MtxP get() { return mDoMtx_stack_c__now; }
    static void transS(f32 x, f32 y, f32 z) { PSMTXTrans(mDoMtx_stack_c__now, x, y, z); }
    static void scaleS(f32 x, f32 y, f32 z) { PSMTXScale(mDoMtx_stack_c__now, x, y, z); }
    static void XYZrotM(short x, short y, short z) { mDoMtx_XYZrotM(mDoMtx_stack_c__now, x, y, z); }
    static void revConcat(MtxP mtx) { PSMTXConcat(mtx, mDoMtx_stack_c__now, mDoMtx_stack_c__now); }
    static void scaleM(f32 x, f32 y, f32 z) { mDoMtx_stack_c__scaleM(x, y, z); }
    static void copy(const Mtx m) { PSMTXCopy(m, mDoMtx_stack_c__now); }
    static void transM(f32 x, f32 y, f32 z) { mDoMtx_stack_c__transM(x, y, z); }
    static void inverseTranspose() { mDoMtx_inverseTranspose(mDoMtx_stack_c__now, mDoMtx_stack_c__now); }
    static void XrotM(s16 x) { mDoMtx_XrotM(mDoMtx_stack_c__now, x); }
};

#endif /* M_DO_M_DO_MTX_H */
