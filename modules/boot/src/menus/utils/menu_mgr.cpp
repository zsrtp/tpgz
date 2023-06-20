#include "menus/utils/menu_mgr.h"
#include <cstdio>
#include <iterator>
#include "menu.h"
#include "gz_flags.h"
#include "rels/include/defines.h"

KEEP_VAR MenuMgr* g_menuMgr;

namespace menus {
MenuState::MenuState(int id, const char* relPath) : id(id), rel(relPath) {}
MenuState::~MenuState() {}
void MenuState::load(bool isCreated) {
    if (rel.isLoaded()) {
        return;
    }
    rel.loadFixed(true);
    if (isCreated && create_hook) {
        create_hook();
    }
    if (load_hook) {
        load_hook();
    }
}

void MenuState::unload(bool isDeleted) {
    if (!rel.isLoaded()) {
        return;
    }
    if (unload_hook) {
        unload_hook();
    }
    if (isDeleted && delete_hook) {
        delete_hook();
    }
    rel.close();
}

void MenuState::del() {
    if (rel.isLoaded()) {
        if (unload_hook) {
            unload_hook();
        }
    } else {
        rel.loadFixed(true);
    }
    if (delete_hook) {
        delete_hook();
    }
    rel.close();
}
}  // namespace menus

KEEP_FUNC MenuMgr::MenuMgr() : is_open(false) {}
KEEP_FUNC MenuMgr::~MenuMgr() {}

KEEP_FUNC bool MenuMgr::isOpen() const {
    return is_open;
}

KEEP_FUNC size_t MenuMgr::getStackSize() const {
    return states.size();
}

KEEP_FUNC bool MenuMgr::isEmpty() const {
    return states.empty();
}

void MenuMgr::handleCommands() {
    if (command.cmd_id == menus::MC_NONE) {
        return;
    }
    switch (command.cmd_id) {
    case menus::MC_OPEN:
        handleOpen();
        break;
    case menus::MC_HIDE:
        handleHide();
        break;
    case menus::MC_PUSH:
        handlePush(command.menu_id);
        break;
    case menus::MC_POP:
        handlePop();
        break;
    case menus::MC_CLEAR:
        handleClear();
        break;
    case menus::MC_NONE:
        break;
    }
    command = {menus::MC_NONE, MN_NONE_INDEX};
}

KEEP_FUNC void MenuMgr::open() {
    command = {menus::MC_OPEN, MN_NONE_INDEX};
}
KEEP_FUNC void MenuMgr::hide() {
    command = {menus::MC_HIDE, MN_NONE_INDEX};
}

KEEP_FUNC void MenuMgr::push(int menu_id) {
    command = {menus::MC_PUSH, menu_id};
}
KEEP_FUNC void MenuMgr::pop() {
    command = {menus::MC_POP, MN_NONE_INDEX};
}
KEEP_FUNC void MenuMgr::clear() {
    command = {menus::MC_CLEAR, MN_NONE_INDEX};
}

KEEP_FUNC void MenuMgr::handleOpen() {
    if (states.empty()) {
        is_open = false;
        return;
    }
    if (is_open) {
        return;
    }
    auto state = *states.begin();
    state->load(false);
    is_open = true;
    GZ_setFifoVisible(false);
}
KEEP_FUNC void MenuMgr::handleHide() {
    if (states.empty() || !(*states.begin())->rel.isLoaded()) {
        is_open = false;
    }
    if (!is_open) {
        return;
    }
    auto state = *states.begin();
    state->unload(false);
    is_open = false;
    GZ_setFifoVisible(true);
}

KEEP_FUNC void MenuMgr::handlePush(int menu_id) {
    if (menu_id <= MN_NONE_INDEX || menu_id >= MN_COUNT) {
        // If menu ID is invalid, do nothing.
        return;
    }
    if (is_open && !states.empty()) {
        // Hide the currently opened menu, but keep it on the stack.
        menus::MenuState* state = *states.begin();
        state->unload(false);
    }
    char buf[45];
    snprintf(buf, sizeof(buf), "/tpgz/rels/menus/menu_%s.rel", g_menuPaths[menu_id]);
    auto* state = new menus::MenuState(menu_id, buf);
    states.push(state);
    state->load(true);
    is_open = true;
    GZ_setFifoVisible(false);
}

KEEP_FUNC void MenuMgr::handlePop() {
    if (!states.empty()) {
        menus::MenuState* state = *states.begin();
        state->del();
        states.pop();
        delete state;
    }

    if (!states.empty() && is_open) {
        menus::MenuState* state = *states.begin();
        state->load(false);
        GZ_setFifoVisible(false);
    }

    if (states.empty()) {
        is_open = false;
        GZ_setFifoVisible(true);
    }
}

KEEP_FUNC void MenuMgr::handleClear() {
    while (!states.empty()) {
        menus::MenuState* state = *states.begin();
        state->del();
        states.pop();
        delete state;
    }
    is_open = false;
    GZ_setFifoVisible(true);
}

KEEP_FUNC void MenuMgr::setCreateHook(void (*createHook)()) {
    if (!states.empty()) {
        (*states.begin())->create_hook = createHook;
    }
}

KEEP_FUNC void MenuMgr::setLoadHook(void (*loadHook)()) {
    if (!states.empty()) {
        (*states.begin())->load_hook = loadHook;
    }
}

KEEP_FUNC void MenuMgr::setUnloadHook(void (*unloadHook)()) {
    if (!states.empty()) {
        (*states.begin())->unload_hook = unloadHook;
    }
}

KEEP_FUNC void MenuMgr::setDeleteHook(void (*deleteHook)()) {
    if (!states.empty()) {
        (*states.begin())->delete_hook = deleteHook;
    }
}
