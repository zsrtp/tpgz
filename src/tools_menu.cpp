#include "libtp_c/include/actor.h"
#include "libtp_c/include/tp.h"
#include "menu.h"
#include "input_viewer.h"
#include "controller.h"
#include "utils.h"
#include "timer.h"
#include "commands.h"
#include "gorge.h"
#include "rollcheck.h"
#define LINES 9

static int cursor = 2;
bool g_roll_check_active;
bool g_gorge_active;
bool init_once = false;

Line lines[LINES] = {
    {"tools", 0, "", false},
    {"", 1, "", false},
    {"input viewer", INPUT_VIEWER_INDEX, "show current inputs (buttons only for now)", true, &iv_visible},
    {"timer", TIMER_INDEX, "frame timer - Z+A to start/stop, Z+B to reset", true, &timer_visible},
    {"roll check", ROLL_INDEX, "see how bad you are at chaining rolls", true, &g_roll_check_active},
    {"gorge void indicator", GORGE_INDEX, "use L + Z to warp to to kak gorge", true, &g_gorge_active},
    {"freeze actors", FREEZE_ACTOR_INDEX, "freezes actors", true, &tp_actor.freeze},
    {"hide actors", HIDE_ACTOR_INDEX, "hides actors (except link)", true, &tp_stopstatus.hide_actors},
    {"freeze camera", FREEZE_CAMERA_INDEX, "locks the camera in place", true, &tp_gameInfo.lock_camera}};

void ToolsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        tools_visible = false;
        mm_visible = true;
        init_once = false;
        return;
    };

    if (!init_once) {current_input = 0;init_once = true;}

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor, LINES);

    if (current_input == 256 && a_held == false) {
        switch (cursor) {
            case INPUT_VIEWER_INDEX: {
                iv_visible = !iv_visible;
                break;
            }
            case TIMER_INDEX: {
                timer_visible = !timer_visible;
                Commands::enable_command(Commands::TIMER_TOGGLE);
                Commands::enable_command(Commands::TIMER_RESET);
                break;
            }
            case GORGE_INDEX: {
                g_gorge_active = !g_gorge_active;
                if (g_gorge_active) {
                    Commands::enable_command(Commands::GORGE_VOID);
                } else {
                    Commands::disable_command(Commands::GORGE_VOID);
                }
                break;
            }
            case ROLL_INDEX: {
                g_roll_check_active = !g_roll_check_active;
                break;
            }
            case FREEZE_ACTOR_INDEX: {
                tp_actor.freeze = !tp_actor.freeze;
                break;
            }
            case HIDE_ACTOR_INDEX: {
                tp_stopstatus.hide_actors = !tp_stopstatus.hide_actors;
                break;
            }
            case FREEZE_CAMERA_INDEX: {
                tp_gameInfo.lock_camera = !tp_gameInfo.lock_camera;
                break;
            }
        }
    }
}  // namespace Tools