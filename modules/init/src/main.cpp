#include <main.h>
#include "boot.h"
#include "fifo_queue.h"
#include "font.h"
#include "free_cam.h"
#include "gz_flags.h"
#include "menu.h"

#include "menus/amounts_menu.h"
#include "menus/any_saves_menu.h"
#include "menus/cheats_menu.h"
#include "menus/flags_menu.h"
#include "menus/hundo_saves_menu.h"
#include "menus/inventory_menu.h"
#include "menus/item_wheel_menu.h"
#include "menus/main_menu.h"
#include "menus/memory_editor_menu.h"
#include "menus/memory_menu.h"
#include "menus/pause_menu.h"
#include "menus/position_settings_menu.h"
#include "menus/practice_menu.h"
#include "menus/scene_menu.h"
#include "menus/settings_menu.h"
#include "menus/flag_records_menu.h"
#include "menus/tools_menu.h"
#include "menus/warping_menu.h"
#include "menus/ad_saves_menu.h"
#include "menus/memfiles_menu.h"
#include "menus/actor_spawn_menu.h"

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

extern Menu* l_menuDrawList[MAX_MENU_RENDER_FLAGS];

void initMenus() {
    memset(l_menuDrawList, 0, sizeof(l_menuDrawList));
    l_menuDrawList[MN_MAIN_MENU_INDEX] = new (0x4, HEAP_ARCHIVE) MainMenu();
    l_menuDrawList[MN_CHEAT_INDEX] = new (0x4, HEAP_ARCHIVE) CheatsMenu();
    l_menuDrawList[MN_FLAGS_INDEX] = new (0x4, HEAP_ARCHIVE) FlagsMenu();
    l_menuDrawList[MN_INVENTORY_INDEX] = new (0x4, HEAP_ARCHIVE) InventoryMenu();
    l_menuDrawList[MN_MEMORY_INDEX] = new (0x4, HEAP_ARCHIVE) MemoryMenu();
    l_menuDrawList[MN_PRACTICE_INDEX] = new (0x4, HEAP_ARCHIVE) PracticeMenu();
    l_menuDrawList[MN_SCENE_INDEX] = new (0x4, HEAP_ARCHIVE) SceneMenu();
    l_menuDrawList[MN_SETTINGS_INDEX] = new (0x4, HEAP_ARCHIVE) SettingsMenu();
    l_menuDrawList[MN_TOOLS_INDEX] = new (0x4, HEAP_ARCHIVE) ToolsMenu();
    l_menuDrawList[MN_WARPING_INDEX] = new (0x4, HEAP_ARCHIVE) WarpingMenu();
    l_menuDrawList[MN_GENERAL_FLAGS_INDEX] = new (0x4, HEAP_ARCHIVE) GeneralFlagsMenu();
    l_menuDrawList[MN_DUNGEON_FLAGS_INDEX] = new (0x4, HEAP_ARCHIVE) DungeonFlagsMenu();
    l_menuDrawList[MN_PORTAL_FLAGS_INDEX] = new (0x4, HEAP_ARCHIVE) PortalFlagsMenu();
    l_menuDrawList[MN_FLAG_RECORDS_INDEX] = new (0x4, HEAP_ARCHIVE) FlagRecordsMenu();
    l_menuDrawList[MN_FLAG_LOG_INDEX] = new (0x4, HEAP_ARCHIVE) FlagLogMenu();
    l_menuDrawList[MN_ITEM_WHELL_INDEX] = new (0x4, HEAP_ARCHIVE) ItemWheelMenu();
    l_menuDrawList[MN_PAUSE_INDEX] = new (0x4, HEAP_ARCHIVE) PauseMenu();
    l_menuDrawList[MN_AMOUNTS_INDEX] = new (0x4, HEAP_ARCHIVE) AmountsMenu();
    l_menuDrawList[MN_WATCHES_INDEX] = new (0x4, HEAP_ARCHIVE) WatchesMenu();
    l_menuDrawList[MN_MEMORY_EDITOR_INDEX] = new (0x4, HEAP_ARCHIVE) MemoryEditorMenu();
    l_menuDrawList[MN_MEM_FILES_INDEX] = new (0x4, HEAP_ARCHIVE) MemfilesMenu();
    l_menuDrawList[MN_ANY_SAVES_INDEX] = new (0x4, HEAP_ARCHIVE) AnySavesMenu();
    l_menuDrawList[MN_HUNDO_SAVES_INDEX] = new (0x4, HEAP_ARCHIVE) HundoSavesMenu();
    l_menuDrawList[MN_AD_SAVES_INDEX] = new (0x4, HEAP_ARCHIVE) ADSavesMenu();
    l_menuDrawList[MN_ACTOR_SPAWNER_INDEX] = new (0x4, HEAP_ARCHIVE) ActorSpawnMenu();
    l_menuDrawList[MN_ACTOR_LIST_INDEX] = new (0x4, HEAP_ARCHIVE) ActorListMenu();
    l_menuDrawList[MN_POS_SETTINGS_INDEX] = new (0x4, HEAP_ARCHIVE) PosSettingsMenu();
}

namespace tpgz::modules {
void main() {
    Hook::applyHooks();
    Font::loadFont("/tpgz/fonts/consola.fnt");
    Draw::init();
    initMenus();
    PosSettingsMenu::initDefaults();
    g_fifoVisible = true;
    GZ_patchLinkColor();
#ifdef WII_PLATFORM
    g_tmpBuf = new (-0x200) uint8_t[0x4000];
#endif
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
    g_drawHandler->addHandler(GZ_drawMenu);
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
    g_PreLoopHandler->addHandler(ToolsMenu::setTunicColor);
    g_PreLoopHandler->addHandler(GZ_frameAdvance);
    g_PreLoopHandler->addHandler(FreeCam::execute);
    g_PreLoopHandler->addHandler(MoveLink::execute);
    g_PreLoopHandler->addHandler(GZ_controlTools);
    // Init the post-loop handler
    g_PostLoopHandler = new PostLoopHandler();
    g_PostLoopHandler->addHandler(GZ_controlFlags_PostLoop);
    g_PostLoopHandler->addHandler(GZ_setCursorColor);
    g_PostLoopHandler->addHandler(ToolsMenu::setTunicColor);
}
void exit() {}

}  // namespace tpgz::modules