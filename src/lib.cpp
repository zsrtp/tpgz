#include <stdio.h>
#include "utils.h"
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
#include "log.h"
#include "save_injector.h"
#include "commands.h"
#include "timer.h"
#include "spawning.h"
#include "flags.h"

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

    if (tp_mPadStatus.sval == (L | R | DPAD_DOWN)) {
        mm_visible = true;
        fifo_visible = false;
    }

    Flags::apply_active_flags();
}

void draw() {
    Consolas.setupRendering();
    if (fifo_visible) {
        FIFOQueue::renderItems(Queue, Consolas);
    }
    MenuRendering::render_active_menus(Consolas);
}
}