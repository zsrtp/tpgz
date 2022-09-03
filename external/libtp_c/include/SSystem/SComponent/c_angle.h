#ifndef C_ANGLE_H
#define C_ANGLE_H

#include "c_xyz.h"
#include <stdint.h>

class cSAngle {
public:
    int16_t mAngle;

    int16_t Val() const { return this->mAngle; }
    bool operator<(const cSAngle& other) const { return mAngle < other.mAngle; }
    bool operator>(const cSAngle& other) const { return mAngle > other.mAngle; }
    operator int16_t(void) const { return mAngle; }
    void operator=(const cSAngle& other) { mAngle = other.mAngle; }
};

class cDegree {
public:
    float mDegree;
};

class cSPolar {
public:
    float mRadial;
    cSAngle mAngle1;
    cSAngle mAngle2;
};

class cSGlobe {
public:
    float mRadius;
    cSAngle mAzimuth;      // original: V
    cSAngle mInclination;  // original: U

    float R(void) const { return mRadius; }
    const cSAngle& V(void) const { return mAzimuth; }
    const cSAngle& U(void) const { return mInclination; }
};

#endif /* C_ANGLE_H */
