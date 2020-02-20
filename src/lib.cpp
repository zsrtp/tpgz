#include <stdio.h>
#include "libtp_c/include/system.h"
#include "libtp_c/include/link.h"
#include "libtp_c/include/controller.h"
#include "controller.h"
#include "fonts/consolas.h"
#include "font.h"
#include "fifo_queue.h"
#include "menu.h"
#include "input_viewer.h"
#include "gorge.h"
#include "rollcheck.h"

static Font Consolas;
bool mm_visible = false;
bool prac_visible = false;
bool iv_visible = false;
_FIFOQueue Queue;

extern "C" {

void init() {
    Consolas = Font(f_Consolas, consolas_bytes);
}

void game_loop() {
    using namespace Controller::Pad;
    if (tp_mPadStatus.sval == (L | R | DPAD_DOWN)) {
        mm_visible = true;
    }

    GorgeVoidIndicator::run();
    RollIndicator::run();

    // TODO
    // if (Settings::showInputViewer()) {
    //     iv_visible = true;
    // }
}

void draw() {
    Consolas.setupRendering();
    FIFOQueue::renderItems(Queue, Consolas);
    if (mm_visible == true) {
        MainMenu::render(Consolas);
    }
    if (prac_visible == true) {
        PracticeMenu::render(Consolas);
    }
    InputViewer::render(Consolas);
}
}