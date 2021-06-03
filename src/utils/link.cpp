#include "utils/link.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/position_settings_menu.h"
#include "menus/settings_menu.h"
#include "menus/tools_menu.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"

uint8_t red;
uint8_t green;
uint8_t blue;

namespace Utilities {
void show_link_debug_info() {
    if (dComIfGp_getPlayer()) {
        char link_angle[20];
        // char vspeed[4];
        char link_speed[20];
        char link_x[20];
        char link_y[20];
        char link_z[20];

        tp_sprintf(link_angle, "angle: %d", (uint16_t)dComIfGp_getPlayer()->mCollisionRot.mY);
        tp_sprintf(link_speed, "speed: %.4f", dComIfGp_getPlayer()->mSpeedF);
        tp_sprintf(link_x, "x-pos: %.4f", dComIfGp_getPlayer()->mCurrent.mPosition.x);
        tp_sprintf(link_y, "y-pos: %.4f", dComIfGp_getPlayer()->mCurrent.mPosition.y);
        tp_sprintf(link_z, "z-pos: %.4f", dComIfGp_getPlayer()->mCurrent.mPosition.z);

        Font::gz_renderChars(link_angle, sprite_offsets[DEBUG_INFO_INDEX].x,
                             sprite_offsets[DEBUG_INFO_INDEX].y, 0xFFFFFFFF, g_drop_shadows);
        Font::gz_renderChars(link_speed, sprite_offsets[DEBUG_INFO_INDEX].x,
                             sprite_offsets[DEBUG_INFO_INDEX].y + 20.0f, 0xFFFFFFFF,
                             g_drop_shadows);
        Font::gz_renderChars(link_x, sprite_offsets[DEBUG_INFO_INDEX].x,
                             sprite_offsets[DEBUG_INFO_INDEX].y + 40.0f, 0xFFFFFFFF,
                             g_drop_shadows);
        Font::gz_renderChars(link_y, sprite_offsets[DEBUG_INFO_INDEX].x,
                             sprite_offsets[DEBUG_INFO_INDEX].y + 60.0f, 0xFFFFFFFF,
                             g_drop_shadows);
        Font::gz_renderChars(link_z, sprite_offsets[DEBUG_INFO_INDEX].x,
                             sprite_offsets[DEBUG_INFO_INDEX].y + 80.0f, 0xFFFFFFFF,
                             g_drop_shadows);
    } else {
        Font::gz_renderChars("angle: n/a", sprite_offsets[DEBUG_INFO_INDEX].x,
                             sprite_offsets[DEBUG_INFO_INDEX].y, 0xFFFFFFFF, g_drop_shadows);
        Font::gz_renderChars("speed: n/a", sprite_offsets[DEBUG_INFO_INDEX].x,
                             sprite_offsets[DEBUG_INFO_INDEX].y + 20.0f, 0xFFFFFFFF,
                             g_drop_shadows);
        Font::gz_renderChars("x-pos: n/a", sprite_offsets[DEBUG_INFO_INDEX].x,
                             sprite_offsets[DEBUG_INFO_INDEX].y + 40.0f, 0xFFFFFFFF,
                             g_drop_shadows);
        Font::gz_renderChars("y-pos: n/a", sprite_offsets[DEBUG_INFO_INDEX].x,
                             sprite_offsets[DEBUG_INFO_INDEX].y + 60.0f, 0xFFFFFFFF,
                             g_drop_shadows);
        Font::gz_renderChars("z-pos: n/a", sprite_offsets[DEBUG_INFO_INDEX].x,
                             sprite_offsets[DEBUG_INFO_INDEX].y + 80.0f, 0xFFFFFFFF,
                             g_drop_shadows);
    }
}
void change_tunic_color() {
    if (dComIfGp_getPlayer()) {
        int16_t red_ = 0;
        int16_t green_ = 0;
        int16_t blue_ = 0;
        switch (g_tunic_color) {
        case GREEN:  // passthrough
        default: {
            red_ = 0x10;
            green_ = 0x10;
            blue_ = 0x10;
            break;
        }
        case BLUE: {
            red_ = 0x00;
            green_ = 0x08;
            blue_ = 0x20;
            break;
        }
        case RED: {
            red_ = 0x18;
            green_ = 0x00;
            blue_ = 0x00;
            break;
        }
        case ORANGE: {
            red_ = 0x20;
            green_ = 0x10;
            blue_ = 0x00;
            break;
        }
        case YELLOW: {
            red_ = 0x20;
            green_ = 0x20;
            blue_ = 0x00;
            break;
        }
        case WHITE: {
            red_ = 0x20;
            green_ = 0x1C;
            blue_ = 0x20;
            break;
        }
        case CYCLE: {
            if (red < 0x0010 && (green == 0x0000 && blue == 0x0000)) {
                red += 0x0001;
            } else if (green < 0x0010 && (blue == 0x0000 && red == 0x0010)) {
                green += 0x0001;
            } else if (blue < 0x0010 && (green == 0x0010 && red == 0x0010)) {
                blue += 0x0001;
            } else if (red > 0x0000 && (green == 0x0010 && blue == 0x0010)) {
                red -= 0x0001;
            } else if (green > 0x0000 && (blue == 0x0010 && red == 0x0000)) {
                green -= 0x0001;
            } else {
                blue -= 0x0001;
            }
            red_ = red;
            green_ = green;
            blue_ = blue;
            break;
        }
        }
#ifdef GCN_PLATFORM
        dComIfGp_getPlayer()->field_0x32a0[0].mColor.r = red_ - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[0].mColor.g = green_ - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[0].mColor.b = blue_ - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.r = red_ - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.g = green_ - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.b = blue_ - 0x10;
#endif
#ifdef WII_PLATFORM
        dComIfGp_getPlayer()->field_0x32a0[0].mColor.r = red_ - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[0].mColor.g = green_ - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[0].mColor.b = blue_ - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.r = red_ - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.g = green_ - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.b = blue_ - 0x10;
        // tp_gameInfo.link_tunic_ptr->not_tunic_red = 1;
        // tp_gameInfo.link_tunic_ptr->tunic_red = red_ - 0x10;
        // tp_gameInfo.link_tunic_ptr->tunic_green = green_ - 0x10;
        // tp_gameInfo.link_tunic_ptr->tunic_blue = blue_ - 0x10;
#endif
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