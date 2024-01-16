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

#endif /* VEC_H */
