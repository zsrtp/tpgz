#include "libtp_c/include/actor.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "menus/tools_menu.h"
#include "input_viewer.h"
#include "controller.h"
#include "utils/cursor.hpp"
#include "utils/lines.hpp"
#include "timer.h"
#include "commands.h"
#include "gorge.h"
#include "rollcheck.h"
#include "free_cam.h"
#include "movelink.h"
#define LINES TOOL_AMNT
#define MAX_TUNIC_COLORS 7
using namespace Tools;

static Cursor cursor = {0, 0};
int g_tunic_color;
uint8_t tunic_color_index = 0;
bool init_once = false;
bool g_tunic_color_flag;

Tool ToolItems[TOOL_AMNT] = {
    {RELOAD_AREA_INDEX, false},
    {FAST_BONK_INDEX, false},
    {FAST_MOVEMENT_INDEX, false},
    {GORGE_INDEX, false},
    {INPUT_VIEWER_INDEX, false},
    {LINK_DEBUG_INDEX, false},
    {SAND_INDEX, false},
    {ROLL_INDEX, false},
    {TELEPORT_INDEX, false},
    {TIMER_INDEX, false},
    {LOAD_TIMER_INDEX, false},
    {IGT_TIMER_INDEX, false},
    {FREE_CAM_INDEX, false},
    {MOVE_LINK_INDEX, false}};

Line lines[LINES] = {
    {"area reload", RELOAD_AREA_INDEX, "Use L+R+Start+A to reload current area", true, &ToolItems[RELOAD_AREA_INDEX].active},
    {"fast bonk recovery", FAST_BONK_INDEX, "Reduces bonk animation significantly", true, &ToolItems[FAST_BONK_INDEX].active},
    {"fast movement", FAST_MOVEMENT_INDEX, "Link's movement is much faster", true, &ToolItems[FAST_MOVEMENT_INDEX].active},
    {"gorge checker", GORGE_INDEX, "Use L+Z to warp to Kakariko Gorge", true, &ToolItems[GORGE_INDEX].active},
    {"input viewer", INPUT_VIEWER_INDEX, "Show current inputs (buttons only for now)", true, &ToolItems[INPUT_VIEWER_INDEX].active},
    {"link debug info", LINK_DEBUG_INDEX, "Show Link's position, angle, and speed", true, &ToolItems[LINK_DEBUG_INDEX].active},
    {"no sinking in sand", SAND_INDEX, "Link won't sink in sand", true, &ToolItems[SAND_INDEX].active},
    {"roll checker", ROLL_INDEX, "Frame counter for chaining rolls", true, &ToolItems[ROLL_INDEX].active},
    {"teleport", TELEPORT_INDEX, "dpadUp to set, dpadDown to load", true, &ToolItems[TELEPORT_INDEX].active},
    {"timer", TIMER_INDEX, "Frame timer: Z+A to start/stop, Z+B to reset", true, &ToolItems[TIMER_INDEX].active},
    {"load timer", LOAD_TIMER_INDEX, "Loading zone timer: Z+B to reset", true, &ToolItems[LOAD_TIMER_INDEX].active},
    {"igt timer", IGT_TIMER_INDEX, "In-game time timer: Z+A to start/stop, Z+B to reset", true, &ToolItems[IGT_TIMER_INDEX].active},
    {"free cam", FREE_CAM_INDEX, "Z+A+B to activate, Stick/L/R to move, C-stick to look, Z to speed", true, &ToolItems[FREE_CAM_INDEX].active},
    {"move link", MOVE_LINK_INDEX, "Stick/C-stick to move, C-stick L/R to change angle", true, &ToolItems[MOVE_LINK_INDEX].active},
    {"link tunic color:", TUNIC_COLOR_INDEX, "Changes Link's tunic color", false, nullptr, MAX_TUNIC_COLORS}};

