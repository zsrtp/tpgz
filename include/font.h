#pragma once

#include "libtp_c/include/utils.h"
#include "libtp_c/include/addrs.h"
#include "utils/texture.h"
#include "gcn_c/include/gfx.h"

#define MAX_GLYPHS 94
#define DROP_SHADOWS_RGBA 0x000000FF
#define FONT_DEFAULT_SIZE 17.f

enum FontCode {
    FNT_OK = 1,           /*<@brief Font loaded successfully */
    FNT_UNLOADED = 0,     /*<@brief Font hasn't been loaded yet */
    FNT_ERR_FILE = -1,    /*<@brief Could not open font file */
    FNT_ERR_READ = -2,    /*<@brief Error occured while reading the font file */
    FNT_ERR_TEXTURE = -3, /*<@brief Error occured while reading the texture from the file */
    FNT_ERR_MEM = -4,     /*<@brief Not enough memory to load the font */
};

struct _Metrics {
    float ascender, descender;
};

struct _Glyph {
    float offset, width, minX, minY, maxX, maxY;
};

struct _FontHeader {
    char magic[0x4];
    float base_size;  // in points
    _Metrics metrics;
    uint32_t glyph_count;
};

struct _Font {
    _FontHeader header;
    _Glyph* glyphs;
    Texture texture;
    FontCode loadCode;
};

class PositionedGlyph {
public:
    Vec2 vertices[4];
    Vec2 tex_coords[4];
    float next_x;
    void render(uint32_t color, Texture* texture);
};

class DecodedGlyph {
public:
    _Glyph* glyph;
    float width;
    float offset;
    _Metrics metrics;

    PositionedGlyph position(float _x, float _y, float size);
};

class Font {
private:
    static _Font font;

public:
    static FontCode load_font(const char* path);
    static void free_font();
    static bool lookupGlyph(char c, DecodedGlyph& glyph);
    static float renderChar(char c, float x, float y, uint32_t color,
                            float size = FONT_DEFAULT_SIZE);
    static void renderChars(const char* str, float x, float y, uint32_t color,
                            float size = FONT_DEFAULT_SIZE);
    static void gz_renderChar(char c, float x, float y, uint32_t color, bool drop_shawdows,
                              float size = FONT_DEFAULT_SIZE);
    static void gz_renderChars(const char* str, float x, float y, uint32_t color, bool drop_shadows,
                               float size = FONT_DEFAULT_SIZE);
    static float get_char_width(char c, float size = FONT_DEFAULT_SIZE);
    static float get_chars_width(const char* str, float size = FONT_DEFAULT_SIZE);
};