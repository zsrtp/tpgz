#include "utils/link.h"
#include <cstdio>
#include "pos_settings.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/m_Do/m_Do_audio.h"
#include "tools.h"
#include "rels/include/defines.h"

KEEP_FUNC void GZ_displayLinkInfo() {
    if (!GZStng_getData(STNG_TOOLS_LINK_DEBUG, false)) {
        return;
    }
    char time[14] = {0};
    snprintf(time, sizeof(time), "time: %02d:%02d", g_mDoAud_zelAudio.mAudioMgr.mStatusMgr.mHour,
             g_mDoAud_zelAudio.mAudioMgr.mStatusMgr.mMinute);
    Vec2 spriteOffset = GZ_getSpriteOffset(STNG_SPRITES_DEBUG_INFO);
    Font::GZ_drawStr(time, spriteOffset.x, spriteOffset.y, 0xFFFFFFFF, GZ_checkDropShadows());

    if (dComIfGp_getPlayer()) {
        char link_angle[22];
        char y_angle[22];
        char link_speed[22];
        char link_x[22];
        char link_y[22];
        char link_z[22];
        char link_action[22];

        snprintf(link_angle, sizeof(link_angle), "angle: %d",
                 (uint16_t)dComIfGp_getPlayer()->shape_angle.y);
        snprintf(y_angle, sizeof(y_angle), "y-angle: %d", dComIfGp_getPlayer()->mLookAngleY);
        snprintf(link_speed, sizeof(link_speed), "speed: %.4f", dComIfGp_getPlayer()->speedF);
        snprintf(link_x, sizeof(link_x), "x-pos: %.4f", dComIfGp_getPlayer()->current.pos.x);
        snprintf(link_y, sizeof(link_y), "y-pos: %.4f", dComIfGp_getPlayer()->current.pos.y);
        snprintf(link_z, sizeof(link_z), "z-pos: %.4f", dComIfGp_getPlayer()->current.pos.z);
        snprintf(link_action, sizeof(link_action), "action: %d", dComIfGp_getPlayer()->mActionID);


        Font::GZ_drawStr(link_angle, spriteOffset.x,
                         spriteOffset.y + 20.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr(y_angle, spriteOffset.x,
                         spriteOffset.y + 40.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr(link_speed, spriteOffset.x,
                         spriteOffset.y + 60.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr(link_x, spriteOffset.x,
                         spriteOffset.y + 80.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr(link_y, spriteOffset.x,
                         spriteOffset.y + 100.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr(link_z, spriteOffset.x,
                         spriteOffset.y + 120.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr(link_action, spriteOffset.x,
                        spriteOffset.y + 140.0f, 0xFFFFFFFF,
                        GZ_checkDropShadows());
    } else {
        Font::GZ_drawStr("angle: n/a", spriteOffset.x,
                         spriteOffset.y + 20.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr("y-angle: n/a", spriteOffset.x,
                         spriteOffset.y + 40.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr("speed: n/a", spriteOffset.x,
                         spriteOffset.y + 60.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr("x-pos: n/a", spriteOffset.x,
                         spriteOffset.y + 80.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr("y-pos: n/a", spriteOffset.x,
                         spriteOffset.y + 100.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr("z-pos: n/a", spriteOffset.x,
                         spriteOffset.y + 120.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
        Font::GZ_drawStr("action: n/a", spriteOffset.x,
                         spriteOffset.y + 140.0f, 0xFFFFFFFF,
                         GZ_checkDropShadows());
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