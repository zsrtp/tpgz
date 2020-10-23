#include "libtp_c/include/system.h"
#include "font.h"
#include "utils/draw.h"
#include "utils/disc.h"

_Font Font::font;

FontCode Font::load_font(const char* path) {
    DVDFileInfo fileInfo;
    int32_t readsize;
    if (font.loadCode == FontCode::FNT_OK) {
        free_font();
    }

    if(!DVDOpen(path, &fileInfo)) {
        font.loadCode = FontCode::FNT_ERR_FILE;
        return font.loadCode;
    }
    readsize = dvd_read(&fileInfo, &font.header, sizeof(_FontHeader), 0);
    if (readsize < (int32_t)sizeof(_FontHeader)) {
        DVDClose(&fileInfo);
        font.loadCode = FontCode::FNT_ERR_READ;
        return font.loadCode;
    }

    uint32_t size = font.header.glyph_count * sizeof(_Glyph);
    font.glyphs = (_Glyph*)tp_memalign(-32, size);
    if (font.glyphs == nullptr) {
        DVDClose(&fileInfo);
        font.loadCode = FontCode::FNT_ERR_MEM;
        return font.loadCode;
    }

    if (DVDReadPrio(&fileInfo, font.glyphs, size, sizeof(font.header), 2) < (int32_t)size) {
        tp_free(font.glyphs);
        DVDClose(&fileInfo);
        font.loadCode = FontCode::FNT_ERR_READ;
        return font.loadCode;
    }

    if (load_texture_offset(path, &font.texture, sizeof(font.header) + size) != TexCode::TEX_OK) {
        tp_free(font.glyphs);
        DVDClose(&fileInfo);
        font.loadCode = FontCode::FNT_ERR_TEXTURE;
        return font.loadCode;
    }
    DVDClose(&fileInfo);

    font.loadCode = FontCode::FNT_OK;
    return font.loadCode;
}

void Font::free_font() {
    if (font.glyphs != nullptr) {
        tp_free(font.glyphs);
        font.glyphs = 0;
    }
    free_texture(&font.texture);
    tp_memset(&font, 0, sizeof(_Font));
    // The next line is redundant, but is still there for good measure
    font.loadCode = FontCode::FNT_UNLOADED;
}

void PositionedGlyph::render(uint32_t color, Texture* texture) {
    Draw::draw_quad(color, vertices, tex_coords, &texture->_texObj);
}

PositionedGlyph DecodedGlyph::position(float _x, float _y, float factor) {
    float vty = _y - metrics.ascender * factor;
    float vby = _y + metrics.descender * factor;
    float vrx = _x + (width + offset) * factor;
    float vlx = _x + offset * factor;

    float tty = glyph->minY;
    float tby = glyph->maxY;
    float trx = glyph->maxX;
    float tlx = glyph->minX;

    return {
        {{vlx, vty}, {vrx, vty}, {vrx, vby}, {vlx, vby}},
        {{tlx, tty}, {trx, tty}, {trx, tby}, {tlx, tby}},
        (_x + width * factor)};
}

bool Font::lookupGlyph(char c, DecodedGlyph& glyph) {
    uint8_t idx = c;
    if (idx < 0 || idx >= font.header.glyph_count) {
        return false;
    }
    glyph.glyph = &font.glyphs[idx];
    glyph.width = font.glyphs[idx].width;
    glyph.offset = font.glyphs[idx].offset;
    glyph.metrics = font.header.metrics;
    return true;
}

float Font::renderChar(char c, float x, float y, uint32_t color, float size) {
    DecodedGlyph glyph;
    if (lookupGlyph(c, glyph)) {
        auto positioned = glyph.position(x, y, size / font.header.base_size);
        positioned.render(color, &font.texture);
        return positioned.next_x;
    } else {
        return x + font.glyphs[' '].width * size / font.header.base_size;
    }
}

void Font::renderChars(const char* str, float x, float y, uint32_t color, float size) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        x = renderChar(str[i], x, y, color, size);
    }
}

void Font::gz_renderChar(char c, float x, float y, uint32_t color, bool drop_shadows, float size) {
    if (drop_shadows) {
        renderChar(c, x + 1.0f, y + 1.0f, DROP_SHADOWS_RGBA, size);
    }
    renderChar(c, x, y, color, size);
}

void Font::gz_renderChars(const char* str, float x, float y, uint32_t color, bool drop_shadows, float size) {
    if (drop_shadows) {
        renderChars(str, x + 1.0f, y + 1.0f, DROP_SHADOWS_RGBA, size);
    }
    renderChars(str, x, y, color, size);
}

float Font::get_char_width(char c, float size) {
    DecodedGlyph glyph;
    if (lookupGlyph(c, glyph)) {
        return glyph.width * size / font.header.base_size;
    } else {
        return font.glyphs[' '].width * size / font.header.base_size;
    }
}

float Font::get_chars_width(const char* str, float size) {
    int len = strlen(str);
    float str_size = 0.f;
    for (int i = 0; i < len; i++) {
        str_size += get_char_width(str[i], size);
    }
    return str_size;
}