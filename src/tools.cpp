#include "menu.h"
#include "input_viewer.h"
#include "controller.h"
#include "utils.h"
#include "timer.h"
#include "commands.h"
#define LINES 4

static int cursor = 2;

    Line lines[LINES] = {
        {"tools", 0, "", false},
        {"", 1, "", false},
        {"input viewer", 2, "show current inputs (buttons only for now)", true},
        {"timer", 3, "in game timer (frames only for now). Z+A to start/stop, Z+B to reset", true}};

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
            }
        }
    }  // namespace Tools