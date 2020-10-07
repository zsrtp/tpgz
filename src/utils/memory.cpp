#include "utils/memory.hpp"
#include "libtp_c/include/system.h"
#include "menus/memory_menu.h"
#include "menus/settings_menu.h"

namespace Utilities {
    void render_active_watches(Font &font) {
        for (int i = 0; i < MAX_WATCHES; i++) {
            if (Watches[i].visible) {
                char rendered_value[8];
                switch (Watches[i].type) {
                    case u32: {
                        if (Watches[i].offset > 0x0000) {
                            sprintf(rendered_value, Watches[i].hex ? "%08X" : "%u", *(uint32_t *)(*(uint32_t *)Watches[i].address + Watches[i].offset));
                        } else {
                            sprintf(rendered_value, Watches[i].hex ? "%08X" : "%u", *(uint32_t *)Watches[i].address);
                        }
                        font.gz_renderChars(rendered_value, Watches[i].x, Watches[i].y, 0xFFFFFFFF, g_drop_shadows);
                        break;
                    }
                    case u16: {
                        if (Watches[i].offset > 0x0000) {
                            sprintf(rendered_value, Watches[i].hex ? "%04X" : "%u", *(uint16_t *)(*(uint32_t *)Watches[i].address + Watches[i].offset));
                        } else {
                            sprintf(rendered_value, Watches[i].hex ? "%04X" : "%u", *(uint16_t *)Watches[i].address);
                        }
                        font.gz_renderChars(rendered_value, Watches[i].x, Watches[i].y, 0xFFFFFFFF, g_drop_shadows);
                        break;
                    }
                    case u8: {
                        if (Watches[i].offset > 0x0000) {
                            sprintf(rendered_value, Watches[i].hex ? "%02X" : "%u", *(uint8_t *)(*(uint32_t *)Watches[i].address + Watches[i].offset));
                        } else {
                            sprintf(rendered_value, Watches[i].hex ? "%02X" : "%u", *(uint8_t *)Watches[i].address);
                        }
                        font.gz_renderChars(rendered_value, Watches[i].x, Watches[i].y, 0xFFFFFFFF, g_drop_shadows);
                        break;
                    }
                    case i32: {
                        if (Watches[i].offset > 0x0000) {
                            sprintf(rendered_value, Watches[i].hex ? "%08X" : "%i", *(int32_t *)(*(uint32_t *)Watches[i].address + Watches[i].offset));
                        } else {
                            sprintf(rendered_value, Watches[i].hex ? "%08X" : "%i", *(int32_t *)Watches[i].address);
                        }
                        font.gz_renderChars(rendered_value, Watches[i].x, Watches[i].y, 0xFFFFFFFF, g_drop_shadows);
                        break;
                    }
                    case i16: {
                        if (Watches[i].offset > 0x0000) {
                            sprintf(rendered_value, Watches[i].hex ? "%04X" : "%i", *(int16_t *)(*(uint32_t *)Watches[i].address + Watches[i].offset));
                        } else {
                            sprintf(rendered_value, Watches[i].hex ? "%04X" : "%i", *(int16_t *)Watches[i].address);
                        }
                        font.gz_renderChars(rendered_value, Watches[i].x, Watches[i].y, 0xFFFFFFFF, g_drop_shadows);
                        break;
                    }
                    case i8: {
                        if (Watches[i].offset > 0x0000) {
                            sprintf(rendered_value, Watches[i].hex ? "%02X" : "%i", *(int8_t *)(*(uint32_t *)Watches[i].address + Watches[i].offset));
                        } else {
                            sprintf(rendered_value, Watches[i].hex ? "%02X" : "%i", *(int8_t *)Watches[i].address);
                        }
                        font.gz_renderChars(rendered_value, Watches[i].x, Watches[i].y, 0xFFFFFFFF, g_drop_shadows);
                        break;
                    }
                    case f32: {
                        if (Watches[i].offset > 0x0000) {
                            sprintf(rendered_value, "%.2f", *(float *)(*(uint32_t *)Watches[i].address + Watches[i].offset));
                        } else {
                            sprintf(rendered_value, "%.2f", *(float *)Watches[i].address);
                        }
                        font.gz_renderChars(rendered_value, Watches[i].x, Watches[i].y, 0xFFFFFFFF, g_drop_shadows);
                        break;
                    }
                    case string: {
                        if (Watches[i].offset > 0x0000) {
                            sprintf(rendered_value, "%s", (char *)(*(uint32_t *)Watches[i].address + Watches[i].offset));
                        } else {
                            sprintf(rendered_value, "%s", (char *)Watches[i].address);
                        }
                        font.gz_renderChars(rendered_value, Watches[i].x, Watches[i].y, 0xFFFFFFFF, g_drop_shadows);
                        break;
                    }
                }
                // logic to draw the watch
            }
        }
    }
}  // namespace Utilities