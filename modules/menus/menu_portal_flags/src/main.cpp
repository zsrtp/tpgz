#include <main.h>
#include "menus/menu_portal_flags/include/portal_flags_menu.h"
#include "handlers/draw_handler.h"
#include "menus/utils/menu_mgr.h"
#include "utils/draw.h"

void onCreate();
void onLoad();
void onDraw();
void onUnload();
void onDelete();

PortalFlagsMenu* l_menu;

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
    g_menuMgr->setPersistentData(new PortalFlagsData);
    if (!g_menuMgr->getPermanentData<Cursor>()) {
        g_menuMgr->setPermanentData(new Cursor);
    }
}

void onLoad() {
    l_menu = new PortalFlagsMenu(*g_menuMgr->getPermanentData<Cursor>(), *g_menuMgr->getPersistentData<PortalFlagsData>());
    g_drawHandler->addHandler(onDraw);
}

void onDraw() {
    l_menu->draw();
}

void onUnload() {
    g_drawHandler->removeHandler(onDraw);
    delete l_menu;
}

void onDelete() {
    auto data = g_menuMgr->getPersistentData<PortalFlagsData>();
    delete (PortalFlagsData*)data;
    g_menuMgr->setPersistentData<PortalFlagsData>(nullptr);
}