void ToolsMenu::render(Font& font) {
    if (button_is_pressed(Controller::B)) {
		MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        init_once = false;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    ListMember tunic_color_options[MAX_TUNIC_COLORS] = {
        "green",
        "blue",
        "red",
        "orange",
        "yellow",
        "white",
        "cycle"};

    if (cursor.y == TUNIC_COLOR_INDEX) {
        cursor.x = tunic_color_index;
        Utilities::move_cursor(cursor, LINES, MAX_TUNIC_COLORS);
        if (cursor.y == TUNIC_COLOR_INDEX) {
            tunic_color_index = cursor.x;
        }
        g_tunic_color = tunic_color_index;
    } else {
        Utilities::move_cursor(cursor, LINES);
    }
    sprintf(lines[TUNIC_COLOR_INDEX].line, "link tunic color:     <%s>", tunic_color_options[tunic_color_index].member);
    Utilities::render_lines(font, lines, cursor.y, LINES);

    if (current_input == 256 && a_held == false) {
        ToolItems[cursor.y].active = !ToolItems[cursor.y].active;
        if (ToolItems[cursor.y].active) {
            switch (cursor.y) {
                case TIMER_INDEX: {
                    Commands::enable_command(Commands::CMD_TIMER_TOGGLE);
                    Commands::enable_command(Commands::CMD_TIMER_RESET);
                    break;
                }
                case LOAD_TIMER_INDEX: {
                    Commands::enable_command(Commands::CMD_TIMER_RESET);
                    break;
                }
                case IGT_TIMER_INDEX: {
                    Commands::enable_command(Commands::CMD_TIMER_TOGGLE);
                    Commands::enable_command(Commands::CMD_TIMER_RESET);
                    break;
                }
                case GORGE_INDEX: {
                    if (ToolItems[GORGE_INDEX].active) {
                        Commands::enable_command(Commands::CMD_GORGE_VOID);
                    } else {
                        Commands::disable_command(Commands::CMD_GORGE_VOID);
                    }
                    break;
                }
                case TELEPORT_INDEX: {
                    Commands::enable_command(Commands::CMD_STORE_POSITION);
                    Commands::enable_command(Commands::CMD_LOAD_POSITION);
                    break;
                }
                case RELOAD_AREA_INDEX: {
                    Commands::enable_command(Commands::CMD_RELOAD_AREA);
                    break;
                }
                case FAST_MOVEMENT_INDEX: {
                    tp_link_human_frontroll.roll_factor = 3.0f;
                    tp_link_human_swim.swim_up_speed = 50;
                    tp_link_human_swim.back_swim_speed = 50;
                    tp_link_human_swim.side_swim_speed = 50;
                    tp_link_human_swim.dash_swim_max_speed = 50;
                    tp_link_human_swim.forward_swim_speed = 50;
                    tp_link_human_swim.ib_swim_speed = 50;
                    tp_link_human_swim.sinking_speed = -50;
                    tp_link_human_swim.initial_sinking_speed = -50;
                    tp_link_wolf_general.dash_initial_speed_large_area = 100;
                    tp_link_wolf_general.dash_speed_large_area = 100;
                    tp_link_wolf_general.dash_initial_speed_small_area = 70;
                    tp_link_wolf_general.dash_speed_small_area = 70;
                    tp_link_wolf_swim.dash_swim_speed = 50;
                    tp_link_wolf_swim.swim_speed = 50;
                    break;
                }
                case FAST_BONK_INDEX: {
                    tp_link_human_frontroll.bonk_recoil_anim_speed = 50.0f;
                    tp_link_human_frontroll.bonk_recovery_anim_factor = 0.0f;
                    break;
                }
                case SAND_INDEX: {
                    tp_zelAudio.link_debug_ptr->sand_height_lost = 0;
                    break;
                }
                case FREE_CAM_INDEX: {
                    Commands::enable_command(Commands::CMD_FREE_CAM);
                    free_cam_active = false;
                    break;
                }
                case MOVE_LINK_INDEX: {
                    move_link_active = true;
				}
            }
        } else {
            switch (cursor.y) {
                case TELEPORT_INDEX: {
                    Commands::disable_command(Commands::CMD_STORE_POSITION);
                    Commands::disable_command(Commands::CMD_LOAD_POSITION);
                    break;
                }
                case RELOAD_AREA_INDEX: {
                    Commands::disable_command(Commands::CMD_RELOAD_AREA);
                    break;
                }
                case FAST_MOVEMENT_INDEX: {
                    tp_link_human_frontroll.roll_factor = 1.3;
                    tp_link_human_swim.swim_up_speed = 12;
                    tp_link_human_swim.forward_swim_speed = 8;
                    tp_link_human_swim.back_swim_speed = 6;
                    tp_link_human_swim.side_swim_speed = 8;
                    tp_link_human_swim.dash_swim_max_speed = 13;
                    tp_link_human_swim.ib_swim_speed = 8;
                    tp_link_human_swim.sinking_speed = -20;
                    tp_link_human_swim.initial_sinking_speed = -0.699999988;
                    tp_link_wolf_general.dash_initial_speed_large_area = 65;
                    tp_link_wolf_general.dash_speed_large_area = 45;
                    tp_link_wolf_general.dash_initial_speed_small_area = 35;
                    tp_link_wolf_general.dash_speed_small_area = 33;
                    tp_link_wolf_swim.dash_swim_speed = 20;
                    tp_link_wolf_swim.swim_speed = 9;
                    break;
                }
                case FAST_BONK_INDEX: {
                    tp_link_human_frontroll.bonk_recoil_anim_speed = 3.0f;
                    tp_link_human_frontroll.bonk_recovery_anim_factor = 0.800000012f;
                    break;
                }
                case FREE_CAM_INDEX: {
                    Commands::disable_command(Commands::CMD_FREE_CAM);
                    free_cam_active = false;
                    break;
                }
                case MOVE_LINK_INDEX: {
                    move_link_active = false;
                }
            }
        }
    }
}  // namespace Tools