#ifndef C_ANGLE_H
#define C_ANGLE_H

#include "c_xyz.h"
#include "../../dolphin/types.h"

class cSAngle {
public:
    s16 mAngle;

    s16 Val() const { return this->mAngle; }
    bool operator<(const cSAngle& other) const { return mAngle < other.mAngle; }
    bool operator>(const cSAngle& other) const { return mAngle > other.mAngle; }
    operator s16(void) const { return mAngle; }
    void operator=(const cSAngle& other) { mAngle = other.mAngle; }
};

class cDegree {
public:
    f32 mDegree;
};

class cSPolar {
public:
    f32 mRadial;
    cSAngle mAngle1;
    cSAngle mAngle2;
};

class cSGlobe {
public:
    f32 mRadius;
    cSAngle mAzimuth;      // original: V
    cSAngle mInclination;  // original: U

    f32 R(void) const { return mRadius; }
    const cSAngle& V(void) const { return mAzimuth; }
    const cSAngle& U(void) const { return mInclination; }
};

#endif /* C_ANGLE_H */
