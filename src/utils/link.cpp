#include "utils/link.hpp"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "menus/position_settings_menu.h"
#include "menus/settings_menu.h"
#include "menus/tools_menu.h"
#include <stdio.h>

uint8_t red;
uint8_t green;
uint8_t blue;

namespace Utilities {
    void show_link_debug_info(Font &font) {
        if (tp_zelAudio.link_debug_ptr) {
            char link_angle[20];
            //char vspeed[4];
            char link_speed[20];
            char link_x[20];
            char link_y[20];
            char link_z[20];

            sprintf(link_angle, "angle: %d", tp_zelAudio.link_debug_ptr->facing);
            sprintf(link_speed, "speed: %.4f", tp_zelAudio.link_debug_ptr->speed);
            sprintf(link_x, "x-pos: %.4f", tp_zelAudio.link_debug_ptr->position.x);
            sprintf(link_y, "y-pos: %.4f", tp_zelAudio.link_debug_ptr->position.y);
            sprintf(link_z, "z-pos: %.4f", tp_zelAudio.link_debug_ptr->position.z);

            font.gz_renderChars(link_angle, sprite_offsets[DEBUG_INFO_INDEX].x, sprite_offsets[DEBUG_INFO_INDEX].y, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars(link_speed, sprite_offsets[DEBUG_INFO_INDEX].x, sprite_offsets[DEBUG_INFO_INDEX].y + 20.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars(link_x, sprite_offsets[DEBUG_INFO_INDEX].x, sprite_offsets[DEBUG_INFO_INDEX].y + 40.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars(link_y, sprite_offsets[DEBUG_INFO_INDEX].x, sprite_offsets[DEBUG_INFO_INDEX].y + 60.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars(link_z, sprite_offsets[DEBUG_INFO_INDEX].x, sprite_offsets[DEBUG_INFO_INDEX].y + 80.0f, 0xFFFFFFFF, g_drop_shadows);
        } else {
            font.gz_renderChars("angle: n/a", sprite_offsets[DEBUG_INFO_INDEX].x, sprite_offsets[DEBUG_INFO_INDEX].y, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars("speed: n/a", sprite_offsets[DEBUG_INFO_INDEX].x, sprite_offsets[DEBUG_INFO_INDEX].y + 20.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars("x-pos: n/a", sprite_offsets[DEBUG_INFO_INDEX].x, sprite_offsets[DEBUG_INFO_INDEX].y + 40.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars("y-pos: n/a", sprite_offsets[DEBUG_INFO_INDEX].x, sprite_offsets[DEBUG_INFO_INDEX].y + 60.0f, 0xFFFFFFFF, g_drop_shadows);
            font.gz_renderChars("z-pos: n/a", sprite_offsets[DEBUG_INFO_INDEX].x, sprite_offsets[DEBUG_INFO_INDEX].y + 80.0f, 0xFFFFFFFF, g_drop_shadows);
        }
    }
    void change_tunic_color() {
        if (tp_gameInfo.link_tunic_ptr) {
            switch (g_tunic_color) {
                case GREEN: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x00;
                    break;
                }
                case BLUE: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x20;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x80;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x20;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x80;
                    break;
                }
                case RED: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0x80;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0x80;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x00;
                    break;
                }
                case ORANGE: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0xDC;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x14;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0xDC;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x14;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x00;
                    break;
                }
                case YELLOW: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x00;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x00;
                    break;
                }
                case WHITE: {
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = 0x30;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = 0x30;
                    break;
                }
                case CYCLE: {
                    if (red < 0x0040 && (green == 0x0000 && blue == 0x0000)) {
                        red += 0x0002;
                    } else if (green < 0x0040 && (blue == 0x0000 && red == 0x0040)) {
                        green += 0x0002;
                    } else if (blue < 0x0040 && (green == 0x0040 && red == 0x0040)) {
                        blue += 0x0002;
                    } else if (red > 0x0000 && (green == 0x0040 && blue == 0x0040)) {
                        red -= 0x0002;
                    } else if (green > 0x0000 && (blue == 0x0040 && red == 0x0000)) {
                        green -= 0x0002;
                    } else {
                        blue -= 0x0002;
                    }
                    tp_gameInfo.link_tunic_ptr->tunic_top_red = red;
                    tp_gameInfo.link_tunic_ptr->tunic_top_green = green;
                    tp_gameInfo.link_tunic_ptr->tunic_top_blue = blue;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_red = red;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_green = green;
                    tp_gameInfo.link_tunic_ptr->tunic_bottom_blue = blue;
                    break;
                }
            }
        }
    }
}  // namespace Utilities

// temp -
// patch setWaterDropEffect back to it's original code
// tp_memset((void *)0x801244a4, 0xB0, 1);
// tp_memset((void *)0x801244a5, 0x03, 1);
// tp_memset((void *)0x801244a6, 0x32, 1);
// tp_memset((void *)0x801244a7, 0xA0, 1);
// tp_memset((void *)0x801244a8, 0xB0, 1);
// tp_memset((void *)0x801244a9, 0x03, 1);
// tp_memset((void *)0x801244aa, 0x32, 1);
// tp_memset((void *)0x801244ab, 0xA2, 1);
// tp_memset((void *)0x801244ac, 0xB0, 1);
// tp_memset((void *)0x801244ad, 0x03, 1);
// tp_memset((void *)0x801244ae, 0x32, 1);
// tp_memset((void *)0x801244af, 0xA4, 1);