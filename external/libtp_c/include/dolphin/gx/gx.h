#pragma once

#include <stdint.h>
#include "../mtx/mtx.h"
#include "gcn_c/include/gfx.h"

extern "C" {
#define GFX_FIFO(T) (*(volatile T*)0xCC008000)

inline void GXPosition3float(f32 x, f32 y, f32 z) {
    GFX_FIFO(f32) = x;
    GFX_FIFO(f32) = y;
    GFX_FIFO(f32) = z;
}

inline void GXColor1uint32_t(u32 c) {
    GFX_FIFO(u32) = c;
}

inline void GXTexCoord2float(f32 s, f32 t) {
    GFX_FIFO(f32) = s;
    GFX_FIFO(f32) = t;
}

inline void GXTexCoord2uint8_t(u8 s, u8 t) {
    GFX_FIFO(u8) = s;
    GFX_FIFO(u8) = t;
}

inline void GXPosition2uint16_t(u16 x, u16 y) {
    GFX_FIFO(u16) = x;
    GFX_FIFO(u16) = y;
}

inline void GXPosition1x8(u8 x) {
    GFX_FIFO(u8) = x;
}

inline void GXEnd() {}
};