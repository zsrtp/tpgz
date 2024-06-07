#include "menus/menu_scene/include/scene_menu.h"
#include <cstdio>
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/d/meter/d_meter_HIO.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

KEEP_FUNC SceneMenu::SceneMenu(Cursor& cursor)
    : Menu(cursor), lines{
                        {"disable bg music", DISABLE_BG_INDEX,
                         "Disables background and enemy music", true,
                         [](){return g_sceneFlags[DISABLE_BG_INDEX].active;}},
                        {"disable sfx", DISABLE_SFX_INDEX, "Disables sound effects", true,
                         [](){return g_sceneFlags[DISABLE_SFX_INDEX].active;}},
                        {"freeze actors", FREEZE_ACTOR_INDEX, "Freezes actors", true,
                         [](){return g_sceneFlags[FREEZE_ACTOR_INDEX].active;}},
                        {"freeze camera", FREEZE_CAMERA_INDEX, "Locks the camera in place", true,
                         [](){return g_sceneFlags[FREEZE_CAMERA_INDEX].active;}},
                        {"hide actors", HIDE_ACTOR_INDEX, "Hides actors", true,
                         [](){return g_sceneFlags[HIDE_ACTOR_INDEX].active;}},
                        {"hide hud", HIDE_HUD_INDEX, "Hides the heads-up display", true,
                         [](){return g_sceneFlags[HIDE_HUD_INDEX].active;}},
                        {"freeze time", FREEZE_TIME_INDEX, "Freezes ingame time", true,
                         [](){return g_sceneFlags[FREEZE_TIME_INDEX].active;}},
                        {"time (hrs):", TIME_HOURS_INDEX, "The current in-game hour", false},
                        {"time (mins):", TIME_MINUTES_INDEX, "The current in-game minutes", false},
                        {"actor spawner", ACTOR_MENU_INDEX, "Spawn Actors at current position",
                         false},
                        {"actor list", ACTOR_LIST_INDEX, "Display info from the actor list", false},
                        {"collision viewer", COLLISION_VIEW_INDEX, "Change Collision Viewer settings", false},
                        {"projection viewer", PROJECTION_VIEW_INDEX, "Change Projection Viewer settings", false},
                        {"trigger viewer", TRIGGER_VIEW_INDEX, "Change Trigger Viewer settings", false},
                    } {}

SceneMenu::~SceneMenu() {}

void SceneMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        g_menuMgr->pop();
        return;
    }

    float current_time = dComIfGs_getTime();

    int current_hour = (int)current_time / 15;
    if (current_hour > 23) {
        current_hour = 0;
    }
    int current_minute = (int)((4.0f * current_time) - current_hour * 60);

    lines[TIME_HOURS_INDEX].printf(" <%d>", current_hour);
    lines[TIME_MINUTES_INDEX].printf(" <%d>", current_minute);

    if (GZ_getButtonTrig(SELECTION_BUTTON)) {
        g_sceneFlags[cursor.y].active = !g_sceneFlags[cursor.y].active;

        switch (cursor.y) {
        case ACTOR_MENU_INDEX:
            g_menuMgr->push(MN_ACTOR_SPAWNER_INDEX);
            return;
        case ACTOR_LIST_INDEX:
            g_menuMgr->push(MN_ACTOR_LIST_INDEX);
            return;
        case COLLISION_VIEW_INDEX:
            g_menuMgr->push(MN_COLLISION_VIEW_INDEX);
            return;
        // case PROJECTION_VIEW_INDEX:
        //     g_menuMgr->push(MN_PROJECTION_VIEW_INDEX);
        //     return;
        case TRIGGER_VIEW_INDEX:
            g_menuMgr->push(MN_TRIGGER_VIEW_INDEX);
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
