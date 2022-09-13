#ifndef VEC_H
#define VEC_H

struct Vec {
    float x, y, z;
    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetZ() const { return z; }
    float getXDiff(const Vec* other) const { return x - other->x; }
    float getYDiff(const Vec* other) const { return y - other->y; }
    float getZDiff(const Vec* other) const { return z - other->z; }
};

struct Vec2 {
    float x, y;
};

struct CameraMatrix {
    Vec target;
    Vec pos;
};

#endif /* VEC_H */
