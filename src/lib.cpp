#include <stdio.h>
//#include "save_files/norgor.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/link.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "save_files/norgor.h"
#include "controller.h"
#include "fonts/consolas.h"
#include "font.h"
#include "fifo_queue.h"
#include "menu.h"
#include "input_viewer.h"
#include "gorge.h"
#include "log.h"
#include "rollcheck.h"
#include "save_injector.h"
#include "utils.h"
#include "commands.h"
#include "timer.h"

static Font Consolas;
bool mm_visible = false;
bool prac_visible = false;
bool settings_visible = false;
bool cheats_visible = false;
bool iv_visible = false;
bool timer_visible = false;
bool tools_visible = false;
bool fifo_visible = true;
static bool jump_to_quest_log_screen;
static bool was_loading_title_screen = false;
_FIFOQueue Queue;
PracticeFile practice_file;



extern "C" {

void init() {
    Consolas = Font(f_Consolas, consolas_bytes);
    //jump_to_quest_log_screen = true;
}

void game_loop() {
    using namespace Controller::Pad;
    // Log log;
    // char buf[10];

    // if (was_loading_title_screen) {
    //     log.PrintLog("setting next load", DEBUG);
    //     tp_titleScreenInfo.title_screen_info->trigger_on_next_load = 13;
    // }

    // if (tp_fopScnRq.isLoading == 1 && tp_titleScreenInfo.title_screen_info->trigger_on_next_load == 12) {
    //     was_loading_title_screen = true;
    //     tp_fopScnRq.isLoading = 0;
    // }

    if (tp_mPadStatus.sval == (L | R | DPAD_DOWN)) {
        mm_visible = true;
    }

    memcpy(&practice_file.qlog_bytes,&norgor_bytes,2700);
    practice_file.position = {173.71f,-186.52f,-3633.71f};
    practice_file.angle = 46568;
    SaveInjector::load_area();
    RollIndicator::run();
    GorgeVoidIndicator::run();
    if (reload_area_flag) {
        Utilities::trigger_load(AreaReload);
    }

    if (g_reload_temp_flags) {
        Utilities::trigger_load(SaveTempFlags);
    }
}

void draw() {
    Consolas.setupRendering();
    if (fifo_visible) {
        FIFOQueue::renderItems(Queue, Consolas);
    }
    if (mm_visible) {
        MainMenu::render(Consolas);
    }
    if (prac_visible) {
        PracticeMenu::render(Consolas);
    }
    if (cheats_visible) {
        CheatsMenu::render(Consolas);
    }
    if (settings_visible) {
        SettingsMenu::render(Consolas);
    }
    if (tools_visible) {
        ToolsMenu::render(Consolas);
    }
    if (iv_visible) {
        InputViewer::render(Consolas);
    }
    if (timer_visible) {
        Timer::render(Consolas);
    }
}
}