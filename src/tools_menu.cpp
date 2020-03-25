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
#define LINES 13

static int cursor = 2;
bool g_roll_check_active;
bool g_gorge_active;
bool g_hide_actors;
bool g_freeze_actors;
bool g_lock_camera;
bool g_hide_hud;
int g_tunic_color;
bool init_once = false;
bool g_tunic_color_flag;
bool g_disable_bg_music;
bool g_disable_sfx;

Line lines[LINES] = {
    {"tools", 0, "", false},
    {"", 1, "", false},
    {"input viewer", INPUT_VIEWER_INDEX, "show current inputs (buttons only for now)", true, &iv_visible},
    {"timer", TIMER_INDEX, "frame timer - Z+A to start/stop, Z+B to reset", true, &timer_visible},
    {"roll check", ROLL_INDEX, "see how bad you are at chaining rolls", true, &g_roll_check_active},
    {"gorge void indicator", GORGE_INDEX, "use L + Z to warp to to kak gorge", true, &g_gorge_active},
    {"freeze actors", FREEZE_ACTOR_INDEX, "freezes actors", true, &g_freeze_actors},
    {"hide actors", HIDE_ACTOR_INDEX, "hides actors (except link)", true, &g_hide_actors},
    {"disabled bg music", DISABLE_BG_INDEX,"disables background and enemy music", true, &g_disable_bg_music},
    {"disable sfx", DISABLE_SFX_INDEX,"disables item, weather, etc. sound effects", true, &g_disable_sfx},
    {"freeze camera", FREEZE_CAMERA_INDEX, "locks the camera in place", true, &g_lock_camera},
    {"hide hud", HIDE_HUD_INDEX, "hides the heads up display", true, &g_hide_hud},
    {"link tunic color:", TUNIC_COLOR_INDEX, "changes link's tunic color", false, nullptr, true, {"green", "blue", "red", "orange", "yellow", "black", "white","cycle"}, &g_tunic_color}};

void ToolsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
        tools_visible = false;
        mm_visible = true;
        init_once = false;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

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
                g_freeze_actors = !g_freeze_actors;
                break;
            }
            case HIDE_ACTOR_INDEX: {
                g_hide_actors = !g_hide_actors;
                break;
            }
            case FREEZE_CAMERA_INDEX: {
                g_lock_camera = !g_lock_camera;
                break;
            }
            case HIDE_HUD_INDEX: {
                g_hide_hud = !g_hide_hud;
                break;
            }
            case TUNIC_COLOR_INDEX: {
                if (g_tunic_color < TUNIC_COLOR_COUNT-1) {
                    g_tunic_color++;
                    g_tunic_color_flag = true;
                    break;
                } else {
                    g_tunic_color = GREEN;
                    g_tunic_color_flag = false;
                    break;
                }
            }
            case DISABLE_SFX_INDEX: {
                g_disable_sfx = !g_disable_sfx;
                break;
            }
            case DISABLE_BG_INDEX: {
                g_disable_bg_music = !g_disable_bg_music;
            }
        }
    }
}  // namespace Tools