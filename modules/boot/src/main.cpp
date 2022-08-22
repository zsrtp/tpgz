#include <boot.h>
#include "controller.h"
#include "fifo_queue.h"
#include "font.h"
#include "free_cam.h"
#include "gz_flags.h"
#include "libtp_c/include/m_Do/m_Do_printf.h"
#include "menu.h"
#include "settings.h"
#include "menus/utils/menu_mgr.h"
#include "movelink.h"
#include "timer.h"
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
#include "handlers/draw_handler.h"
#include "handlers/pre_loop_handler.h"
#include "handlers/post_loop_handler.h"

_FIFOQueue Queue;
bool l_loadCard = true;
Texture l_gzIconTex;
bool last_frame_was_loading = false;
tpgz::dyn::GZModule g_InputViewer_rel("/tpgz/rels/input_viewer.rel");

#define Q(x) #x
#define QUOTE(x) Q(x)

#ifdef GZ_VERSION
#define INTERNAL_GZ_VERSION QUOTE(GZ_VERSION)
#else
#warning GZ_VERSION is not defined
#define INTERNAL_GZ_VERSION "<unk>"
#endif

#ifdef GCN_PLATFORM
#define BUTTONS (mPadStatus.button)
#define CANCEL_LOAD_BUTTONS (CButton::L | CButton::R | CButton::B)
#define SHOW_MENU_BUTTONS (CButton::L | CButton::R | CButton::DPAD_DOWN)
#endif
#ifdef WII_PLATFORM
#define BUTTONS (mPad.mHoldButton)
#define CANCEL_LOAD_BUTTONS (CButton::Z | CButton::C | CButton::B)
#define SHOW_MENU_BUTTONS (CButton::Z | CButton::C | CButton::MINUS)
#endif

namespace tpgz::modules {
void main() {
    // Run the initialization module.
    tpgz::dyn::GZModule* initRel = new tpgz::dyn::GZModule("/tpgz/rels/init.rel");
    initRel->load(true);
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

KEEP_FUNC void game_loop() {
    g_PreLoopHandler->handleAll(nullptr);
}

KEEP_FUNC void post_game_loop() {
    g_PostLoopHandler->handleAll(nullptr);
}

KEEP_FUNC void draw() {
    setupRendering();
    g_drawHandler->handleAll(nullptr);
}
}

inline void GZ_controlModule(size_t id, tpgz::dyn::GZModule& rel) {
    if (g_tools[id].active) {
        rel.load(true);
    } else {
        rel.close();
    }
}

KEEP_FUNC void GZ_controlTools() {
    GZ_controlModule(INPUT_VIEWER_INDEX, g_InputViewer_rel);
}

KEEP_FUNC void GZ_controlMenu() {
    if (BUTTONS == SHOW_MENU_BUTTONS && fopScnRq.isLoading != 1 && !g_moveLinkEnabled) {
        if (!g_menuMgr->isOpen()) {
            if (g_menuMgr->getStackSize() > 0) {
                g_menuMgr->open();
            } else {
                g_menuMgr->push(MN_MAIN_MENU_INDEX);
            }
        }

        g_fifoVisible = false;
    }

    g_menuMgr->handleCommands();

    if (fopScnRq.isLoading) {
        g_menuMgr->hide();
        g_moveLinkEnabled = false;
        last_frame_was_loading = true;
        g_freeCamEnabled = false;
    }
}

KEEP_FUNC void GZ_controlCardLoad() {
    // Button combo to bypass the automatic loading of the save file
    // in case of crash caused by the load.
    if (BUTTONS == CANCEL_LOAD_BUTTONS && l_loadCard) {
        l_loadCard = false;
    }

    // check and load gz settings card if found
    GZ_loadGZSave(l_loadCard);
}

KEEP_FUNC void GZ_controlSavingTmp() {
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

KEEP_FUNC void GZ_controlFlags_PreLoop() {
    GZ_execute(GAME_LOOP);
}

KEEP_FUNC void GZ_controlFlags_PostLoop() {
    GZ_execute(POST_GAME_LOOP);
}

KEEP_FUNC void GZ_controlTurbo() {
    if (g_tools[TURBO_MODE_INDEX].active) {
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
        Font::GZ_drawStr("tpgz v" INTERNAL_GZ_VERSION, g_spriteOffsets[MENU_INDEX].x + 35.0f, 25.0f,
                         g_cursorColor, g_dropShadows);
        if (l_gzIconTex.loadCode == TexCode::TEX_OK) {
            Draw::drawRect(0xFFFFFFFF, {g_spriteOffsets[MENU_INDEX].x, 5.0f}, {30, 30},
                           &l_gzIconTex._texObj);
        }
    }
}

Texture l_framePauseTex;
Texture l_framePlayTex;

KEEP_FUNC void GZ_renderPlayPause() {
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
}