#include <main.h>
#include "menus/menu_settings/include/settings_menu.h"
#include "handlers/draw_handler.h"
#include "menus/utils/menu_mgr.h"
#include "utils/draw.h"

void onCreate();
void onLoad();
void onDraw();
void onUnload();
void onDelete();

SettingsMenu* l_settingsMenu;

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
    if (!g_menuMgr->getPermanentData<Cursor>()) {
        g_menuMgr->setPermanentData(new Cursor);
    }
}

void onLoad() {
    l_settingsMenu = new SettingsMenu(*g_menuMgr->getPermanentData<Cursor>());
    g_drawHandler->addHandler(onDraw);
}

void onDraw() {
    l_settingsMenu->draw();
}

void onUnload() {
    g_drawHandler->removeHandler(onDraw);
    delete l_settingsMenu;
}

void onDelete() {
}
