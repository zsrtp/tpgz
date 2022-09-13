#pragma once

#include <stdint.h>
#include "../mtx/mtx.h"
#include "gcn_c/include/gfx.h"

extern "C" {
#define GFX_FIFO(T) (*(volatile T*)0xCC008000)

inline void GXPosition3float(float x, float y, float z) {
    GFX_FIFO(float) = x;
    GFX_FIFO(float) = y;
    GFX_FIFO(float) = z;
}

inline void GXColor1uint32_t(uint32_t c) {
    GFX_FIFO(uint32_t) = c;
}

inline void GXTexCoord2float(float s, float t) {
    GFX_FIFO(float) = s;
    GFX_FIFO(float) = t;
}

inline void GXTexCoord2uint8_t(uint8_t s, uint8_t t) {
    GFX_FIFO(uint8_t) = s;
    GFX_FIFO(uint8_t) = t;
}

inline void GXPosition2uint16_t(uint16_t x, uint16_t y) {
    GFX_FIFO(uint16_t) = x;
    GFX_FIFO(uint16_t) = y;
}

inline void GXPosition1x8(uint8_t x) {
    GFX_FIFO(uint8_t) = x;
}

inline void GXEnd() {}
};