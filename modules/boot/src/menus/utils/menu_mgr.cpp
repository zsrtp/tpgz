#include "menus/utils/menu_mgr.h"
#include <cstdio>
#include "menu.h"
#include "gz_flags.h"
#include "rels/include/defines.h"

extern "C" {
KEEP_VAR MenuMgr* g_menuMgr;
}

namespace menus {
void MenuState::load(bool isCreated) {
    if (rel->isLoaded()) {
        return;
    }
    rel->loadFixed(true);
    if (isCreated && create_hook) {
        create_hook();
    }
    if (load_hook) {
        load_hook();
    }
}

void MenuState::unload(bool isDeleted) {
    if (!rel || !rel->isLoaded()) {
        return;
    }
    if (unload_hook) {
        unload_hook();
    }
    if (isDeleted && delete_hook) {
        delete_hook();
    }
    rel->close();
}

void MenuState::del() {
    if (rel->isLoaded()) {
        if (unload_hook) {
            unload_hook();
        }
    } else {
        rel->loadFixed(true);
    }
    if (delete_hook) {
        delete_hook();
    }
    rel->close();
}

MenuStateIterator::MenuStateIterator(MenuStateList* list) {
    curr = list->m_first;
}
MenuStateIterator::~MenuStateIterator() {}
MenuState* MenuStateIterator::operator*() {
    if (curr != nullptr) {
        return curr->elem;
    }
    return nullptr;
}
MenuStateIterator& MenuStateIterator::operator++() {
    if (curr != nullptr) {
        curr = curr->next;
    }
    return *this;
}
MenuStateIterator MenuStateIterator::operator++(int) {
    MenuStateIterator old = *this;
    operator++();
    return old;
}
MenuStateIterator& MenuStateIterator::operator--() {
    if (curr != nullptr) {
        curr = curr->prev;
    }
    return *this;
}
MenuStateIterator MenuStateIterator::operator--(int) {
    MenuStateIterator old = *this;
    operator--();
    return old;
}
MenuStateIterator::operator bool() const {
    return curr != nullptr && curr->elem != nullptr;
}
bool MenuStateIterator::hasNext() const {
    return curr && curr->next != nullptr;
}
bool MenuStateIterator::hasPrev() const {
    return curr && curr->prev != nullptr;
}

MenuStateConstIterator::MenuStateConstIterator(const MenuStateList* list) {
    curr = list->m_first;
}
MenuStateConstIterator::~MenuStateConstIterator() {}
const MenuState* MenuStateConstIterator::operator*() const {
    if (curr != nullptr) {
        return curr->elem;
    }
    return nullptr;
}
MenuStateConstIterator& MenuStateConstIterator::operator++() {
    if (curr != nullptr) {
        curr = curr->next;
    }
    return *this;
}
MenuStateConstIterator MenuStateConstIterator::operator++(int) {
    MenuStateConstIterator old = *this;
    operator++();
    return old;
}
MenuStateConstIterator& MenuStateConstIterator::operator--() {
    if (curr != nullptr) {
        curr = curr->prev;
    }
    return *this;
}
MenuStateConstIterator MenuStateConstIterator::operator--(int) {
    MenuStateConstIterator old = *this;
    operator--();
    return old;
}
MenuStateConstIterator::operator bool() const {
    return curr != nullptr && curr->elem != nullptr;
}
bool MenuStateConstIterator::hasNext() const {
    return curr->next != nullptr;
}
bool MenuStateConstIterator::hasPrev() const {
    return curr->prev != nullptr;
}

MenuStateList::MenuStateList() {}
MenuStateList::~MenuStateList() {
    MenuStateNode* item = getLast();
    while (item != nullptr) {
        MenuStateNode* prev = item->prev;
        delete item;
        item = prev;
    }
}
void MenuStateList::push(MenuState* state) {
    if (state == nullptr) {
        return;
    }
    MenuStateNode* item = new MenuStateNode;
    MenuStateNode* last = getLast();
    item->prev = last;
    item->next = nullptr;
    item->elem = state;
    if (last == nullptr) {
        m_first = item;
        return;
    }
    item->prev = last;
    last->next = item;
}
bool MenuStateList::remove(MenuState* state) {
    MenuStateNode* item = m_first;
    while (item != nullptr && item->elem != state) {
        item = item->next;
    }
    if (item != nullptr) {
        MenuStateNode* prev = item->prev;
        MenuStateNode* next = item->next;
        if (prev != nullptr) {
            prev->next = next;
        }
        if (next != nullptr) {
            next->prev = prev;
        }
        if (m_first == item) {
            m_first = nullptr;
        }
        delete item;
        return true;
    }
    return false;
}
MenuStateIterator MenuStateList::begin() {
    return MenuStateIterator(this);
}
MenuStateConstIterator MenuStateList::begin() const {
    return MenuStateConstIterator(this);
}
MenuStateIterator MenuStateList::end() {
    MenuStateIterator it = begin();
    while (it.hasNext()) {
        ++it;
    }
    return it;
}
MenuStateConstIterator MenuStateList::end() const {
    MenuStateConstIterator it = begin();
    while (it.hasNext()) {
        ++it;
    }
    return it;
}
MenuStateNode* MenuStateList::getLast() {
    if (m_first == nullptr) {
        return nullptr;
    }
    MenuStateNode* item = m_first;
    while (item->next != nullptr) {
        item = item->next;
    }
    return item;
}
}  // namespace menus

