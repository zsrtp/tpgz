#include <main.h>
#include "boot.h"
#include "fifo_queue.h"
#include "font.h"
#include "gz_flags.h"
#include "menu.h"
#include "menus/utils/menu_mgr.h"
#include "collision_view.h"
#include "mash_checker.h"
#include "modules.h"

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
    g_drawListener->addListener(GZ_drawWatches);
    g_drawListener->addListener(GZ_renderPlayPause);
    g_drawListener->addListener(GZ_drawPacketNumOverflow);

    // Init the module list
    g_modules.push_back(new Module{inputViewer_active, "/tpgz/rels/features/input_viewer.rel"});
    g_modules.push_back(new Module{freeCam_active, "/tpgz/rels/features/free_cam.rel"});
    g_modules.push_back(new Module{moveLink_active, "/tpgz/rels/features/moveactor.rel"});
    g_modules.push_back(new Module{triggerViewer_active, "/tpgz/rels/features/trigger_view.rel"});
    g_modules.push_back(new Module{actorView_active, "/tpgz/rels/features/actor_view.rel"});
    g_modules.push_back(new Module{transformIndicator_active, {"/tpgz/rels/features/transform_indicator.rel"}});

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
    g_PreLoopListener->addListener(GZ_handleModules);
    g_PreLoopListener->addListener(GZ_drawPolygons);

    // Init the post-loop listener
    g_PostLoopListener = new PostLoopListener();
    g_PostLoopListener->addListener(GZ_handleFlags_PostLoop);
    g_PostLoopListener->addListener(GZ_setCursorColor);
    g_PostLoopListener->addListener(GZ_setTunicColor);

    // Init the command list
    // g_commands.push_back({});
}
void exit() {}

}  // namespace tpgz::modules