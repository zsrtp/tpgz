#ifndef JUTTEXTURE_H
#define JUTTEXTURE_H

#include <stdint.h>

struct ResTIMG { /* Acts as the header to image data. Usually texture data immediately follows it,
                    so any pointer arithmetic to go past the end of this structure is so that a
                    variable sized allocated buffer can be accessed. */
    uint8_t texture_format;
    bool is_alpha_enabled;
    uint16_t texture_width;
    uint16_t texture_height;
    uint8_t wrap_s;
    uint8_t wrap_t;
    bool is_palettes_enabled;
    uint8_t palette_format;
    uint16_t palette_count;
    uint32_t palette_offset;
    bool is_mip_map_enabled;
    bool do_edge_lod;
    bool bias_clamp;
    uint8_t max_anisotropy;
    uint8_t min_filter;
    uint8_t mag_filter;
    uint8_t min_lod;
    uint8_t max_lod;
    uint8_t num_mipmaps;
    uint8_t unknown;
    uint16_t lod_bias;
    uint32_t texture_data_offset;
};

#endif /* JUTTEXTURE_H */
