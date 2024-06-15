#include <boot.h>
#include "controller.h"
#include "fifo_queue.h"
#include "font.h"
#include "global_data.h"
#include "gz_flags.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "menus/menu.h"
#include "settings.h"
#include "menus/utils/menu_mgr.h"
#include "timer.h"
#include "pos_settings.h"
#include "trigger_view.h"
#include "collision_view.h"
#include "utils/card.h"
#include "utils/draw.h"
#include "utils/link.h"
#include "utils/loading.h"
#include "utils/memory.h"
#include "utils/texture.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_scene_req.h"
#include "libtp_c/include/m_Do/m_Re_controller_pad.h"
#include "rels/include/cxx.h"
#include "utils/rels.h"
#include "rels/include/defines.h"
#include "events/draw_listener.h"
#include "events/pre_loop_listener.h"
#include "events/post_loop_listener.h"

#ifdef WII_PLATFORM
extern bool isWidescreen;
#else
#define isWidescreen (false)
#endif
_FIFOQueue Queue;
bool l_loadCard = true;
Texture l_gzIconTex;
bool last_frame_was_loading = false;

#define Q(x) #x
#define QUOTE(x) Q(x)

#ifdef GZ_VERSION
#define INTERNAL_GZ_VERSION QUOTE(GZ_VERSION)
#else
#warning GZ_VERSION is not defined
#define INTERNAL_GZ_VERSION "<unk>"
#endif

#define BUTTONS (GZ_getButtonStatus())
#ifdef GCN_PLATFORM
#define CANCEL_LOAD_BUTTONS (CButton::L | CButton::R | CButton::B)
#define SHOW_MENU_BUTTONS (CButton::L | CButton::R | CButton::DPAD_DOWN)
#endif
#ifdef WII_PLATFORM
#define CANCEL_LOAD_BUTTONS (CButton::Z | CButton::C | CButton::B)
#define SHOW_MENU_BUTTONS (CButton::Z | CButton::C | CButton::MINUS)
#endif

namespace tpgz::modules {
void main() {
    OSReportEnable();
    OSReport("TPGZ is starting...\n");
    // Run the initialization module.
    tpgz::dyn::GZModule* initRel = new tpgz::dyn::GZModule("/tpgz/rels/init.rel");
    initRel->loadFixed(true);
    // The initialization module doesn't need to be kept in memory once ran.
    // initRel->close(); // This code is implicitly ran in the destructor.
    delete initRel;

    if (l_gzIconTex.loadCode == TexCode::TEX_UNLOADED) {
        load_texture("/tpgz/tex/tpgz.tex", &l_gzIconTex);
    }
}
void exit() {}

}  // namespace tpgz::modules

// Game hooks
extern "C" {

/**
 * @brief Hooked to run right before the next main loop starts.
 */
KEEP_FUNC void game_loop() {
    // Call all the functions registered to be run before the main loop.
    g_PreLoopListener->dispatchAll();
}

/**
 * @brief Hooked to run right after the current main loop finishes.
 */
KEEP_FUNC void post_game_loop() {
    // Call all the functions registered to be run after the main loop.
    g_PostLoopListener->dispatchAll();
}

/**
 * @brief Hooked to run in the render thread.
 */
KEEP_FUNC void draw() {
    // Setup the graphic library for our drawing utility API.
    setupRendering();
    // Call all the functions registered to be run in the render thread.
    g_drawListener->dispatchAll();
}
}

KEEP_FUNC void GZ_drawPacketNumOverflow() {
    if (l_drawPacketListNum >= 1000) {
        Font::GZ_drawStr("Draw Packet List full!", 35.0f, 430.0f, 0xFFFFFFFF, GZ_checkDropShadows());
    }
}

/**
 * @brief Handles when to show/hide the menus.
 */
KEEP_FUNC void GZ_handleMenu() {
    if (BUTTONS == SHOW_MENU_BUTTONS && fopScnRq.isLoading != 1 && !g_moveLinkEnabled) {
        if (!g_menuMgr->isOpen()) {
            if (!g_menuMgr->isEmpty()) {
                g_menuMgr->open();
            } else {
                g_menuMgr->push(MN_MAIN_MENU_INDEX);
            }
        }

        g_fifoVisible = false;
    }

    if (fopScnRq.isLoading) {
        g_menuMgr->hide();
        g_moveLinkEnabled = false;
        g_actorViewEnabled = false;
        last_frame_was_loading = true;
        g_freeCamEnabled = false;
    }

    g_menuMgr->handleCommands();
}

KEEP_FUNC void GZ_handleCardLoad() {
    // Button combo to bypass the automatic loading of the save file
    // in case of crash caused by the load.
    if (BUTTONS == CANCEL_LOAD_BUTTONS && l_loadCard) {
        l_loadCard = false;
    }

    // check and load gz settings card if found
    GZ_loadGZSave(l_loadCard);
}

KEEP_FUNC void GZ_handleSavingTmp() {
    // save temp flags and tears after every loading zone
    if (last_frame_was_loading && !fopScnRq.isLoading) {
        memcpy(gSaveManager.mAreaReloadOpts.temp_flags, &g_dComIfG_gameInfo.info.mMemory,
               sizeof(g_dComIfG_gameInfo.info.mMemory));

        for (int i = 0; i < 4; i++) {
            gSaveManager.mAreaReloadOpts.tears[i] = dComIfGs_getLightDropNum(i);
        }

        last_frame_was_loading = false;
    }
}

KEEP_FUNC void GZ_handleFlags_PreLoop() {
    GZ_execute(GAME_LOOP);
}

KEEP_FUNC void GZ_handleFlags_PostLoop() {
    GZ_execute(POST_GAME_LOOP);
}

KEEP_FUNC void GZ_handleTurbo() {
    if (GZStng_getSettingData(STNG_TOOLS_TURBO_MODE, false)) {
#ifdef GCN_PLATFORM
        cPadInfo[0].mPressedButtonFlags = cPadInfo[0].mButtonFlags;
#endif

#ifdef WII_PLATFORM
        if (!g_menuMgr->isOpen()) {
            mPad.mTrigButton = mPad.mHoldButton;
        }
#endif
    }
}

KEEP_FUNC void GZ_renderMenuTitle() {
    if (g_menuMgr->isOpen()) {
        Vec2 spriteOffset = GZ_getSpriteOffset(STNG_SPRITES_MENU);
        Font::GZ_drawStr("tpgz v" INTERNAL_GZ_VERSION, spriteOffset.x + 35.0f, 25.0f,
                         g_cursorColor, GZ_checkDropShadows());
        if (l_gzIconTex.loadCode == TexCode::TEX_OK) {
            Draw::drawRect(0xFFFFFFFF, {spriteOffset.x, 5.0f},
                           {30 * (isWidescreen ? 0.75f : 1.0f), 30}, &l_gzIconTex._texObj);
        }
    }
}

Texture l_framePauseTex;
Texture l_framePlayTex;

KEEP_FUNC void GZ_renderPlayPause() {
    if (GZStng_getSettingData(STNG_TOOLS_FRAME_ADVANCE, false)) {
        if (l_framePauseTex.loadCode == TexCode::TEX_UNLOADED) {
            load_texture("/tpgz/tex/framePause.tex", &l_framePauseTex);
        }

        if (l_framePlayTex.loadCode == TexCode::TEX_UNLOADED) {
            load_texture("/tpgz/tex/framePlay.tex", &l_framePlayTex);
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
}