KEEP_FUNC MenuMgr::MenuMgr() : is_open(false) {}
KEEP_FUNC MenuMgr::~MenuMgr() {}

KEEP_FUNC bool MenuMgr::isOpen() const {
    return is_open;
}

KEEP_FUNC size_t MenuMgr::getStackSize() const {
    size_t count = 0;
    for (auto it = states.begin(); it; ++it) {
        ++count;
    }
    return count;
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
    auto end = states.end();
    if (!end) {
        is_open = false;
        return;
    }
    if (is_open) {
        return;
    }
    auto state = *end;
    state->load(false);
    is_open = true;
}
KEEP_FUNC void MenuMgr::handleHide() {
    auto end = states.end();
    if (!end || !(*end)->rel->isLoaded()) {
        is_open = false;
    }
    if (!is_open) {
        return;
    }
    auto state = *end;
    state->unload(false);
    is_open = false;
    GZ_setFifoVisible(true);
}

KEEP_FUNC void MenuMgr::handlePush(int menu_id) {
    if (menu_id <= MN_NONE_INDEX || menu_id >= MN_COUNT) {
        // If menu ID is invalid, do nothing.
        return;
    }
    auto end = states.end();
    if (is_open && end) {
        // Hide the currently opened menu, but keep it on the stack.
        menus::MenuState* state = *end;
        state->unload(false);
    }
    menus::MenuState* state = new menus::MenuState();
    state->id = menu_id;
    char buf[64];
    snprintf(buf, sizeof(buf), "/tpgz/rels/menus/menu_%s.rel", g_menuPaths[menu_id]);
    state->rel = new tpgz::dyn::GZModule(buf);
    states.push(state);
    state->load(true);
    is_open = true;
}

KEEP_FUNC void MenuMgr::handlePop() {
    auto end = states.end();
    if (end) {
        menus::MenuState* state = *(end--);
        state->del();
        states.remove(state);
        delete state->rel;
        delete state;
    }

    if (end && is_open) {
        menus::MenuState* state = *end;
        state->load(false);
    }

    if (!end) {
        is_open = false;
        GZ_setFifoVisible(true);
    }
}

KEEP_FUNC void MenuMgr::handleClear() {
    auto it = states.end();
    while (it) {
        menus::MenuState* state = *(it--);
        state->del();
        states.remove(state);
        delete state->rel;
        delete state;
    }
    is_open = false;
    GZ_setFifoVisible(true);
}

KEEP_FUNC void MenuMgr::setPersistentData(void* data) {
    auto state = *states.end();
    if (state) {
        state->data = data;
    }
}

KEEP_FUNC void* MenuMgr::getPersistentData() {
    auto state = *states.end();
    if (state) {
        return state->data;
    }
    return nullptr;
}

KEEP_FUNC void MenuMgr::setCreateHook(void (*createHook)()) {
    auto state = *states.end();
    if (state) {
        state->create_hook = createHook;
    }
}

KEEP_FUNC void MenuMgr::setLoadHook(void (*loadHook)()) {
    auto state = *states.end();
    if (state) {
        state->load_hook = loadHook;
    }
}

KEEP_FUNC void MenuMgr::setUnloadHook(void (*unloadHook)()) {
    auto state = *states.end();
    if (state) {
        state->unload_hook = unloadHook;
    }
}

KEEP_FUNC void MenuMgr::setDeleteHook(void (*deleteHook)()) {
    auto state = *states.end();
    if (state) {
        state->delete_hook = deleteHook;
    }
}
