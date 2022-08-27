#ifndef TPGZ_MENUS_UTILS_MENU_MGR_H
#define TPGZ_MENUS_UTILS_MENU_MGR_H

#include <stddef.h>
#include "utils/rels.h"

// Namespace for internal classes.
namespace menus {
struct MenuState {
    int id;
    tpgz::dyn::GZModule* rel;
    void* data;
    // Lifecyce hooks
    void (*create_hook)();
    void (*load_hook)();
    void (*unload_hook)();
    void (*delete_hook)();

    /**
     * @brief   If the menu has not already been loaded, loads the module, and call the load hook.
     *          Otherwise, does nothing.
     *
     * @param isCreated If true, calls the create hook before the load hook.
     */
    void load(bool isCreated);
    /**
     * @brief   If the menu has already been loaded, calls the unload hook, and unloads the module.
     *          Otherwise, does nothing.
     *
     * The difference with `del()` is that unload does not load the module if it wasn't already
     * loaded. And del() will call the delete hook in every case. unload() will call it only if
     * requested.
     *
     * @param isDeleted If true, calls the delete hook after the unload hook.
     */
    void unload(bool isDeleted);
    /**
     * @brief   If the menu is loaded, calls the unload hook, then calls the delete hook, and then
     *          unload the module.
     *          Otherwise, loads the module, then calls the delete hook, and then unloads the
     * module.
     *
     * The difference with `unload()` is that del will load the module if it wasn't already loaded.
     * And unload() will call the unload hook in every case. del() will only call the unload hook if
     * the module was already loaded.
     *
     */
    void del();
};
struct MenuStateNode {
    MenuStateNode* prev;
    MenuStateNode* next;
    MenuState* elem;
};

class MenuStateList;

class MenuStateIterator {
    MenuStateNode* curr;

public:
    MenuStateIterator(MenuStateList* list);
    virtual ~MenuStateIterator();

    MenuState* operator*();
    MenuStateIterator& operator++();
    MenuStateIterator operator++(int);
    MenuStateIterator& operator--();
    MenuStateIterator operator--(int);
    inline bool operator==(const MenuStateIterator& rhs) const { return this->curr == rhs.curr; }
    operator bool() const;

    bool hasNext() const;
    bool hasPrev() const;
};

class MenuStateConstIterator {
    const MenuStateNode* curr;

public:
    MenuStateConstIterator(const MenuStateList* list);
    virtual ~MenuStateConstIterator();

    const MenuState* operator*() const;
    MenuStateConstIterator& operator++();
    MenuStateConstIterator operator++(int);
    MenuStateConstIterator& operator--();
    MenuStateConstIterator operator--(int);
    inline bool operator==(const MenuStateConstIterator& rhs) const {
        return this->curr == rhs.curr;
    }
    operator bool() const;

    bool hasNext() const;
    bool hasPrev() const;
};

class MenuStateList {
public:
    MenuStateList();
    virtual ~MenuStateList();

    void push(MenuState* elem);
    bool remove(MenuState* elem);

    MenuStateIterator begin();
    MenuStateConstIterator begin() const;
    MenuStateIterator end();
    MenuStateConstIterator end() const;

private:
    MenuStateNode* m_first;

    MenuStateNode* getLast();

public:
    friend class MenuStateConstIterator;
    friend class MenuStateIterator;
};

enum MenuCommandId { MC_NONE, MC_OPEN, MC_HIDE, MC_PUSH, MC_POP, MC_CLEAR };

struct MenuCommand {
    MenuCommandId cmd_id;
    int menu_id;
};
}  // namespace menus

class MenuMgr {
public:
    MenuMgr();
    virtual ~MenuMgr();

    bool isOpen() const;

    size_t getStackSize() const;

    void handleCommands();

    void open();
    void hide();

    /**
     * @brief Push a new menu on the stack.
     *
     * @param menu_id Id of the menu to load
     */
    void push(int menu_id);
    /**
     * @brief Removes the last menu from the stack.
     *
     */
    void pop();
    /**
     * @brief Removes all menus from the stack.
     *
     */
    void clear();

    /**
     * @brief Set the Persistent Data object of the current menu.
     *
     * @param data Pointer to the data to keep between load/unload.
     */
    void setPersistentData(void* data);
    /**
     * @brief Get the Persistent Data object of the current menu.
     *
     * @return void* Pointer to the data kept between load/unload.
     */
    void* getPersistentData();
    /**
     * @brief Set the function to call when loading the menu for the first
     *        time. It's a good place to setup the persistent data for the
     *        menu.
     *
     * @param createHook
     */
    void setCreateHook(void (*createHook)());
    /**
     * @brief Set the function to call everytime we load the menu.
     *        It's a good place to hook the module's functions to the
     *        appropriate handlers.
     *
     * @param loadHook
     */
    void setLoadHook(void (*loadHook)());
    /**
     * @brief Set the function to call everytime we unload the menu.
     *
     * @param unloadHook
     */
    void setUnloadHook(void (*unloadHook)());
    /**
     * @brief Set the function to call right before unloading and destroying
     *        the menu. It's a good place to destroy the persistent data.
     *
     * @param deleteHook
     */
    void setDeleteHook(void (*deleteHook)());

private:
    menus::MenuStateList states;
    bool is_open;
    menus::MenuCommand command;

    void handleOpen();
    void handleHide();

    void handlePush(int menu_id);
    void handlePop();
    void handleClear();
};

extern "C" {
extern MenuMgr* g_menuMgr;
}

#endif  // !TPGZ_MENUS_UTILS_MENU_MGR_H