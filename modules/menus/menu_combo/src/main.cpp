#include <main.h>
#include "menus/menu_combo/include/combo_menu.h"
#include "events/draw_listener.h"
#include "events/pre_loop_listener.h"
#include "menus/utils/menu_mgr.h"
#include "utils/draw.h"

void onCreate();
void onLoad();
void onPreLoop();
void onDraw();
void onUnload();
void onDelete();

ComboMenu* l_comboMenu;

namespace tpgz::modules {
void main() {
    g_menuMgr->setCreateHook(onCreate);
    g_menuMgr->setLoadHook(onLoad);
    g_menuMgr->setUnloadHook(onUnload);
    g_menuMgr->setDeleteHook(onDelete);
}
void exit() {
    g_menuMgr->setCreateHook(nullptr);
    g_menuMgr->setLoadHook(nullptr);
    g_menuMgr->setUnloadHook(nullptr);
    g_menuMgr->setDeleteHook(nullptr);
}
}  // namespace tpgz::modules

void onCreate() {
    g_menuMgr->setPersistentData(new ComboData());
    if (!g_menuMgr->getPermanentData<Cursor>()) {
        g_menuMgr->setPermanentData(new Cursor);
    }
}

void onLoad() {
    l_comboMenu = new ComboMenu(*g_menuMgr->getPermanentData<Cursor>(),
                                *g_menuMgr->getPersistentData<ComboData>());
    g_drawListener->addListener(onDraw);
    g_PreLoopListener->addListener(onPreLoop);
}

void onPreLoop() {
    l_comboMenu->execute();
}

void onDraw() {
    l_comboMenu->draw();
}

void onUnload() {
    g_PreLoopListener->removeListener(onPreLoop);
    g_drawListener->removeListener(onDraw);
    delete l_comboMenu;
}

void onDelete() {
    auto data = g_menuMgr->getPersistentData<ComboData>();
    delete data;
    g_menuMgr->setPersistentData<ComboData>(nullptr);
}
