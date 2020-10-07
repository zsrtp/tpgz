#include "menus/scene_menu.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include <stdio.h>
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#define LINES SCENE_AMNT

static Cursor cursor = {0, 0};
bool init_once = false;
using namespace Scene;

SceneItem SceneItems[SCENE_AMNT] = {
    {FREEZE_ACTOR_INDEX, false},
    {HIDE_ACTOR_INDEX, false},
    {DISABLE_BG_INDEX, false},
    {DISABLE_SFX_INDEX, false},
    {FREEZE_CAMERA_INDEX, false},
    {HIDE_HUD_INDEX, false},
    {FREEZE_TIME_INDEX, false}};

Line lines[LINES] = {
    {"disable bg music", DISABLE_BG_INDEX, "Disables background and enemy music", true, &SceneItems[DISABLE_BG_INDEX].active},
    {"disable sfx", DISABLE_SFX_INDEX, "Disables sound effects (item, weather, etc.)", true, &SceneItems[DISABLE_SFX_INDEX].active},
    {"freeze actors", FREEZE_ACTOR_INDEX, "Freezes actors", true, &SceneItems[FREEZE_ACTOR_INDEX].active},
    {"freeze camera", FREEZE_CAMERA_INDEX, "Locks the camera in place", true, &SceneItems[FREEZE_CAMERA_INDEX].active},
    {"hide actors", HIDE_ACTOR_INDEX, "Hides actors", true, &SceneItems[HIDE_ACTOR_INDEX].active},
    {"hide hud", HIDE_HUD_INDEX, "Hides the heads-up display", true, &SceneItems[HIDE_HUD_INDEX].active},
    {"freeze time", FREEZE_TIME_INDEX, "Freezes ingame time", true, &SceneItems[FREEZE_TIME_INDEX].active},
    {"", TIME_HOURS_INDEX, "The current in-game hour", false},
    {"", TIME_MINUTES_INDEX, "The current in-game minutes", false}};

void SceneMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
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

    sprintf(lines[TIME_HOURS_INDEX].line, "time (hrs):        <%d>", current_hour);
    sprintf(lines[TIME_MINUTES_INDEX].line, "time (mins):       <%d>", current_minute);

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.y, LINES, 160.0f);
    
    if (current_input == 256 && a_held == false) {
        SceneItems[cursor.y].active = !SceneItems[cursor.y].active;
    }
    switch (cursor.y) {
        case TIME_HOURS_INDEX: {
            if (button_is_pressed(Controller::DPAD_RIGHT)) {
                tp_gameInfo.raw_game_time += 15.0f;
                if (tp_gameInfo.raw_game_time >= 360.0f) {
                    tp_gameInfo.raw_game_time = (tp_gameInfo.raw_game_time - 360.0f);
                }
            } else if (button_is_pressed(Controller::DPAD_LEFT)) {
                if ((tp_gameInfo.raw_game_time - 15.0f) > 0) {
                    tp_gameInfo.raw_game_time -= 15.0f;
                } else {
                    tp_gameInfo.raw_game_time = (360.0f - tp_gameInfo.raw_game_time);
                }
            }
            break;
        }
        case TIME_MINUTES_INDEX: {
            if (button_is_pressed(Controller::DPAD_RIGHT)) {
                tp_gameInfo.raw_game_time += 0.25f;
                if (tp_gameInfo.raw_game_time >= 360.0f) {
                    tp_gameInfo.raw_game_time = 0.0f;
                }
            } else if (button_is_pressed(Controller::DPAD_LEFT)) {
                if (tp_gameInfo.raw_game_time > 0) {
                    tp_gameInfo.raw_game_time -= 0.25f;
                } else {
                    tp_gameInfo.raw_game_time = 359.75f;
                }
            }
            break;
        }
    }
}
