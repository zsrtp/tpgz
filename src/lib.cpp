#include <stdio.h>
#include "libtp_c/include/system.h"
#include "libtp_c/include/link.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
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

static Font Consolas;
bool mm_visible = false;
bool prac_visible = false;
bool settings_visible = false;
bool cheats_visible = false;
bool iv_visible = false;
static bool jump_to_quest_log_screen;
static bool was_loading_title_screen = false;
_FIFOQueue Queue;
uint8_t norgor_bytes[2700];

extern "C" {

void init() {
    Consolas = Font(f_Consolas, consolas_bytes);
    jump_to_quest_log_screen = true;
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

    PracticeFile norgor_file;
    memcpy(&norgor_file.qlog_bytes,&norgor_bytes,2700);

    SaveInjector::load_area(norgor_file);
    RollIndicator::run();
    GorgeVoidIndicator::run();
}

void draw() {
    Consolas.setupRendering();
    FIFOQueue::renderItems(Queue, Consolas);
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
    if (iv_visible) {
        InputViewer::render(Consolas);
    }
}
}