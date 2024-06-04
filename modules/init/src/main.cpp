#include <main.h>
#include "boot.h"
#include "fifo_queue.h"
#include "font.h"
#include "gz_flags.h"
#include "menu.h"
#include "menus/utils/menu_mgr.h"
#include "collision_view.h"
#include "mash_checker.h"

#include "utils/memory.h"
#include "utils/card.h"
#include "utils/draw.h"
#include "utils/link.h"
#include "utils/hook.h"
#include "rels/include/cxx.h"
#include "events/draw_listener.h"
#include "events/pre_loop_listener.h"
#include "events/post_loop_listener.h"

namespace tpgz::modules {
void main() {
    // Utilities initialization
    Hook::applyHooks();
    Font::loadFont("/tpgz/fonts/consola.fnt");
    Draw::init();
    GZ_PosSettings_initDefaults();
    GZ_patchLinkColor();
#ifdef WII_PLATFORM
    g_tmpBuf = new (-0x200) uint8_t[0x4000];
#endif

    g_menuMgr = new MenuMgr();
    g_fifoVisible = true;
    // Init the draw listener
    g_drawListener = new DrawListener();
    // Setup the render order
    g_drawListener->addListener(GZ_renderMenuTitle);
    g_drawListener->addListener(GZ_renderFifoQueue);
    g_drawListener->addListener(GZ_displayLinkInfo);
    g_drawListener->addListener(GZ_displayButtonMashInfo);
    g_drawListener->addListener(GZ_drawHeapInfo);
    g_drawListener->addListener(Timer::drawTimer);
    g_drawListener->addListener(Timer::drawLoadTimer);
    g_drawListener->addListener(Timer::drawIGT);
    // g_drawListener->addListener(GZ_drawMenu);
    g_drawListener->addListener(GZ_drawWatches);
    g_drawListener->addListener(GZ_renderPlayPause);
    g_drawListener->addListener(GZ_drawPacketNumOverflow);
    
    // Init the pre-loop listener
    g_PreLoopListener = new PreLoopListener();
    g_PreLoopListener->addListener(GZ_handleCardLoad);
    g_PreLoopListener->addListener(GZ_handleMenu);
    g_PreLoopListener->addListener(GZ_handleSavingTmp);
    g_PreLoopListener->addListener(GZ_handleFlags_PreLoop);
    g_PreLoopListener->addListener(GZ_handleTurbo);
    g_PreLoopListener->addListener(GZ_setCursorColor);
    g_PreLoopListener->addListener(GZ_setTunicColor);
    g_PreLoopListener->addListener(GZ_frameAdvance);
    g_PreLoopListener->addListener(GZ_handleTools);
    g_PreLoopListener->addListener(GZ_handleTriggerView);
    g_PreLoopListener->addListener(GZ_handleActorView);
    g_PreLoopListener->addListener(GZ_drawPolygons);
    g_PreLoopListener->addListener(GZ_handleTansformIndicator);
    
    // Init the post-loop listener
    g_PostLoopListener = new PostLoopListener();
    g_PostLoopListener->addListener(GZ_handleFlags_PostLoop);
    g_PostLoopListener->addListener(GZ_setCursorColor);
    g_PostLoopListener->addListener(GZ_setTunicColor);
}
void exit() {}

}  // namespace tpgz::modules