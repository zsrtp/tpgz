#include <main.h>
#include "boot.h"
#include "collision_view.h"
#include "fifo_queue.h"
#include "font.h"
#include "gz_flags.h"
#include "scene.h"
#include "menus/menu.h"
#include "menus/utils/menu_mgr.h"
#include "modules.h"
#include "tools.h"

#include "utils/memory.h"
#include "utils/audio.h"
#include "utils/card.h"
#include "utils/draw.h"
#include "utils/link.h"
#include "utils/hook.h"
#include "rels/include/cxx.h"
#include "events/draw_listener.h"
#include "events/pre_loop_listener.h"
#include "events/post_loop_listener.h"
#include "libtp_c/include/dolphin/os/OSCache.h"

void GZ_PosSettings_initDefaults();
void GZ_patchLinkColor();

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
    g_modules.push_back(new Module{projectionView_active, "/tpgz/rels/features/projection_view.rel"});
    g_modules.push_back(new Module{triggerViewer_active, "/tpgz/rels/features/trigger_view.rel"});
    g_modules.push_back(new Module{actorView_active, "/tpgz/rels/features/actor_view.rel"});
    g_modules.push_back(
        new Module{transformIndicator_active, "/tpgz/rels/features/transform_indicator.rel"});
    g_modules.push_back(new Module{umd_active, "/tpgz/rels/features/umd.rel"});
#ifdef WII_PLATFORM
    g_modules.push_back(new Module{bit_active, "/tpgz/rels/features/bit.rel"});
#endif
    g_modules.push_back(new Module{corotd_active, "/tpgz/rels/features/corotd.rel"});
    g_modules.push_back(new Module{mash_checker_active, "/tpgz/rels/features/mash_checker.rel"});
    g_modules.push_back(new Module{gorge_active, "/tpgz/rels/features/gorge.rel"});
    g_modules.push_back(new Module{rollcheck_active, "/tpgz/rels/features/rollcheck.rel"});
    g_modules.push_back(new Module{moon_jump_active, "/tpgz/rels/features/moon_jump.rel"});

    // Init the pre-loop listener
    g_PreLoopListener = new PreLoopListener();
    g_PreLoopListener->addListener(GZ_handleCardLoad);
    g_PreLoopListener->addListener(GZ_handleMenu);
    g_PreLoopListener->addListener(GZ_handleTools);
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

    // Init the gz flags
    GZFlg_addFlag(new GZFlag{GZFLG_FREEZE_ACTOR, GZ_freezeActors_active,
                             GAME_LOOP, GZ_freezeActors, GZ_unfreezeActors});
    GZFlg_addFlag(new GZFlag{GZFLG_HIDE_ACTOR, GZ_hideActors_active, GAME_LOOP,
                             GZ_hideActors, GZ_showActors});
    GZFlg_addFlag(new GZFlag{GZFLG_FREEZE_CAMERA, GZ_freezeCamera_active,
                             GAME_LOOP, GZ_freezeCamera, GZ_unfreezeCamera});
    GZFlg_addFlag(new GZFlag{GZFLG_HIDE_HUD, GZ_hideHUD_active, GAME_LOOP,
                             GZ_hideHUD, GZ_showHUD});
    GZFlg_addFlag(new GZFlag{GZFLG_FREEZE_TIME, GZ_freezeTime_active, GAME_LOOP,
                             GZ_freezeTime});
    GZFlg_addFlag(new GZFlag{GZFLG_DISABLE_BGM, GZ_disableBgm_active, GAME_LOOP,
                             GZ_disableBGM, GZ_enableBGM});
    GZFlg_addFlag(new GZFlag{GZFLG_DISABLE_SFX, GZ_disableSFX_active, GAME_LOOP,
                             GZ_disableSFX, GZ_enableSFX});
}
void exit() {}

}  // namespace tpgz::modules

void GZ_PosSettings_initDefaults() {
#ifdef GCN_PLATFORM
    GZStng_add(STNG_SPRITES_INPUT_VIEWER, new Vec2{220.f, 380.f}, sizeof(Vec2));
#elif defined(WII_PLATFORM)
    GZStng_add(STNG_SPRITES_INPUT_VIEWER, new Vec2{250.f, 360.f}, sizeof(Vec2));
#endif
    GZStng_add(STNG_SPRITES_MENU, new Vec2{25.f, 60.f}, sizeof(Vec2));
    GZStng_add(STNG_SPRITES_DEBUG_INFO, new Vec2{450.0f, 200.f}, sizeof(Vec2));
    GZStng_add(STNG_SPRITES_TIMER_SPR, new Vec2{450.0f, 420.f}, sizeof(Vec2));
    GZStng_add(STNG_SPRITES_LOAD_TIMER_SPR, new Vec2{450.0f, 30.f}, sizeof(Vec2));
    GZStng_add(STNG_SPRITES_IGT_TIMER_SPR, new Vec2{35.0f, 30.f}, sizeof(Vec2));
    GZStng_add(STNG_SPRITES_FIFO_SPR, new Vec2{5.0f, 440.f}, sizeof(Vec2));
    GZStng_add(STNG_SPRITES_HEAP_INFO, new Vec2{145.0f, 25.0f}, sizeof(Vec2));
    GZStng_add(STNG_SPRITES_MASH_INFO, new Vec2{450.0f, 400.0f}, sizeof(Vec2));
    GZStng_add(STNG_SPRITES_TRANSFORM_IND, new Vec2{465.0f, 30.0f}, sizeof(Vec2));
}

inline void GZ_patchLinkColor() {
#ifdef WII_PLATFORM
#ifdef WII_NTSCU_10
#define SWORD_UP_RED_ADDR 0x801176B0
#define SWORD_UP_GREEN_ADDR 0x801176C8
#define SWORD_UP_BLUE_ADDR 0x801176E0
#endif
#ifdef WII_NTSCU_12
#define SWORD_UP_RED_ADDR 0x80117de0
#define SWORD_UP_GREEN_ADDR 0x80117df8
#define SWORD_UP_BLUE_ADDR 0x80117e10
#endif
#ifdef WII_NTSCJ
#define SWORD_UP_RED_ADDR 0x80117bec
#define SWORD_UP_GREEN_ADDR 0x80117c04
#define SWORD_UP_BLUE_ADDR 0x80117c1c
#endif
#ifdef WII_PAL
#define SWORD_UP_RED_ADDR 0x80117d64
#define SWORD_UP_GREEN_ADDR 0x80117d7c
#define SWORD_UP_BLUE_ADDR 0x80117d94
#endif
    *reinterpret_cast<uint32_t*>(SWORD_UP_RED_ADDR) = 0x60000000;  // nop
    DCFlushRange((void*)(SWORD_UP_RED_ADDR), sizeof(uint32_t));
    ICInvalidateRange((void*)(SWORD_UP_RED_ADDR), sizeof(uint32_t));
    *reinterpret_cast<uint32_t*>(SWORD_UP_GREEN_ADDR) = 0x60000000;  // nop
    DCFlushRange((void*)(SWORD_UP_GREEN_ADDR), sizeof(uint32_t));
    ICInvalidateRange((void*)(SWORD_UP_GREEN_ADDR), sizeof(uint32_t));
    *reinterpret_cast<uint32_t*>(SWORD_UP_BLUE_ADDR) = 0x60000000;  // nop
    DCFlushRange((void*)(SWORD_UP_BLUE_ADDR), sizeof(uint32_t));
    ICInvalidateRange((void*)(SWORD_UP_BLUE_ADDR), sizeof(uint32_t));
#endif  // WII_PLATFORM
}
