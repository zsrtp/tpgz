#pragma once

#include "libtp_c/include/utils.h"
#include "libtp_c/include/addrs.h"
#include "gcn_c/include/gfx.h"

extern GXTexObj _blankTexObj;
extern const char _blank_tex_data[1];

namespace Draw {
    void init();

    // Basic functions
    void begin(uint16_t n);
    void begin(uint16_t n, uint8_t primitive);
    void begin_outline(uint16_t n);
    void begin_outline(uint16_t n, uint8_t width);
    void add_vertex(uint32_t color, Vec2 point);
    void add_vertex(uint32_t color, Vec2 point, Vec2 tex);
    void end();

    void draw_quad(uint32_t color, Vec2 p[4]);
    void draw_quad_outline(uint32_t color, Vec2 p[4]);
    void draw_quad_outline(uint32_t color, Vec2 p[4], uint8_t width);
    void draw_rect(uint32_t color, Vec2 pos, Vec2 dim);
    void draw_rect_outline(uint32_t color, Vec2 pos, Vec2 dim);
    void draw_rect_outline(uint32_t color, Vec2 pos, Vec2 dim, uint8_t width);
}; // namespace Draw
