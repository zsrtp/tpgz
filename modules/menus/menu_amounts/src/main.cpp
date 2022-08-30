#include <main.h>
#include "menus/menu_amounts/include/amounts_menu.h"
#include "events/draw_listener.h"
#include "menus/utils/menu_mgr.h"
#include "utils/draw.h"

void onCreate();
void onLoad();
void onDraw();
void onUnload();
void onDelete();

AmountsMenu* l_menu;

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
    g_menuMgr->setPersistentData(new AmountsData);
    if (!g_menuMgr->getPermanentData<Cursor>()) {
        g_menuMgr->setPermanentData(new Cursor);
    }
}

void onLoad() {
    l_menu = new AmountsMenu(*g_menuMgr->getPermanentData<Cursor>(),
                             *g_menuMgr->getPersistentData<AmountsData>());
    g_drawListener->addListener(onDraw);
}

void onDraw() {
    l_menu->draw();
}

void onUnload() {
    g_drawListener->removeListener(onDraw);
    delete l_menu;
}

void onDelete() {
    auto data = g_menuMgr->getPersistentData<AmountsData>();
    delete data;
    g_menuMgr->setPersistentData<AmountsData>(nullptr);
}
