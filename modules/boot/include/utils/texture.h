#pragma once

#include <stdint.h>
#include "libtp_c/include/dolphin/gx/gx.h"

enum TexCode {
    TEX_OK = 1,                  /*<@brief Texture loaded successfully */
    TEX_UNLOADED = 0,            /*<@brief Texture hasn't been loaded yet */
    TEX_ERR_FILE = -1,           /*<@brief Could not open texture file */
    TEX_ERR_READ = -2,           /*<@brief Error occured while reading the texture file */
    TEX_ERR_INVALID_FORMAT = -3, /*<@brief The format of the texture file is not supported */
    TEX_ERR_MEM = -4,            /*<@brief Not enough memory to load the texture */
};

struct TexHeader {
    uint32_t magic;
    uint32_t format;
    uint32_t width;
    uint32_t height;
} __attribute__((packed));

struct Texture {
    TexHeader header;
    uint8_t* data;
    GXTexObj _texObj;
    TexCode loadCode;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Loads a texture from a file on the DVD.
 *
 * @param[in] path Path to the texture file on the DVD.
 * @param[out] tex Texture object containing the fetched texture.
 * @returns A TexCode code signaling the success/failure of the loading.
 */
TexCode load_texture(const char* path, Texture* tex);
/**
 * @brief Loads a texture at an offset from a file on the DVD.
 *
 * @param[in] path Path to the texture file on the DVD.
 * @param[out] tex Texture object containing the fetched texture.
 * @param[in] offset Offset in the file to start loading the texture from.
 * @returns A TexCode code signaling the success/failure of the loading.
 */
TexCode load_texture_offset(const char* path, Texture* tex, uint32_t offset);
void free_texture(Texture* tex);

void setupRendering();

#ifdef __cplusplus
}
#endif