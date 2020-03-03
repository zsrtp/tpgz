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
#include "utils.h"
#include "commands.h"
#include "timer.h"
#include "spawning.h"

static Font Consolas;
bool mm_visible = false;
bool prac_visible = false;
bool settings_visible = false;
bool cheats_visible = false;
bool iv_visible = false;
bool timer_visible = false;
bool tools_visible = false;
bool fifo_visible = true;
bool item_wheel_visible = false;
bool pause_visible = false;
bool inventory_visible = false;
bool memory_visible = false;
bool warping_visible = false;
bool inject_save_flag = false;
// static bool jump_to_quest_log_screen;
// static bool was_loading_title_screen = false;
_FIFOQueue Queue;
PracticeFile practice_file;

extern "C" {

void init() {
    Consolas = Font(f_Consolas, consolas_bytes);
}

void game_loop() {
    using namespace Controller::Pad;

    if (tp_mPadStatus.sval == (Y | X)) {
        tp_osReport("g spawn");
        spawn("Grass");
    }

    if (tp_mPadStatus.sval == (L | R | DPAD_DOWN)) {
        mm_visible = true;
        fifo_visible = false;
    }

    if (inject_save_flag) {
        Utilities::trigger_load(SaveInjection);
    }
    RollIndicator::run();
    GorgeVoidIndicator::run();
    if (reload_area_flag) {
        Utilities::trigger_load(AreaReload);
    }
    if (g_reset_temp_flags) {
        Utilities::trigger_load(SaveTempFlags);
    }
    if (inject_gorge_flag) {
        Utilities::trigger_load(Gorge);
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
    if (inventory_visible) {
        InventoryMenu::render(Consolas);
    }
    if (pause_visible) {
        PauseMenu::render(Consolas);
    }
    if (item_wheel_visible) {
        ItemWheelMenu::render(Consolas);
    }
    if (warping_visible) {
        WarpingMenu::render(Consolas);
    }
    if (memory_visible) {
        MemoryMenu::render(Consolas);
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