#include "libtp_c/include/system.h"
#include "font.h"

void PositionedGlyph::render(uint32_t color) {
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
    for (int i = 0; i < 4; i++) {
        GX_Position2f32(vertices[i][0], vertices[i][1]);
        GX_Color1u32(color);
        GX_Position2f32(tex_coords[i][0], tex_coords[i][1]);
    }
    GX_End();
}

PositionedGlyph DecodedGlyph::position(float _x, float _y) {
    float y = _y + glyph->descender;
    float vty = y - height;
    float vby = y;
    float vrx = _x + width;
    float vlx = _x;

    float tty = glyph->minY;
    float tby = glyph->maxY;
    float trx = glyph->maxX;
    float tlx = glyph->minX;

    return {
        {{vlx, vty}, {vrx, vty}, {vrx, vby}, {vlx, vby}},
        {{tlx, tty}, {trx, tty}, {trx, tby}, {tlx, tby}},
        (_x + advance_x)};
}

Font::Font(const _Font& _font) {
    tp_memset(&_texobj, 0x0, sizeof(GXTexObj));
    GX_InitTexObj(&_texobj, _font._start, _font.width, _font.height, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    font = &_font;
}

Font::Font(const _Font& _font, const char* data) {
    tp_memset(&_texobj, 0x0, sizeof(GXTexObj));
    GX_InitTexObj(&_texobj, (void*)data, _font.width, _font.height, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    font = &_font;
}

bool Font::lookupGlyph(char c, DecodedGlyph& glyph) {
    int idx = c - '!';
    if (idx < 0 || idx > (MAX_GLYPHS - 1)) {
        return false;
    }
    _Glyph _glyph = font->glyphs[idx];
    glyph.glyph = &_glyph;
    glyph.width = (_glyph.maxX - _glyph.minX) * font->width;
    glyph.height = (_glyph.maxY - _glyph.minY) * font->height;
    glyph.advance_x = glyph.width;
    return true;
}

float Font::renderChar(char c, float x, float y, uint32_t color) {
    GX_LoadTexObj(&_texobj, (uint8_t)GX_TEXMAP0);
    DecodedGlyph glyph;
    if (lookupGlyph(c, glyph)) {
        auto positioned = glyph.position(x, y);
        positioned.render(color);
        return positioned.next_x;
    } else {
        return x + font->spaceAdvance;
    }
}

void Font::renderChars(const char* str, float x, float y, uint32_t color) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        x = renderChar(str[i], x, y, color);
    }
}

void Font::gz_renderChar(char c, float x, float y, uint32_t color, bool drop_shadows) {
    this->renderChar(c, x, y, color);
    if (drop_shadows) {
        this->renderChar(c, x + 1.0f, y + 1.0f, DROP_SHADOWS_RGBA);
    }
}

void Font::gz_renderChars(const char* str, float x, float y, uint32_t color, bool drop_shadows) {
    this->renderChars(str, x, y, color);
    if (drop_shadows) {
        this->renderChars(str, x + 1.0f, y + 1.0f, DROP_SHADOWS_RGBA);
    }
}

void Font::setupRendering() {
    GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);

    GX_ClearVtxDesc();
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GX_SetNumTexGens(1);
    GX_SetTexCoordGen2((uint16_t)GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_DTTIDENTITY);

    GX_SetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GX_SetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GX_SetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GX_SetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
}