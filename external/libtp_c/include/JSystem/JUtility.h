#ifndef JUTILITY_H
#define JUTILITY_H

#include "../dolphin/gx/GXTexture.h"

namespace JUtility {

struct TColor : _GXColor {
    TColor() { set(-1); }

    TColor(uint32_t raw) { *(uint32_t*)&r = raw; }

    void set(uint32_t col) { *(uint32_t*)&r = col; }
    void set(uint8_t oR, uint8_t oG, uint8_t oB, uint8_t oA) {
        r = oR;
        g = oG;
        b = oB;
        a = oA;
    }

    uint32_t toUInt32() const { return *(uint32_t*)&r; }

    operator uint32_t() const { return toUInt32(); }
    void operator=(const TColor& rhs) { ((_GXColor*)this)->operator=(rhs); }
};

}  // namespace JUtility

#endif /* JUTILITY_H */