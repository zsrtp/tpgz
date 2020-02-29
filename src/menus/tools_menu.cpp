#include "menus/menu.h"
#include "tpgz/input_viewer.h"
#include "tpgz/controller.h"
#include "tpgz/utils.h"
#include "tpgz/timer.h"
#include "tpgz/commands.h"
#include "tpgz/gorge.h"
#include "tpgz/rollcheck.h"
#define LINES 6

static int cursor = 2;
bool g_roll_check_active;
bool g_gorge_active;

Line lines[LINES] = {
    {"tools", 0, "", false},
    {"", 1, "", false},
    {"input viewer", 2, "show current inputs (buttons only for now)", true},
    {"timer", 3, "in game timer (frames only for now). Z+A to start/stop, Z+B to reset", true},
    {"roll check", 4, "see how bad u are at chaining rolls", true},
    {"gorge void", 5, "gorge void practice -- use L + Z to warp to to kak gorge", true}};

void ToolsMenu::render(Font& font) {
    if (button_is_down(Controller::B) && !button_is_held(Controller::B)) {
        tools_visible = false;
        mm_visible = true;
        return;
    };

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor, LINES);

    if (button_is_down(Controller::A) && !button_is_held(Controller::A)) {
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
                break;
            }
            case ROLL_INDEX: {
                g_roll_check_active = !g_roll_check_active;
                break;
            }
        }
    }
}  // namespace Tools