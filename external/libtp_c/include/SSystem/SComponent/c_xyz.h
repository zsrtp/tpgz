#ifndef C_XYZ_H
#define C_XYZ_H

#include "../../dolphin/types.h"
#include "../../dolphin/mtx/vec.h"
#include "../../msl_c/math.h"

struct cXyz : Vec {
    ~cXyz() {}
    cXyz() {}
    cXyz(f32 x, f32 y, f32 z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    cXyz(const cXyz& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }
    cXyz(const Vec& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }
    void operator=(const Vec& vec) {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }
    void operator+=(f32 f) {
        x += f;
        y += f;
        z += f;
    }
    void operator-=(f32 f) {
        x -= f;
        y -= f;
        z -= f;
    }
    void operator+=(const Vec& vec) {
        x += vec.x;
        y += vec.y;
        z += vec.z;
    }
    void setAll(f32 f) {
        z = f;
        y = f;
        x = f;
    }
    void set(f32 pX, f32 pY, f32 pZ) {
        x = pX;
        y = pY;
        z = pZ;
    }
    void setMin(const cXyz& other) {
        if (x > other.x) {
            x = other.x;
        }
        if (y > other.y) {
            y = other.y;
        }
        if (z > other.z) {
            z = other.z;
        }
    }
    void setMax(const cXyz& other) {
        if (x < other.x) {
            x = other.x;
        }
        if (y < other.y) {
            y = other.y;
        }
        if (z < other.z) {
            z = other.z;
        }
    }

    float getSquareMag() const { return PSVECSquareMag(this); }
    f32 getSquareDistance(const Vec& other) const { return PSVECSquareDistance(this, &other); }

    f32 abs2() const { return this->getSquareMag(); }
    f32 abs2(const Vec& other) const { return this->getSquareDistance(other); }

    f32 abs() const { return (f32)sqrt(this->abs2()); }
    f32 abs(const Vec& other) const { return (f32)sqrt(this->abs2(other)); }
};

#endif /* C_XYZ_H */
