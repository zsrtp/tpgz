#include "menus/scene_menu.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/d/meter/d_meter_HIO.h"
#include "gz_flags.h"

SceneMenu::SceneMenu() : Menu(), lines{
    {"disable bg music", DISABLE_BG_INDEX, "Disables background and enemy music", true,
     &g_sceneFlags[DISABLE_BG_INDEX].active},
    {"disable sfx", DISABLE_SFX_INDEX, "Disables sound effects", true,
     &g_sceneFlags[DISABLE_SFX_INDEX].active},
    {"freeze actors", FREEZE_ACTOR_INDEX, "Freezes actors", true,
     &g_sceneFlags[FREEZE_ACTOR_INDEX].active},
    {"freeze camera", FREEZE_CAMERA_INDEX, "Locks the camera in place", true,
     &g_sceneFlags[FREEZE_CAMERA_INDEX].active},
    {"hide actors", HIDE_ACTOR_INDEX, "Hides actors", true, &g_sceneFlags[HIDE_ACTOR_INDEX].active},
    {"hide hud", HIDE_HUD_INDEX, "Hides the heads-up display", true,
     &g_sceneFlags[HIDE_HUD_INDEX].active},
    {"freeze time", FREEZE_TIME_INDEX, "Freezes ingame time", true,
     &g_sceneFlags[FREEZE_TIME_INDEX].active},
    {"time (hrs):", TIME_HOURS_INDEX, "The current in-game hour", false},
    {"time (mins):", TIME_MINUTES_INDEX, "The current in-game minutes", false},
    {"actor spawner", ACTOR_MENU_INDEX, "Spawn Actors at current position", false},
    {"actor list", ACTOR_LIST_INDEX, "Display info from the actor list", false},
} {}

SceneItem g_sceneFlags[SCENE_AMNT] = {
    {FREEZE_ACTOR_INDEX, false}, {HIDE_ACTOR_INDEX, false},    {DISABLE_BG_INDEX, false},
    {DISABLE_SFX_INDEX, false},  {FREEZE_CAMERA_INDEX, false}, {HIDE_HUD_INDEX, false},
    {FREEZE_TIME_INDEX, false},
};

void GZ_freezeTime() {
    if (g_sceneFlags[FREEZE_TIME_INDEX].active) {
        dStage_roomControl_c__setTimePass(TIME_STOP);
    }
}

bool l_initCamLock;
void GZ_freezeCamera() {
    l_initCamLock = true;
    dComIfGp_getEventManager().mCameraPlay = 1;
}

void GZ_unfreezeCamera() {
    if (l_initCamLock) {
        dComIfGp_getEventManager().mCameraPlay = 0;
        l_initCamLock = false;
    }
}

bool l_initHide;
void GZ_hideHUD() {
    g_drawHIO.mHUDAlpha = 0.0f;
    l_initHide = true;
}

void GZ_showHUD() {
    if (l_initHide) {
        g_drawHIO.mHUDAlpha = 1.0f;
        l_initHide = false;
    }
}

bool l_initActorFreeze;
void GZ_freezeActors() {
    l_initActorFreeze = true;
    g_dComIfAc_gameInfo.freeze = true;
}

void GZ_unfreezeActors() {
    if (l_initActorFreeze) {
        g_dComIfAc_gameInfo.freeze = false;
        l_initActorFreeze = false;
    }
}

bool l_initActorHide;
void GZ_hideActors() {
    l_initActorHide = true;
    fopAc_ac_c__stopStatus |= 0x100;
}

void GZ_showActors() {
    if (l_initActorHide) {
        fopAc_ac_c__stopStatus &= ~0x100;
        l_initActorHide = false;
    }
}

void SceneMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(GZ_MAIN_MENU);
        return;
    }

    float current_time = dComIfGs_getTime();

    int current_hour = (int)current_time / 15;
    if (current_hour > 23) {
        current_hour = 0;
    }
    int current_minute = (int)((4.0f * current_time) - current_hour * 60);

    tp_sprintf(lines[TIME_HOURS_INDEX].value, " <%d>", current_hour);
    tp_sprintf(lines[TIME_MINUTES_INDEX].value, " <%d>", current_minute);

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        g_sceneFlags[cursor.y].active = !g_sceneFlags[cursor.y].active;

        switch (cursor.y) {
        case ACTOR_MENU_INDEX:
            GZ_setMenu(GZ_SPAWN_MENU);
            return;
        case ACTOR_LIST_INDEX:
            GZ_setMenu(GZ_ACLIST_MENU);
            return;
        }
    }

    switch (cursor.y) {
    case TIME_HOURS_INDEX:
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            dComIfGs_setTime(current_time + 15.0f);
        } else if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            dComIfGs_setTime(current_time - 15.0f);
        }
        break;
    case TIME_MINUTES_INDEX:
        if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
            dComIfGs_setTime(current_time + 0.25f);
        } else if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
            dComIfGs_setTime(current_time - 0.25f);
        }
        break;
    }

    if (current_time >= 360.0f) {
        dComIfGs_setTime(current_time - 360.0f);
    } else if (current_time < 0) {
        dComIfGs_setTime(current_time + 360.0f);
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
