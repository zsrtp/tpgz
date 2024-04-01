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

extern "C" f32 PSVECSquareMag(const Vec* v);
extern "C" f32 PSVECSquareDistance(const Vec* a, const Vec* b);
extern "C" void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
extern "C" void PSVECScale(const Vec* src, Vec* dst, f32 scale);

#endif /* VEC_H */
