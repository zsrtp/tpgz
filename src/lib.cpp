#include "controller.h"
#include "fifo_queue.h"
#include "font.h"
#include "free_cam.h"
#include "gz_flags.h"
#include "input_viewer.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
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
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"

_FIFOQueue Queue;
bool l_loadCard = true;
Texture l_gzIconTex;
bool last_frame_was_loading = false;

extern "C" {

#define Q(x) #x
#define QUOTE(x) Q(x)

#if (GCN_NTSCU)
#define main_trampoline ((void (*)(void))0x803737b4)
#endif
#if (GCN_PAL)
#define main_trampoline ((void (*)(void))0x803745e4)
#endif
#if (GCN_NTSCJ)
#define main_trampoline ((void (*)(void))0x80375c44)
#endif
#if (WII_NTSCU_10)
#define main_trampoline ((void (*)(void))0x803ce3dc)
#endif
#if (WII_PAL)
#define main_trampoline ((void (*)(void))0x803b929c)
#endif
#ifdef GZ_VERSION
#define INTERNAL_GZ_VERSION QUOTE(GZ_VERSION)
#endif

void apply_lib_hooks() {
    Hook::applyHooks();
    main_trampoline();
}

void init() {
    Font::loadFont("tpgz/fonts/consola.fnt");
    Draw::init();
    PosSettingsMenu::initDefaults();
    g_fifoVisible = true;
    if (l_gzIconTex.loadCode == TexCode::TEX_UNLOADED) {
        load_texture("tpgz/tex/tpgz.tex", &l_gzIconTex);
    }
    GZ_patchLinkColor();
}

void game_loop() {
#ifdef GCN_PLATFORM
#define BUTTONS (tp_mPadStatus.button)
#define CANCEL_LOAD_BUTTONS (CButton::L | CButton::R | CButton::B)
#define SHOW_MENU_BUTTONS (CButton::L | CButton::R | CButton::DPAD_DOWN)
#endif
#ifdef WII_PLATFORM
#define BUTTONS (tp_mPad.mHoldButton)
#define CANCEL_LOAD_BUTTONS (CButton::Z | CButton::C | CButton::B)
#define SHOW_MENU_BUTTONS (CButton::Z | CButton::C | CButton::MINUS)
#endif

    // Button combo to bypass the automatic loading of the save file
    // in case of crash caused by the load.
    if (BUTTONS == CANCEL_LOAD_BUTTONS && l_loadCard) {
        l_loadCard = false;
    }

    // check and load gz settings card if found
    GZ_loadGZSave(l_loadCard);

    if (BUTTONS == SHOW_MENU_BUTTONS && tp_fopScnRq.isLoading != 1 && !g_moveLinkEnabled) {
        if (GZ_checkReturnMenu()) {
            GZ_returnMenu();
        } else {
            GZ_setMenu(MN_MAIN_MENU_INDEX);
        }

        g_fifoVisible = false;
    }

    if (tp_fopScnRq.isLoading) {
        GZ_clearMenu();
        g_moveLinkEnabled = false;
        last_frame_was_loading = true;
        g_freeCamEnabled = false;
    }

    // save temp flags and tears after every loading zone
    if (last_frame_was_loading && !tp_fopScnRq.isLoading) {
        tp_memcpy(gSaveManager.mAreaReloadOpts.temp_flags, &g_dComIfG_gameInfo.info.mMemory,
                  sizeof(g_dComIfG_gameInfo.info.mMemory));

        for (int i = 0; i < 4; i++) {
            gSaveManager.mAreaReloadOpts.tears[i] = dComIfGs_getLightDropNum(i);
        }

        last_frame_was_loading = false;
    }

    GZ_execute(GAME_LOOP);
    FreeCam::execute();
    MoveLink::execute();

    if (g_tools[TURBO_MODE_INDEX].active) {
#ifdef GCN_PLATFORM
        tp_cPadInfo[0].mPressedButtonFlags = tp_cPadInfo[0].mButtonFlags;
#endif

#ifdef WII_PLATFORM
        if (!GZ_checkMenuOpen()) {
            tp_mPad.mTrigButton = tp_mPad.mHoldButton;
        }
#endif
    }
}

void post_game_loop() {
    GZ_execute(POST_GAME_LOOP);
}

Texture l_framePauseTex;
Texture l_framePlayTex;

void draw() {
    setupRendering();

    if (GZ_checkMenuOpen()) {
        Font::GZ_drawStr("tpgz v" INTERNAL_GZ_VERSION, g_spriteOffsets[MENU_INDEX].x + 35.0f, 25.0f,
                         g_cursorColor, g_dropShadows);
        if (l_gzIconTex.loadCode == TexCode::TEX_OK) {
            Draw::drawRect(0xFFFFFFFF, {g_spriteOffsets[MENU_INDEX].x, 5.0f}, {30, 30},
                           &l_gzIconTex._texObj);
        }
    }

    if (g_fifoVisible) {
        FIFOQueue::renderItems(Queue);
    }

    if (g_tools[LINK_DEBUG_INDEX].active) {
        GZ_displayLinkInfo();
    }

    if (g_tools[HEAP_DEBUG_INDEX].active) {
        GZ_drawHeapInfo();
    }

    if (g_tools[INPUT_VIEWER_INDEX].active) {
        InputViewer::draw();
    }

    if (g_tools[TIMER_INDEX].active) {
        Timer::drawTimer();
    }

    if (g_tools[LOAD_TIMER_INDEX].active) {
        Timer::drawLoadTimer();
    }

    if (g_tools[IGT_TIMER_INDEX].active) {
        Timer::drawIGT();
    }

    if (g_tools[FRAME_ADVANCE_INDEX].active) {
        if (l_framePauseTex.loadCode == TexCode::TEX_UNLOADED) {
            load_texture("tpgz/tex/framePause.tex", &l_framePauseTex);
        }

        if (l_framePlayTex.loadCode == TexCode::TEX_UNLOADED) {
            load_texture("tpgz/tex/framePlay.tex", &l_framePlayTex);
        }

        GZ_drawFrameTex(&l_framePauseTex, &l_framePlayTex);
    } else {
        if (l_framePauseTex.loadCode == TexCode::TEX_OK) {
            free_texture(&l_framePauseTex);
        }

        if (l_framePlayTex.loadCode == TexCode::TEX_OK) {
            free_texture(&l_framePlayTex);
        }
    }

    GZ_drawMenu();
    GZ_drawWatches();
}
}