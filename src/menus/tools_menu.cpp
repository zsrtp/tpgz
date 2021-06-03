#include "menus/tools_menu.h"
#include "commands.h"
#include "controller.h"
#include "free_cam.h"
#include "gorge.h"
#ifdef WII_PLATFORM
#include "bit.h"
#endif
#include "input_viewer.h"
#include "libtp_c/include/msl_c/string.h"
#include "movelink.h"
#include "rollcheck.h"
#include "timer.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#define LINES TOOL_AMNT
#define MAX_TUNIC_COLORS 7
using namespace Tools;

static Cursor cursor = {0, 0};
int g_tunic_color;
uint8_t tunic_color_index = 0;
bool init_once = false;
bool g_tunic_color_flag;

Tool ToolItems[TOOL_AMNT] = {
    {RELOAD_AREA_INDEX, false},  {FAST_BONK_INDEX, false},  {FAST_MOVEMENT_INDEX, false},
    {GORGE_INDEX, false},
#ifdef WII_PLATFORM
    {BIT_INDEX, false},
#endif
    {COROTD_INDEX, false}, {INPUT_VIEWER_INDEX, false}, {LINK_DEBUG_INDEX, false}, {SAND_INDEX, false},
    {ROLL_INDEX, false},         {TELEPORT_INDEX, false},   {TURBO_MODE_INDEX, false},
    {TIMER_INDEX, false},        {LOAD_TIMER_INDEX, false}, {IGT_TIMER_INDEX, false},
    {FREE_CAM_INDEX, false},     {MOVE_LINK_INDEX, false}};

Line lines[LINES] = {
    {"area reload", RELOAD_AREA_INDEX, "Use " RELOAD_AREA_TEXT " to reload current area", true,
     &ToolItems[RELOAD_AREA_INDEX].active},
    {"fast bonk recovery", FAST_BONK_INDEX, "Reduces bonk animation significantly", true,
     &ToolItems[FAST_BONK_INDEX].active},
    {"fast movement", FAST_MOVEMENT_INDEX, "Link's movement is much faster", true,
     &ToolItems[FAST_MOVEMENT_INDEX].active},
    {"gorge checker", GORGE_INDEX, "Use " GORGE_VOID_TEXT " to warp to Kakariko Gorge", true,
     &ToolItems[GORGE_INDEX].active},
#ifdef WII_PLATFORM
    {"bit checker", BIT_INDEX, "Use " BACK_IN_TIME_TEXT " to warp to Ordon Bridge", true,
     &ToolItems[BIT_INDEX].active},
#endif
    {"coro td checker", COROTD_INDEX, "Show frame info when doing coro td", true,
     &ToolItems[COROTD_INDEX].active},
    {"input viewer", INPUT_VIEWER_INDEX, "Show current inputs", true,
     &ToolItems[INPUT_VIEWER_INDEX].active},
    {"link debug info", LINK_DEBUG_INDEX, "Show Link's position, angle, and speed", true,
     &ToolItems[LINK_DEBUG_INDEX].active},
    {"no sinking in sand", SAND_INDEX, "Link won't sink in sand", true,
     &ToolItems[SAND_INDEX].active},
    {"roll checker", ROLL_INDEX, "Frame counter for chaining rolls", true,
     &ToolItems[ROLL_INDEX].active},
    {"teleport", TELEPORT_INDEX, STORE_POSITION_TEXT " to set, " LOAD_POSITION_TEXT " to load",
     true, &ToolItems[TELEPORT_INDEX].active},
    {"turbo mode", TURBO_MODE_INDEX, "Simulates turbo controller inputs", true,
     &ToolItems[TURBO_MODE_INDEX].active},
    {"timer", TIMER_INDEX,
     "Frame timer: " TIMER_TOGGLE_TEXT " to start/stop, " TIMER_RESET_TEXT " to reset", true,
     &ToolItems[TIMER_INDEX].active},
    {"load timer", LOAD_TIMER_INDEX, "Loading zone timer: " TIMER_RESET_TEXT " to reset", true,
     &ToolItems[LOAD_TIMER_INDEX].active},
    {"igt timer", IGT_TIMER_INDEX,
     "In-game time timer: " TIMER_TOGGLE_TEXT " to start/stop, " TIMER_RESET_TEXT " to reset", true,
     &ToolItems[IGT_TIMER_INDEX].active},
    {"free cam", FREE_CAM_INDEX,
     FREE_CAM_TEXT " to activate, " FREE_CAM_MOVEMENT_TEXT " to move, " FREE_CAM_VIEW_TEXT
                   " to view, Z to speed",
     true, &ToolItems[FREE_CAM_INDEX].active},
    {"move link", MOVE_LINK_INDEX,
     MOVE_LINK_TEXT " to activate. " MOVE_LINK_MOVEMENT_TEXT " to move, " MOVE_LINK_ANGLE_TEXT
                    " to change angle",
     true, &ToolItems[MOVE_LINK_INDEX].active},
    {"link tunic color:", TUNIC_COLOR_INDEX, "Changes Link's tunic color", false, nullptr,
     MAX_TUNIC_COLORS}};

void ToolsMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        init_once = false;
        return;
    };

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    ListMember tunic_color_options[MAX_TUNIC_COLORS] = {"green",  "blue",  "red",  "orange",
                                                        "yellow", "white", "cycle"};

    if (cursor.y == TUNIC_COLOR_INDEX) {
        cursor.x = tunic_color_index;
        Utilities::move_cursor(cursor, LINES, MAX_TUNIC_COLORS, false, false, false, true);
        if (cursor.y == TUNIC_COLOR_INDEX) {
            tunic_color_index = cursor.x;
        }
        g_tunic_color = tunic_color_index;
    } else {
        Utilities::move_cursor(cursor, LINES, 0, false, false, false, true);
    }
    tp_sprintf(lines[TUNIC_COLOR_INDEX].value, " <%s>",
               tunic_color_options[tunic_color_index].member);
    Utilities::render_lines(lines, cursor.y, LINES);

    if (current_input == SELECTION_BUTTON && a_held == false) {
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
                Commands::enable_command(Commands::CMD_GORGE_VOID);
                break;
            }
#ifdef WII_PLATFORM
            case BIT_INDEX: {
                Commands::enable_command(Commands::CMD_BIT);
                break;
            }
#endif
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
                if (g_dComIfG_gameInfo.play.mPlayer != nullptr) {
                    dComIfGp_getPlayer()->field_0x2ba8 = 0;
                }
                break;
            }
            case FREE_CAM_INDEX: {
                Commands::enable_command(Commands::CMD_FREE_CAM);
                free_cam_active = false;
                break;
            }
            case MOVE_LINK_INDEX: {
                Commands::enable_command(Commands::CMD_MOVE_LINK);
                move_link_active = false;
                break;
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
                Commands::disable_command(Commands::CMD_MOVE_LINK);
                move_link_active = false;
                break;
            }
            case GORGE_INDEX: {
                Commands::disable_command(Commands::CMD_GORGE_VOID);
                break;
            }
#ifdef WII_PLATFORM
            case BIT_INDEX: {
                Commands::disable_command(Commands::CMD_BIT);
                break;
            }
#endif
            }
        }
    }
}  // namespace Tools