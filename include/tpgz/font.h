#pragma once
#include <string.h>
#include "libtp_c/include/addrs.h"
#include "gcn_c/include/gfx.h"

#define MAX_GLYPHS 94
struct _Glyph {
    float descender, minX, minY, maxX, maxY;
};

struct _Font {
   public:
    float width, height, size, spaceAdvance;
    _Glyph glyphs[MAX_GLYPHS];
    char* _start;
};

class PositionedGlyph {
   public:
    float vertices[4][2];
    float tex_coords[4][2];
    float next_x;
    void render(uint32_t color);
};

class DecodedGlyph {
   public:
    _Glyph* glyph;
    float width;
    float height;
    float advance_x;

    PositionedGlyph position(float _x, float _y);
};

class Font {
   private:
    const _Font* font;

   public:
    GXTexObj _texobj;
    Font();
    Font(const _Font& font);
    Font(const _Font& _font, const char* data);
    bool lookupGlyph(char c, DecodedGlyph& glyph);
    float renderChar(char c, float x, float y, uint32_t color);
    void renderChars(const char* str, float x, float y, uint32_t color);
    void setupRendering();
};