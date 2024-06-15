#pragma once

#include "libtp_c/include/dolphin/gx/gx.h"
#include "libtp_c/include/dolphin/mtx/vec.h"
#include "utils/texture.h"

extern Texture blankTex;

namespace Draw {
void init();

// Basic functions
void begin(uint16_t n);
void begin(uint16_t n, uint8_t primitive);
void begin(uint16_t n, GXTexObj* tex);
void begin(uint16_t n, uint8_t primitive, GXTexObj* tex);
void begin_outline(uint16_t n);
void begin_outline(uint16_t n, uint8_t width);
void add_vertex(uint32_t color, Vec2 point);
void add_vertex(uint32_t color, Vec2 point, Vec2 tex);
void end();

void drawQuad(uint32_t color, Vec2 p[4]);
void drawQuad(uint32_t color, Vec2 p[4], GXTexObj* texture);
void drawQuad(uint32_t color, Vec2 p[4], Vec2 tex[4]);
void drawQuad(uint32_t color, Vec2 p[4], Vec2 tex[4], GXTexObj* texture);
void drawQuadOutline(uint32_t color, Vec2 p[4]);
void drawQuadOutline(uint32_t color, Vec2 p[4], uint8_t width);
void drawRect(uint32_t color, Vec2 pos, Vec2 dim);
void drawRect(uint32_t color, Vec2 pos, Vec2 dim, GXTexObj* texture);
void drawRect(uint32_t color, Vec2 pos, Vec2 dim, Vec2 tex[4]);
void drawRect(uint32_t color, Vec2 pos, Vec2 dim, Vec2 tex[4], GXTexObj* texture);
void drawRectOutline(uint32_t color, Vec2 pos, Vec2 dim);
void drawRectOutline(uint32_t color, Vec2 pos, Vec2 dim, uint8_t width);
};  // namespace Draw
