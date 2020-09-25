#include "utils/draw.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/addrs.h"
#include "gcn_c/include/gfx.h"

#define DEFAULT_WIDTH 0x06

GXTexObj _blankTexObj;
const char _blank_tex_data[1] __attribute__ ((aligned (32))) = {0xff};

namespace Draw {
    void init() {
        tp_memset(&_blankTexObj, 0x0, sizeof(GXTexObj));
        GX_InitTexObj(&_blankTexObj, (void*)_blank_tex_data, 1, 1, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    }

    void begin(uint16_t n) {
        begin(n, GX_TRIANGLESTRIP);
    }

    void begin(uint16_t n, uint8_t primitive) {
        GX_LoadTexObj(&_blankTexObj, (uint8_t)GX_TEXMAP0);
        GX_Begin(primitive, GX_VTXFMT0, n);
    }

    void begin_outline(uint16_t n) {
        begin_outline(n, DEFAULT_WIDTH);
    }

    void begin_outline(uint16_t n, uint8_t width) {
        GX_LoadTexObj(&_blankTexObj, (uint8_t)GX_TEXMAP0);
        GX_SetLineWidth(width, GX_TO_ZERO);
        GX_Begin(GX_LINESTRIP, GX_VTXFMT0, n);
    }

    void add_vertex(uint32_t color, Vec2 point, Vec2 tex) {
        GX_Position2f32(point.x, point.y);
        GX_Color1u32(color);
        GX_TexCoord2f32(tex.x, tex.y);
    }

    void add_vertex(uint32_t color, Vec2 point) {
        add_vertex(color, point, {0.0f, 0.0f});
    }

    void end() {
        GX_End();
    }

    void draw_quad(uint32_t color, Vec2 p[4]) {
        begin(4);
            add_vertex(color, p[0], {0.0, 0.0});
            add_vertex(color, p[1], {1.0, 0.0});
            add_vertex(color, p[3], {0.0, 1.0});
            add_vertex(color, p[2], {1.0, 1.0});
        end();
    }

    void draw_quad_outline(uint32_t color, Vec2 p[4]) {
        draw_quad_outline(color, p, DEFAULT_WIDTH);
    }

    void draw_quad_outline(uint32_t color, Vec2 p[4], uint8_t width) {
        begin_outline(5, width);
            add_vertex(color, p[0], {0.0, 0.0});
            add_vertex(color, p[1], {1.0, 0.0});
            add_vertex(color, p[2], {1.0, 1.0});
            add_vertex(color, p[3], {0.0, 1.0});
            add_vertex(color, p[0], {0.0, 0.0});
        end();
    }

    void draw_rect(uint32_t color, Vec2 pos, Vec2 dim) {
        Vec2 vertices[4] = {
            {pos.x, pos.y},
            {pos.x + dim.x, pos.y},
            {pos.x + dim.x, pos.y + dim.y},
            {pos.x, pos.y + dim.y}};
        draw_quad(color, vertices);
    }

    void draw_rect_outline(uint32_t color, Vec2 pos, Vec2 dim) {
        draw_rect_outline(color, pos, dim, DEFAULT_WIDTH);
    }

    void draw_rect_outline(uint32_t color, Vec2 pos, Vec2 dim, uint8_t width) {
        Vec2 vertices[4] = {
            {pos.x, pos.y},
            {pos.x + dim.x, pos.y},
            {pos.x + dim.x, pos.y + dim.y},
            {pos.x, pos.y + dim.y}};
        draw_quad_outline(color, vertices, width);
    }


}; // namespace Draw
