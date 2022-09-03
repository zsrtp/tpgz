#ifndef C_SXYZ_H
#define C_SXYZ_H

#include <stdint.h>

struct SVec {
    int16_t mX, mY, mZ;
};

class csXyz : public SVec {
public:
    /* 80018BD0 */ ~csXyz() {}
    /* inline   */ csXyz() {}
    /* inline   */ csXyz(const csXyz& other) : SVec(other){};
    /* 802673F4 */ csXyz(int16_t x, int16_t y, int16_t z) {
        mX = x;
        mY = y;
        mZ = z;
    }
    /* 80267404 */ csXyz operator+(csXyz&);
    /* 8026745C */ void operator+=(csXyz&);
    /* 80267490 */ csXyz operator-(csXyz&);
    /* 802674E8 */ csXyz operator*(float);
};

#endif /* C_SXYZ_H */
