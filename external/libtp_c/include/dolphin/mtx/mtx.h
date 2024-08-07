#ifndef MTX_H
#define MTX_H

#include "../types.h"
#include "vec.h"

typedef f32 Mtx[3][4];
typedef f32 Mtx33[3][3];
typedef f32 Mtx23[2][3];
typedef f32 Mtx44[4][4];
typedef f32 (*MtxP)[4];

extern "C" {
void PSMTXIdentity(Mtx m);
void PSMTXTrans(Mtx m, f32 x, f32 y, f32 z);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXScale(Mtx m, f32 x, f32 y, f32 z);
void PSMTXCopy(const Mtx src, Mtx dst);
u32 PSMTXInverse(const Mtx src, Mtx inv);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXMultVecSR(const Mtx m, const Vec* src, Vec* dst);
void PSMTXMultVecArray(const Mtx m, const Vec* srcBase, Vec* dstBase, u32 count);
void PSMTXMultVecArraySR(const Mtx m, const Vec* srcBase, Vec* dstBase, u32 count);
}

#endif /* MTX_H */
