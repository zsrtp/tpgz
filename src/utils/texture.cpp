#include "libtp_c/include/system.h"
#include "libtp_c/include/math.h"
#include "libtp_c/include/addrs.h"
#include "gcn_c/include/gfx.h"
#include "gcn_c/include/dvd.h"
#include "utils/texture.h"

enum TexFmt {
    RGB8 = 0,
    CMPR = 1,
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Like DVDReadPrio, but allows for arbitrary sizes and offsets.
 */
int32_t dvd_read(DVDFileInfo* file_info, void* data, int32_t size, int32_t offset) {
    constexpr const uint32_t buf_size = 0x20;
    uint8_t* buf = (uint8_t*)tp_memalign(-32, buf_size);
    int32_t read_bytes = 0;

    while (size > 0) {
        int32_t result = DVDReadPrio(file_info, buf, buf_size, (offset & ~(buf_size - 1)), 2);
        if (result <= 0) {
            break;
        }
        int32_t rem_size = buf_size - (offset & (buf_size - 1));
        tp_memcpy((void*)((uint32_t)data + read_bytes), buf + (offset & (buf_size - 1)), MIN(rem_size, size));
        read_bytes += MIN(rem_size, size);
        size -= rem_size;
        offset += rem_size;
    }
    tp_free(buf);
    return read_bytes;
}

uint32_t get_size(uint32_t format, uint32_t width, uint32_t height) {
    switch(format) {
        case TexFmt::CMPR: {
            return width * height / 2;
        }
        case TexFmt::RGB8:
        default: {
            return 4 * width * height;
        }
    }
}

int32_t load_texture(const char* path, Texture* tex) {
    DVDFileInfo fileInfo;
    int32_t readsize;

    if(!DVDOpen(path, &fileInfo)) {
        tex->loadCode = TexCode::TEX_ERR_FILE;
        return tex->loadCode;
    }
    readsize = dvd_read(&fileInfo, &tex->header, sizeof(TexHeader), 0);
    if (readsize < (int32_t)sizeof(TexHeader)) {
        DVDClose(&fileInfo);
        tex->loadCode = TexCode::TEX_ERR_READ;
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
        default: {
            DVDClose(&fileInfo);
            tex->loadCode = TexCode::TEX_ERR_INVALID_FORMAT;
            return tex->loadCode;
        }
    }

    uint32_t size = get_size(tex->header.format, tex->header.width, tex->header.height);
    tex->data = (uint8_t*)tp_memalign(-32, size);
    if (tex->data == nullptr) {
        DVDClose(&fileInfo);
        tex->loadCode = TexCode::TEX_ERR_MEM;
        return tex->loadCode;
    }

    if (DVDReadPrio(&fileInfo, tex->data, size, sizeof(tex->header), 2) < (int32_t)size) {
        tp_free(tex->data);
        DVDClose(&fileInfo);
        tex->loadCode = TexCode::TEX_ERR_READ;
        return tex->loadCode;
    }
    DVDClose(&fileInfo);

    tp_memset(&tex->_texObj, 0, sizeof(GXTexObj));
    GX_InitTexObj(&tex->_texObj, tex->data, tex->header.width, tex->header.height, fmt, GX_CLAMP, GX_CLAMP, GX_FALSE);
    tex->loadCode = TexCode::TEX_OK;
    return tex->loadCode;
}

void free_texture(Texture* tex) {
    tp_free(tex->data);
    tp_memset(tex, 0, sizeof(Texture));
    // The next line is redundant, but is still there for good measure
    tex->loadCode = TexCode::TEX_UNLOADED;
}

#ifdef __cplusplus
}
#endif