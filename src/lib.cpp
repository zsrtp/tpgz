#include "libtp_c/include/controller.h"
#include "libtp_c/include/tp.h"
#include "utils/link.hpp"
#include "fonts/consolas.h"
#include "fifo_queue.h"
#include "font.h"
#include "menu.h"
#include "gz_flags.h"

_FIFOQueue Queue;
bool card_load = true;
Font default_font;

extern "C" {

void init() {
    default_font = Font(f_Consolas, consolas_bytes);
}

void game_loop() {
    using namespace Controller::Pad;
    
    // check and load gz settings card if found
    // Utilities::load_gz_card(card_load);

    if (tp_mPadStatus.sval == (L | R | DPAD_DOWN) && tp_fopScnRq.isLoading != 1) {
        mm_visible = true;
        fifo_visible = false;
    }
    if (tp_fopScnRq.isLoading == 1) {
        MenuRendering::close_active_menus();
    }

    GZFlags::apply_active_flags();
}

void draw() {
    default_font.setupRendering();
    //Consolas.setupRendering();
    if (fifo_visible) {
        FIFOQueue::renderItems(Queue, default_font);
    }
    if (ToolItems[Tools::LINK_DEBUG_INDEX].active) {
        Utilities::show_link_debug_info(default_font);
    }
    MenuRendering::render_active_menus(default_font);
}
}