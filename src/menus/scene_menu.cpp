#include "menus/scene_menu.h"
#include "controller.h"
#include "utils/cursor.h"
#include "utils/lines.h"

#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#define LINES SCENE_AMNT

static Cursor cursor = {0, 0};
bool init_once = false;
using namespace Scene;

SceneItem SceneItems[SCENE_AMNT] = {{FREEZE_ACTOR_INDEX, false},  {HIDE_ACTOR_INDEX, false},
                                    {DISABLE_BG_INDEX, false},    {DISABLE_SFX_INDEX, false},
                                    {FREEZE_CAMERA_INDEX, false}, {HIDE_HUD_INDEX, false},
                                    {FREEZE_TIME_INDEX, false}};

Line lines[LINES] = {
    {"disable bg music", DISABLE_BG_INDEX, "Disables background and enemy music", true,
     &SceneItems[DISABLE_BG_INDEX].active},
    {"disable sfx", DISABLE_SFX_INDEX, "Disables sound effects (item, weather, etc.)", true,
     &SceneItems[DISABLE_SFX_INDEX].active},
    {"freeze actors", FREEZE_ACTOR_INDEX, "Freezes actors", true,
     &SceneItems[FREEZE_ACTOR_INDEX].active},
    {"freeze camera", FREEZE_CAMERA_INDEX, "Locks the camera in place", true,
     &SceneItems[FREEZE_CAMERA_INDEX].active},
    {"hide actors", HIDE_ACTOR_INDEX, "Hides actors", true, &SceneItems[HIDE_ACTOR_INDEX].active},
    {"hide hud", HIDE_HUD_INDEX, "Hides the heads-up display", true,
     &SceneItems[HIDE_HUD_INDEX].active},
    {"freeze time", FREEZE_TIME_INDEX, "Freezes ingame time", true,
     &SceneItems[FREEZE_TIME_INDEX].active},
    {"time (hrs):", TIME_HOURS_INDEX, "The current in-game hour", false},
    {"time (mins):", TIME_MINUTES_INDEX, "The current in-game minutes", false}};

void SceneMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        init_once = false;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    int current_hour = (int)tp_gameInfo.raw_game_time / 15;
    if (current_hour > 23) {
        current_hour = 0;
    }
    int current_minute = (int)((4.0f * tp_gameInfo.raw_game_time) - current_hour * 60);

    tp_sprintf(lines[TIME_HOURS_INDEX].value, " <%d>", current_hour);
    tp_sprintf(lines[TIME_MINUTES_INDEX].value, " <%d>", current_minute);

    Utilities::move_cursor(cursor, LINES, 0, false, false, false, true);
    Utilities::render_lines(lines, cursor.y, LINES);

    if (current_input == SELECTION_BUTTON && a_held == false) {
        SceneItems[cursor.y].active = !SceneItems[cursor.y].active;
    }
    switch (cursor.y) {
    case TIME_HOURS_INDEX: {
        if (button_is_pressed(Controller::DPAD_RIGHT)) {
            tp_gameInfo.raw_game_time += 15.0f;
        } else if (button_is_pressed(Controller::DPAD_LEFT)) {
            tp_gameInfo.raw_game_time -= 15.0f;
        }
        break;
    }
    case TIME_MINUTES_INDEX: {
        if (button_is_pressed(Controller::DPAD_RIGHT)) {
            tp_gameInfo.raw_game_time += 0.25f;
        } else if (button_is_pressed(Controller::DPAD_LEFT)) {
            tp_gameInfo.raw_game_time -= 0.25f;
        }
        break;
    }
    }
    if (tp_gameInfo.raw_game_time >= 360.0f) {
        tp_gameInfo.raw_game_time -= 360.0f;
    }
    if (tp_gameInfo.raw_game_time < 0) {
        tp_gameInfo.raw_game_time += 360.0f;
    }
}
