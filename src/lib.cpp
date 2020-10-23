#include "libtp_c/include/controller.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/system.h"
#include "utils/hook.h"
#include "utils/link.hpp"
#include "utils/memory.hpp"
#include "utils/card.hpp"
#include "utils/texture.h"
#include "fifo_queue.h"
#include "font.h"
#include "controller.h"
#include "menu.h"
#include "menus/main_menu.h"
#include "menus/position_settings_menu.h"
#include "menus/settings_menu.h"
#include "menus/tools_menu.h"
#include "gz_flags.h"
#include "input_viewer.h"
#include "utils/draw.h"
#include "timer.h"
#include "free_cam.h"
#include "frame_advance.h"
#include "movelink.h"

_FIFOQueue Queue;
bool card_load = true;
Texture gzIconTex;
// bool inFrameAdvance = false;

// #define tp_padread_addr 0x802e08e4
// typedef void (*tp_padread_t)(void);
// #define tp_padread ((tp_padread_t)tp_padread_addr)

extern "C" {

#define main_tampoline ((void (*)(void))0x803737b4)
void apply_lib_hooks() {
    Hook::apply_hooks();
    main_tampoline();
}

void init() {
    Font::load_font("tpgz/fonts/consola.fnt");
    PosSettingsMenu::initDefaults();
    Draw::init();
    fifo_visible = true;
}

void game_loop() {
    using namespace Controller::Pad;

    // Button combo to bypass the automatic loading of the save file
    // in case of crash cause by the load.
    if (tp_mPadStatus.sval == (L | R | B) && card_load) {
        card_load = false;
    }

    // check and load gz settings card if found
    Utilities::load_gz_card(card_load);

    if (tp_mPadStatus.sval == (L | R | DPAD_DOWN) && tp_fopScnRq.isLoading != 1 && !move_link_active) {
        MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        fifo_visible = false;
    }
    if (tp_fopScnRq.isLoading == 1) {
        MenuRendering::close_active_menus();
        move_link_active = false;
    }

    GZFlags::apply_active_flags();
    FreeCam::handle_free_cam();
    FrameAdvance::handle_frame_advance();
    MoveLink::move_link();

    // if (tp_mPadStatus.sval == 0x10) {
    //     inFrameAdvance = true;
    // }

    // tp_osReport("fa: %d", inFrameAdvance);
    
    
    // if (inFrameAdvance) {
    //     do {
            
    //         tp_osReport("in fa loop!");
    //         tp_padread();
    //         tp_osReport("ok %d", tp_mPadStatus.sval);

    //         if (tp_mPadStatus.sval == 0x10) {
    //             inFrameAdvance = false;
    //         }
    //     } while (inFrameAdvance);
    // }
}

void draw() {
    setupRendering();
    //Consolas.setupRendering();
    if(MenuRendering::is_menu_open()){
        Font::gz_renderChars("tpgz v0.1a", sprite_offsets[MENU_INDEX].x + 35.0f, 25.0f, cursor_rgba, g_drop_shadows);

        if (gzIconTex.loadCode == TexCode::TEX_UNLOADED) {
            load_texture("tpgz/tex/tpgz.tex", &gzIconTex);
            if (gzIconTex.loadCode != TexCode::TEX_OK) {
                tp_osReport("Could not load TPGZ's icon texture (Code: %d)", gzIconTex.loadCode);
            }
        }

        if (gzIconTex.loadCode == TexCode::TEX_OK) {
            Draw::draw_rect(0xFFFFFFFF, {sprite_offsets[MENU_INDEX].x, 5.0f}, {30, 30}, &gzIconTex._texObj);
        }
    }
    if (fifo_visible) {
        FIFOQueue::renderItems(Queue);
    }
    if (ToolItems[Tools::LINK_DEBUG_INDEX].active) {
        Utilities::show_link_debug_info();
    }
    if (ToolItems[Tools::INPUT_VIEWER_INDEX].active) {
        InputViewer::render();
    }
    if (ToolItems[Tools::TIMER_INDEX].active || ToolItems[Tools::LOAD_TIMER_INDEX].active || ToolItems[Tools::IGT_TIMER_INDEX].active) {
        Timer::render();
    }
    if (move_link_active) {
        MoveLink::render_info_input();
	}
    MenuRendering::render_active_menus();
    Utilities::render_active_watches();
}
}