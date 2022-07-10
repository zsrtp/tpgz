#include "utils/link.h"
#include "libtp_c/include/msl_c/string.h"
#include "menus/position_settings_menu.h"
#include "menus/settings_menu.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/m_Do/m_Do_audio.h"


void GZ_displayLinkInfo() {
    char time[12];
    tp_sprintf(time, "time: %02d:%02d", g_mDoAud_zelAudio.mAudioMgr.mStatusMgr.mHour, g_mDoAud_zelAudio.mAudioMgr.mStatusMgr.mMinute);
    Font::GZ_drawStr(time, g_spriteOffsets[DEBUG_INFO_INDEX].x, g_spriteOffsets[DEBUG_INFO_INDEX].y, 0xFFFFFFFF, g_dropShadows);

    if (dComIfGp_getPlayer()) {
        char link_angle[20];
        char y_angle[20];
        char link_speed[20];
        char link_x[20];
        char link_y[20];
        char link_z[20];

        tp_sprintf(link_angle, "angle: %d", (uint16_t)dComIfGp_getPlayer()->mCollisionRot.mY);
        tp_sprintf(y_angle, "y-angle: %d", dComIfGp_getPlayer()->mLookAngleY);
        tp_sprintf(link_speed, "speed: %.4f", dComIfGp_getPlayer()->mSpeedF);
        tp_sprintf(link_x, "x-pos: %.4f", dComIfGp_getPlayer()->mCurrent.mPosition.x);
        tp_sprintf(link_y, "y-pos: %.4f", dComIfGp_getPlayer()->mCurrent.mPosition.y);
        tp_sprintf(link_z, "z-pos: %.4f", dComIfGp_getPlayer()->mCurrent.mPosition.z);

        Font::GZ_drawStr(link_angle, g_spriteOffsets[DEBUG_INFO_INDEX].x, g_spriteOffsets[DEBUG_INFO_INDEX].y + 20.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(y_angle, g_spriteOffsets[DEBUG_INFO_INDEX].x,
                             g_spriteOffsets[DEBUG_INFO_INDEX].y + 40.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr(link_speed, g_spriteOffsets[DEBUG_INFO_INDEX].x,
                             g_spriteOffsets[DEBUG_INFO_INDEX].y + 60.0f, 0xFFFFFFFF,
                             g_dropShadows);
        Font::GZ_drawStr(link_x, g_spriteOffsets[DEBUG_INFO_INDEX].x,
                             g_spriteOffsets[DEBUG_INFO_INDEX].y + 80.0f, 0xFFFFFFFF,
                             g_dropShadows);
        Font::GZ_drawStr(link_y, g_spriteOffsets[DEBUG_INFO_INDEX].x,
                             g_spriteOffsets[DEBUG_INFO_INDEX].y + 100.0f, 0xFFFFFFFF,
                             g_dropShadows);
        Font::GZ_drawStr(link_z, g_spriteOffsets[DEBUG_INFO_INDEX].x,
                             g_spriteOffsets[DEBUG_INFO_INDEX].y + 120.0f, 0xFFFFFFFF,
                             g_dropShadows);
    } else {
        Font::GZ_drawStr("angle: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                             g_spriteOffsets[DEBUG_INFO_INDEX].y + 20.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr("y-angle: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                             g_spriteOffsets[DEBUG_INFO_INDEX].y + 40.0f, 0xFFFFFFFF, g_dropShadows);
        Font::GZ_drawStr("speed: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                             g_spriteOffsets[DEBUG_INFO_INDEX].y + 60.0f, 0xFFFFFFFF,
                             g_dropShadows);
        Font::GZ_drawStr("x-pos: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                             g_spriteOffsets[DEBUG_INFO_INDEX].y + 80.0f, 0xFFFFFFFF,
                             g_dropShadows);
        Font::GZ_drawStr("y-pos: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                             g_spriteOffsets[DEBUG_INFO_INDEX].y + 100.0f, 0xFFFFFFFF,
                             g_dropShadows);
        Font::GZ_drawStr("z-pos: n/a", g_spriteOffsets[DEBUG_INFO_INDEX].x,
                             g_spriteOffsets[DEBUG_INFO_INDEX].y + 120.0f, 0xFFFFFFFF,
                             g_dropShadows);
    }
}