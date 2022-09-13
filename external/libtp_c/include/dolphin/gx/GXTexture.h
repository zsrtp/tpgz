#ifndef GXTEXTURE_H
#define GXTEXTURE_H

#include <stdint.h>

struct _GXColor {
    void operator=(const _GXColor& rhs) {
        r = rhs.r;
        g = rhs.g;
        b = rhs.b;
        a = rhs.a;
    }

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct _GXColorS10 {
    int16_t r;
    int16_t g;
    int16_t b;
    int16_t a;
};

#endif /* GXTEXTURE_H */
