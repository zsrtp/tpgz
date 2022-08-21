#include "utils/link.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/position_settings_menu.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/m_Do/m_Do_audio.h"
#include "tools.h"
#include "rels/include/defines.h"

KEEP_FUNC void GZ_displayLinkInfo() {
    if (!g_tools[LINK_DEBUG_INDEX].active) {
        return;
    }
    char time[12] = {0};
    sprintf(time, "time: %02d:%02d", g_mDoAud_zelAudio.mAudioMgr.mStatusMgr.mHour,
            g_mDoAud_zelAudio.mAudioMgr.mStatusMgr.mMinute);
    Font::GZ_drawStr(time, g_spriteOffsets[DEBUG_INFO_INDEX].x, g_spriteOffsets[DEBUG_INFO_INDEX].y,
                     0xFFFFFFFF, g_dropShadows);

    if (dComIfGp_getPlayer()) {
        char link_angle[20];
        char y_angle[20];
        char link_speed[20];
        char link_x[20];
        char link_y[20];
        char link_z[20];

        sprintf(link_angle, "angle: %d", (uint16_t)dComIfGp_getPlayer()->mCollisionRot.mY);
        sprintf(y_angle, "y-angle: %d", dComIfGp_getPlayer()->mLookAngleY);
        sprintf(link_speed, "speed: %.4f", dComIfGp_getPlayer()->mSpeedF);
        sprintf(link_x, "x-pos: %.4f", dComIfGp_getPlayer()->mCurrent.mPosition.x);
        sprintf(link_y, "y-pos: %.4f", dComIfGp_getPlayer()->mCurrent.mPosition.y);
        sprintf(link_z, "z-pos: %.4f", dComIfGp_getPlayer()->mCurrent.mPosition.z);

        Font::GZ_drawStr(link_angle, g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 20.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(y_angle, g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 40.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(link_speed, g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 60.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(link_x, g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 80.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(link_y, g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 100.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(link_z, g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 120.0f, 0xFFFFFFFF, g_dropShadows);
    } else {
        Font::GZ_drawStr("angle: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 20.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr("y-angle: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 40.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr("speed: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 60.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr("x-pos: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 80.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr("y-pos: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 100.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr("z-pos: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                         g_spriteOffsets[DEBUG_INFO_INDEX].y + 120.0f, 0xFFFFFFFF, g_dropShadows);
    }
}

KEEP_FUNC void GZ_setTunicColor() {
    static int16_t cycle_r = 0;
    static int16_t cycle_g = 0;
    static int16_t cycle_b = 0;

    if (dComIfGp_getPlayer()) {
        int16_t r = 0;
        int16_t g = 0;
        int16_t b = 0;

        switch (g_tunic_color) {
        case GREEN:
        default:
            r = 0x10;
            g = 0x10;
            b = 0x10;
            break;
        case BLUE:
            r = 0x00;
            g = 0x08;
            b = 0x20;
            break;
        case RED:
            r = 0x18;
            g = 0x00;
            b = 0x00;
            break;
        case ORANGE:
            r = 0x20;
            g = 0x10;
            b = 0x00;
            break;
        case YELLOW:
            r = 0x20;
            g = 0x20;
            b = 0x00;
            break;
        case WHITE:
            r = 0x20;
            g = 0x1C;
            b = 0x20;
            break;
        case CYCLE:
            if (cycle_r < 0x0010 && (cycle_g == 0x0000 && cycle_b == 0x0000)) {
                cycle_r += 0x0001;
            } else if (cycle_g < 0x0010 && (cycle_b == 0x0000 && cycle_r == 0x0010)) {
                cycle_g += 0x0001;
            } else if (cycle_b < 0x0010 && (cycle_g == 0x0010 && cycle_r == 0x0010)) {
                cycle_b += 0x0001;
            } else if (cycle_r > 0x0000 && (cycle_g == 0x0010 && cycle_b == 0x0010)) {
                cycle_r -= 0x0001;
            } else if (cycle_g > 0x0000 && (cycle_b == 0x0010 && cycle_r == 0x0000)) {
                cycle_g -= 0x0001;
            } else {
                cycle_b -= 0x0001;
            }

            r = cycle_r;
            g = cycle_g;
            b = cycle_b;
            break;
        }

        dComIfGp_getPlayer()->field_0x32a0[0].mColor.r = r - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[0].mColor.g = g - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[0].mColor.b = b - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.r = r - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.g = g - 0x10;
        dComIfGp_getPlayer()->field_0x32a0[1].mColor.b = b - 0x10;
    }
}