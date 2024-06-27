#ifndef VEC_H
#define VEC_H

#include "../types.h"

struct Vec {
    f32 x, y, z;
};

struct Vec2 {
    f32 x, y;
};

struct CameraMatrix {
    Vec target;
    Vec pos;
};

extern "C" {
f32 PSVECSquareMag(const Vec* v);
f32 PSVECSquareDistance(const Vec* a, const Vec* b);
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void PSVECNormalize(const Vec* src, Vec* unit);
void PSVECCrossProduct(const Vec* a, const Vec* b, Vec* axb);
f32 PSVECMag(const Vec* v);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
f32 PSVECDistance(const Vec* a, const Vec* b);
}

#endif /* VEC_H */
