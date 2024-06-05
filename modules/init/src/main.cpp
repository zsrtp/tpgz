#include <main.h>
#include "bit.h"
#include "boot.h"
#include "collision_view.h"
#include "corotdcheck.h"
#include "fifo_queue.h"
#include "font.h"
#include "gorge.h"
#include "gz_flags.h"
#include "menu.h"
#include "mash_checker.h"
#include "menus/utils/menu_mgr.h"
#include "modules.h"
#include "rollcheck.h"
#include "umd.h"

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
    g_modules.push_back(
        new Module{transformIndicator_active, {"/tpgz/rels/features/transform_indicator.rel"}});

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
    GZCmd_addCmd(new Command{CMD_STORE_POSITION, g_commandStates[CMD_STORE_POSITION],
                             STORE_POSITION_BUTTONS, GZCmd_storePosition});
    GZCmd_addCmd(new Command{CMD_LOAD_POSITION, g_commandStates[CMD_LOAD_POSITION],
                             LOAD_POSITION_BUTTONS, GZCmd_loadPosition});
    GZCmd_addCmd(new Command{CMD_MOON_JUMP, g_commandStates[CMD_MOON_JUMP], MOON_JUMP_BUTTONS,
                             GZCmd_moonJump});
    GZCmd_addCmd(new Command{CMD_RELOAD_AREA, g_commandStates[CMD_RELOAD_AREA], RELOAD_AREA_BUTTONS,
                             GZCmd_reloadArea});
    GZCmd_addCmd(new Command{CMD_TIMER_TOGGLE, g_commandStates[CMD_TIMER_TOGGLE],
                             TIMER_TOGGLE_BUTTONS, GZCmd_toggleTimer});
    GZCmd_addCmd(new Command{CMD_TIMER_RESET, g_commandStates[CMD_TIMER_RESET], TIMER_RESET_BUTTONS,
                             GZCmd_resetTimer});
    GZCmd_addCmd(new Command{CMD_GORGE_VOID, g_commandStates[CMD_GORGE_VOID], GORGE_VOID_BUTTONS,
                             GZCmd_loadGorgeVoid});
#ifdef WII_PLATFORM
    GZCmd_addCmd(
        new Command{CMD_BIT, g_commandStates[CMD_BIT], BACK_IN_TIME_BUTTONS, GZCmd_bitPractice});
#endif
    GZCmd_addCmd(new Command{CMD_FREE_CAM, g_commandStates[CMD_FREE_CAM], FREE_CAM_BUTTONS,
                             GZCmd_toggleFreeCam});
    GZCmd_addCmd(new Command{CMD_MOVE_LINK, g_commandStates[CMD_MOVE_LINK], MOVE_LINK_BUTTONS,
                             GZCmd_toggleMoveLink});
    GZCmd_addCmd(new Command{CMD_FRAME_PAUSE, g_commandStates[CMD_FRAME_PAUSE], FRAME_PAUSE_BUTTONS,
                             GZCmd_pauseFrame});

    // Init the gz flags
    g_gzFlags.push_back(new GZFlag{GZFLG_GORGE_VOID, &g_tools[GORGE_INDEX].active, GAME_LOOP,
                                   GorgeVoidIndicator::execute});
#ifdef WII_PLATFORM
    g_gzFlags.push_back(
        new GZFlag{GZFLG_BIT, &g_tools[BIT_INDEX].active, GAME_LOOP, BiTIndicator::execute});
#endif
    g_gzFlags.push_back(
        new GZFlag{GZFLG_ROLL, &g_tools[ROLL_INDEX].active, GAME_LOOP, RollIndicator::execute});
    g_gzFlags.push_back(
        new GZFlag{GZFLG_COROTD, &g_tools[COROTD_INDEX].active, GAME_LOOP, CoroTDChecker::execute});
    g_gzFlags.push_back(
        new GZFlag{GZFLG_UMD, &g_tools[UMD_INDEX].active, POST_GAME_LOOP, UMDIndicator::execute});
    g_gzFlags.push_back(new GZFlag{GZFLG_FREEZE_ACTOR, &g_sceneFlags[FREEZE_ACTOR_INDEX].active,
                                   GAME_LOOP, GZ_freezeActors, GZ_unfreezeActors});
    g_gzFlags.push_back(new GZFlag{GZFLG_HIDE_ACTOR, &g_sceneFlags[HIDE_ACTOR_INDEX].active,
                                   GAME_LOOP, GZ_hideActors, GZ_showActors});
    g_gzFlags.push_back(new GZFlag{GZFLG_FREEZE_CAMERA, &g_sceneFlags[FREEZE_CAMERA_INDEX].active,
                                   GAME_LOOP, GZ_freezeCamera, GZ_unfreezeCamera});
    g_gzFlags.push_back(new GZFlag{GZFLG_HIDE_HUD, &g_sceneFlags[HIDE_HUD_INDEX].active, GAME_LOOP,
                                   GZ_hideHUD, GZ_showHUD});
    g_gzFlags.push_back(new GZFlag{GZFLG_FREEZE_TIME, &g_sceneFlags[FREEZE_TIME_INDEX].active,
                                   GAME_LOOP, GZ_freezeTime});
    g_gzFlags.push_back(new GZFlag{GZFLG_DISABLE_BG, &g_sceneFlags[DISABLE_BG_INDEX].active,
                                   GAME_LOOP, GZ_disableBGM, GZ_enableBGM});
    g_gzFlags.push_back(new GZFlag{GZFLG_DISABLE_SFX, &g_sceneFlags[DISABLE_SFX_INDEX].active,
                                   GAME_LOOP, GZ_disableSFX, GZ_enableSFX});
}
void exit() {}

}  // namespace tpgz::modules