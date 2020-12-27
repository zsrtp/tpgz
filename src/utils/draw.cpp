#include "utils/draw.h"
#include "libtp_c/include/addrs.h"
#include "libtp_c/include/system.h"
#include "gcn_c/include/gfx.h"
#include "utils/texture.h"

#define DEFAULT_WIDTH 0x06

Texture blankTex;

namespace Draw {
void init() {
    load_texture("tpgz/tex/blank.tex", &blankTex);
    if (blankTex.loadCode != TexCode::TEX_OK) {
        tp_osReport("Could not load blank texture (Code: %d)", blankTex.loadCode);
    }
}

void begin(uint16_t n) {
    begin(n, GX_TRIANGLESTRIP);
}

void begin(uint16_t n, uint8_t primitive) {
    begin(n, primitive, &blankTex._texObj);
}

void begin(uint16_t n, GXTexObj* tex) {
    begin(n, GX_TRIANGLESTRIP, tex);
}

void begin(uint16_t n, uint8_t primitive, GXTexObj* tex) {
    GX_LoadTexObj(tex, (uint8_t)GX_TEXMAP0);
    GX_Begin(primitive, GX_VTXFMT0, n);
}

void begin_outline(uint16_t n) {
    begin_outline(n, DEFAULT_WIDTH);
}

void begin_outline(uint16_t n, uint8_t width) {
    GX_LoadTexObj(&blankTex._texObj, (uint8_t)GX_TEXMAP0);
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
    draw_quad(color, p, &blankTex._texObj);
}

void draw_quad(uint32_t color, Vec2 p[4], Vec2 tex[4]) {
    draw_quad(color, p, tex, &blankTex._texObj);
}

void draw_quad(uint32_t color, Vec2 p[4], GXTexObj* texture) {
    Vec2 tex[4] = {
        {0.0, 0.0},
        {1.0, 0.0},
        {1.0, 1.0},
        {0.0, 1.0},
    };
    draw_quad(color, p, tex, texture);
}

void draw_quad(uint32_t color, Vec2 p[4], Vec2 tex[4], GXTexObj* texture) {
    begin(4, texture);
    add_vertex(color, p[0], tex[0]);
    add_vertex(color, p[1], tex[1]);
    add_vertex(color, p[3], tex[3]);
    add_vertex(color, p[2], tex[2]);
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
    draw_rect(color, pos, dim, &blankTex._texObj);
}

void draw_rect(uint32_t color, Vec2 pos, Vec2 dim, GXTexObj* texture) {
    Vec2 tex[4] = {
        {0.0, 0.0},
        {1.0, 0.0},
        {1.0, 1.0},
        {0.0, 1.0},
    };
    draw_rect(color, pos, dim, tex, texture);
}

void draw_rect(uint32_t color, Vec2 pos, Vec2 dim, Vec2 tex[4]) {
    draw_rect(color, pos, dim, tex, &blankTex._texObj);
}

void draw_rect(uint32_t color, Vec2 pos, Vec2 dim, Vec2 tex[4], GXTexObj* texture) {
    Vec2 vertices[4] = {{pos.x, pos.y},
                        {pos.x + dim.x, pos.y},
                        {pos.x + dim.x, pos.y + dim.y},
                        {pos.x, pos.y + dim.y}};
    draw_quad(color, vertices, tex, texture);
}

void draw_rect_outline(uint32_t color, Vec2 pos, Vec2 dim) {
    draw_rect_outline(color, pos, dim, DEFAULT_WIDTH);
}

void draw_rect_outline(uint32_t color, Vec2 pos, Vec2 dim, uint8_t width) {
    Vec2 vertices[4] = {{pos.x, pos.y},
                        {pos.x + dim.x, pos.y},
                        {pos.x + dim.x, pos.y + dim.y},
                        {pos.x, pos.y + dim.y}};
    draw_quad_outline(color, vertices, width);
}

};  // namespace Draw
