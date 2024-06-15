#include "utils/texture.h"
#include <cstring>
#include "libtp_c/include/msl_c/math.h"
#include "utils/disc.h"
#include "gcn_c/include/dvd.h"
#include "rels/include/cxx.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"

enum TexFmt {
    RGB8 = 0,
    CMPR = 1,
    I8 = 2,
};

#ifdef __cplusplus
extern "C" {
#endif

uint32_t get_size(uint32_t format, uint32_t width, uint32_t height) {
    switch (format) {
    case TexFmt::CMPR: {
        return width * height / 2;
    }
    case TexFmt::I8: {
        return width * height;
    }
    case TexFmt::RGB8:
    default: {
        return 4 * width * height;
    }
    }
}

TexCode load_texture(const char* path, Texture* tex) {
    return load_texture_offset(path, tex, 0);
}

TexCode load_texture_offset(const char* path, Texture* tex, uint32_t offset) {
    DVDFileInfo fileInfo;
    int32_t readsize;
    if (tex->loadCode == TexCode::TEX_OK) {
        free_texture(tex);
    }

    if (!DVDOpen(path, &fileInfo)) {
        tex->loadCode = TexCode::TEX_ERR_FILE;
        OSReport_Warning("Texture not loaded \"%s\"; Couldn't open path [%d]\n", path, tex->loadCode);
        return tex->loadCode;
    }
    readsize = dvd_read(&fileInfo, &tex->header, sizeof(TexHeader), offset);
    if (readsize < (int32_t)sizeof(TexHeader)) {
        DVDClose(&fileInfo);
        tex->loadCode = TexCode::TEX_ERR_READ;
        OSReport_Warning("Texture not loaded \"%s\"; Couldn't read file header [%d]\n", path, tex->loadCode);
        return tex->loadCode;
    }

    uint8_t fmt = GX_TF_I8;
    switch (tex->header.format) {
    case TexFmt::RGB8: {
        fmt = GX_TF_RGBA8;
        break;
    }
    case TexFmt::CMPR: {
        fmt = GX_TF_CMPR;
        break;
    }
    case TexFmt::I8: {
        fmt = GX_TF_I8;
        break;
    }
    default: {
        DVDClose(&fileInfo);
        tex->loadCode = TexCode::TEX_ERR_INVALID_FORMAT;
        OSReport_Warning("Texture not loaded \"%s\"; Invalid texture format id (%d) [%d]\n", path, tex->header.format, tex->loadCode);
        return tex->loadCode;
    }
    }

    uint32_t size = get_size(tex->header.format, tex->header.width, tex->header.height);
    tex->data = new (-32) uint8_t[size];
    if (tex->data == nullptr) {
        DVDClose(&fileInfo);
        tex->loadCode = TexCode::TEX_ERR_MEM;
        OSReport_Warning("Texture not loaded \"%s\"; Couldn't allocate 0x%x bytes for data [%d]\n", path, size, tex->loadCode);
        return tex->loadCode;
    }

    if (DVDReadPrio(&fileInfo, tex->data, size, offset + sizeof(tex->header), 2) < (int32_t)size) {
        delete tex->data;
        DVDClose(&fileInfo);
        tex->loadCode = TexCode::TEX_ERR_READ;
        OSReport_Warning("Texture not loaded \"%s\"; Couldn't read texture data [%d]\n", path, tex->loadCode);
        return tex->loadCode;
    }
    DVDClose(&fileInfo);

    memset(&tex->_texObj, 0, sizeof(GXTexObj));
    GXInitTexObj(&tex->_texObj, tex->data, tex->header.width, tex->header.height, (GXTexFmt)fmt, GX_CLAMP,
                 GX_CLAMP, GX_FALSE);
    tex->loadCode = TexCode::TEX_OK;
    return tex->loadCode;
}

void free_texture(Texture* tex) {
    if (tex->data != nullptr) {
        delete tex->data;
        tex->data = 0;
    }
    memset(tex, 0, sizeof(Texture));
    // The next line is redundant, but is still there for good measure
    tex->loadCode = TexCode::TEX_UNLOADED;
}

void setupRendering() {
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_SET);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE,
                      GX_PTIDENTITY);

    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
}

#ifdef __cplusplus
}
#endif