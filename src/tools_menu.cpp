#include "libtp_c/include/actor.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "menu.h"
#include "input_viewer.h"
#include "controller.h"
#include "utils.h"
#include "timer.h"
#include "commands.h"
#include "gorge.h"
#include "rollcheck.h"
#define LINES TOOL_AMNT
using namespace Tools;

static Cursor cursor = {0, 0};
int g_tunic_color;
bool init_once = false;
bool g_tunic_color_flag;
bool tools_visible;

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
    {TIMER_INDEX, false}};

TunicColor TunicColors[TUNIC_COLOR_AMNT] = {
    {"green", false},
    {"blue", false},
    {"red", false},
    {"orange", false},
    {"yellow", false},
    {"white", false},
    {"cycle", false}};

Line lines[LINES] = {
    {"area reload", RELOAD_AREA_INDEX, "use L+R+Start+A to reload current area", true, &ToolItems[RELOAD_AREA_INDEX].active},
    {"fast bonk recovery", FAST_BONK_INDEX, "reduces bonk animation significantly", true, &ToolItems[FAST_BONK_INDEX].active},
    {"fast movement", FAST_MOVEMENT_INDEX, "link's movement is much faster", true, &ToolItems[FAST_MOVEMENT_INDEX].active},
    {"gorge checker", GORGE_INDEX, "use L + Z to warp to to kak gorge", true, &ToolItems[GORGE_INDEX].active},
    {"input viewer", INPUT_VIEWER_INDEX, "show current inputs (buttons only for now)", true, &ToolItems[INPUT_VIEWER_INDEX].active},
    {"link debug info", LINK_DEBUG_INDEX, "show link's position, angle and speed", true, &ToolItems[LINK_DEBUG_INDEX].active},
    {"no sinking in sand", SAND_INDEX, "link won't sink in sand", true, &ToolItems[SAND_INDEX].active},
    {"roll checker", ROLL_INDEX, "frame counter for chaining rolls", true, &ToolItems[ROLL_INDEX].active},
    {"teleport", TELEPORT_INDEX, "dpad+up to set, dpad+down to load ", true, &ToolItems[TELEPORT_INDEX].active},
    {"timer", TIMER_INDEX, "frame timer - Z+A to start/stop, Z+B to reset", true, &ToolItems[TIMER_INDEX].active},
    {"link tunic color:   ", TUNIC_COLOR_INDEX, "changes link's tunic color", false, nullptr, true, {"green", "blue", "red", "orange", "yellow", "white", "cycle"}, &g_tunic_color}};

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

    // for (int i = 0; i < TUNIC_COLORS; i++) {
    //     if (TunicColors[i].active) {
    //         sprintf(lines[TUNIC_COLOR_INDEX].line, "link tunic color: <%s>", TunicColors[i].name);
    //     }
    // }

    Utilities::move_cursor(cursor, LINES);
    Utilities::render_lines(font, lines, cursor.x, LINES);

    if (current_input == 256 && a_held == false) {
        ToolItems[cursor.x].active = !ToolItems[cursor.x].active;
        if (ToolItems[cursor.x].active) {
            switch (cursor.x) {
                case TIMER_INDEX: {
                    Commands::enable_command(Commands::TIMER_TOGGLE);
                    Commands::enable_command(Commands::TIMER_RESET);
                    break;
                }
                case GORGE_INDEX: {
                    if (ToolItems[GORGE_INDEX].active) {
                        Commands::enable_command(Commands::GORGE_VOID);
                    } else {
                        Commands::disable_command(Commands::GORGE_VOID);
                    }
                    break;
                }
                case TELEPORT_INDEX: {
                    Commands::enable_command(Commands::STORE_POSITION);
                    Commands::enable_command(Commands::LOAD_POSITION);
                    break;
                }
                case RELOAD_AREA_INDEX: {
                    Commands::enable_command(Commands::RELOAD_AREA);
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
                case TUNIC_COLOR_INDEX: {
                    if (g_tunic_color < TUNIC_COLOR_COUNT - 1) {
                        g_tunic_color++;
                        g_tunic_color_flag = true;
                        break;
                    } else {
                        g_tunic_color = GREEN;
                        g_tunic_color_flag = false;
                        break;
                    }
                    // for (int i = 0; i < TUNIC_COLORS; i++) {
                    //     if (TunicColors[i].active) {
                    //         TunicColors[i].active = false;
                    //         if (i == TUNIC_COLORS - 1) {
                    //             TunicColors[0].active = true;
                    //         } else {
                    //             TunicColors[i+1].active = true;
                    //         }
                    //     }
                    // }
                    
                    //TunicColors[cursor.x+1].active = true;
                }
            }
        } else {
            switch (cursor.x) {
                case TELEPORT_INDEX: {
                    Commands::disable_command(Commands::STORE_POSITION);
                    Commands::disable_command(Commands::LOAD_POSITION);
                    break;
                }
                case RELOAD_AREA_INDEX: {
                    Commands::disable_command(Commands::RELOAD_AREA);
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
            }
        }
    }
}  // namespace Tools