#include <main.h>
#include "boot.h"
#include "fifo_queue.h"
#include "font.h"
#include "free_cam.h"
#include "gz_flags.h"
#include "menu.h"
#include "menus/utils/menu_mgr.h"

#include "movelink.h"
#include "utils/memory.h"
#include "utils/card.h"
#include "utils/draw.h"
#include "utils/link.h"
#include "utils/hook.h"
#include "libtp_c/include/msl_c/string.h"
#include "rels/include/cxx.h"
#include "handlers/draw_handler.h"
#include "handlers/pre_loop_handler.h"
#include "handlers/post_loop_handler.h"

namespace tpgz::modules {
void main() {
    // Utilities initialization
    Hook::applyHooks();
    Font::loadFont("/tpgz/fonts/consola.fnt");
    Draw::init();
    PosSettingsMenu::initDefaults();
    GZ_patchLinkColor();
#ifdef WII_PLATFORM
    g_tmpBuf = new (-0x200) uint8_t[0x4000];
#endif

    g_menuMgr = new MenuMgr();
    g_fifoVisible = true;
    // Init the draw handler
    g_drawHandler = new DrawHandler();
    // Setup the render order
    g_drawHandler->addHandler(GZ_renderMenuTitle);
    g_drawHandler->addHandler(GZ_renderFifoQueue);
    g_drawHandler->addHandler(GZ_displayLinkInfo);
    g_drawHandler->addHandler(GZ_drawHeapInfo);
    g_drawHandler->addHandler(Timer::drawTimer);
    g_drawHandler->addHandler(Timer::drawLoadTimer);
    g_drawHandler->addHandler(Timer::drawIGT);
    // g_drawHandler->addHandler(GZ_drawMenu);
    g_drawHandler->addHandler(GZ_drawWatches);
    g_drawHandler->addHandler(GZ_renderPlayPause);
    // Init the pre-loop handler
    g_PreLoopHandler = new PreLoopHandler();
    g_PreLoopHandler->addHandler(GZ_controlCardLoad);
    g_PreLoopHandler->addHandler(GZ_controlMenu);
    g_PreLoopHandler->addHandler(GZ_controlSavingTmp);
    g_PreLoopHandler->addHandler(GZ_controlFlags_PreLoop);
    g_PreLoopHandler->addHandler(GZ_controlTurbo);
    g_PreLoopHandler->addHandler(GZ_setCursorColor);
    g_PreLoopHandler->addHandler(GZ_setTunicColor);
    g_PreLoopHandler->addHandler(GZ_frameAdvance);
    g_PreLoopHandler->addHandler(FreeCam::execute);
    g_PreLoopHandler->addHandler(MoveLink::execute);
    g_PreLoopHandler->addHandler(GZ_controlTools);
    // Init the post-loop handler
    g_PostLoopHandler = new PostLoopHandler();
    g_PostLoopHandler->addHandler(GZ_controlFlags_PostLoop);
    g_PostLoopHandler->addHandler(GZ_setCursorColor);
    g_PostLoopHandler->addHandler(GZ_setTunicColor);
}
void exit() {}

}  // namespace tpgz::modules