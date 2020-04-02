#include <stdio.h>
#include <stdint.h>
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
#include "cheats.h"
#include "timer.h"
#include "spawning.h"
#include "flags.h"

static Font Consolas;
_FIFOQueue Queue;

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