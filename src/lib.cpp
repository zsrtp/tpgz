#include "controller.h"
#include "fifo_queue.h"
#include "font.h"
#include "free_cam.h"
#include "gz_flags.h"
#include "input_viewer.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/tp.h"
#include "menu.h"
#include "menus/main_menu.h"
#include "menus/position_settings_menu.h"
#include "menus/settings_menu.h"
#include "menus/tools_menu.h"
#include "movelink.h"
#include "timer.h"
#include "utils/card.h"
#include "utils/draw.h"
#include "utils/hook.h"
#include "utils/link.h"
#include "utils/loading.h"
#include "utils/memory.h"
#include "utils/texture.h"

_FIFOQueue Queue;
bool card_load = true;
Texture gzIconTex;
bool last_frame_was_loading = false;

extern "C" {

#if (GCN_NTSCU)
#define main_tampoline ((void (*)(void))0x803737b4)
#endif
#if (GCN_PAL)
#define main_tampoline ((void (*)(void))0x803745e4)
#endif
#if (GCN_NTSCJ)
#define main_tampoline ((void (*)(void))0x80375c44)
#endif
#if (WII_NTSCU_10)
#define main_tampoline ((void (*)(void))0x803ce3dc)
#endif

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
#ifdef GCN_PLATFORM
    using namespace Controller::Pad;
#define BUTTONS (tp_mPadStatus.sval)
#define CANCEL_LOAD_BUTTONS (L | R | B)
#define SHOW_MENU_BUTTONS (L | R | DPAD_DOWN)
#endif
#ifdef WII_PLATFORM
    using namespace Controller::Mote;
#define BUTTONS (tp_mPad.buttons)
#define CANCEL_LOAD_BUTTONS (Z | C | B)
#define SHOW_MENU_BUTTONS (Z | C | MINUS)
#endif

    // Button combo to bypass the automatic loading of the save file
    // in case of crash cause by the load.
    if (BUTTONS == CANCEL_LOAD_BUTTONS && card_load) {
        card_load = false;
    }

    // check and load gz settings card if found
    Utilities::load_gz_card(card_load);

    if (BUTTONS == SHOW_MENU_BUTTONS && tp_fopScnRq.isLoading != 1 &&
        !move_link_active) {
        MenuRendering::set_menu(MN_MAIN_MENU_INDEX);
        fifo_visible = false;
    }
    if (tp_fopScnRq.isLoading == 1) {
        MenuRendering::close_active_menus();
        move_link_active = false;
        last_frame_was_loading = true;
    }

    // save temp flags and tears after every loading zone
    if (last_frame_was_loading && tp_fopScnRq.isLoading != 1) {
        tp_memcpy(g_area_reload.temp_flags, tp_gameInfo.temp_flags.flags,
                  sizeof(tp_gameInfo.temp_flags.flags));
        g_area_reload.tears = tp_gameInfo.inventory.tears;
        last_frame_was_loading = false;
    }

    GZFlags::apply_active_flags();
    FreeCam::handle_free_cam();
    MoveLink::move_link();

    if (ToolItems[Tools::TURBO_MODE_INDEX].active) {
        tp_cPadInfo.triggerInput = tp_cPadInfo.input;
    }
}

void draw() {
    setupRendering();
    // Consolas.setupRendering();
    if (MenuRendering::is_menu_open()) {
        Font::gz_renderChars("tpgz v0.1", sprite_offsets[MENU_INDEX].x + 35.0f, 25.0f, cursor_rgba,
                             g_drop_shadows);

        if (gzIconTex.loadCode == TexCode::TEX_UNLOADED) {
            load_texture("tpgz/tex/tpgz.tex", &gzIconTex);
            if (gzIconTex.loadCode != TexCode::TEX_OK) {
                tp_osReport("Could not load TPGZ's icon texture (Code: %d)", gzIconTex.loadCode);
            }
        }

        if (gzIconTex.loadCode == TexCode::TEX_OK) {
            Draw::draw_rect(0xFFFFFFFF, {sprite_offsets[MENU_INDEX].x, 5.0f}, {30, 30},
                            &gzIconTex._texObj);
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
    if (ToolItems[Tools::TIMER_INDEX].active || ToolItems[Tools::LOAD_TIMER_INDEX].active ||
        ToolItems[Tools::IGT_TIMER_INDEX].active) {
        Timer::render();
    }
    if (move_link_active) {
        MoveLink::render_info_input();
    }
    MenuRendering::render_active_menus();
    Utilities::render_active_watches();
}
}