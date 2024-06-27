#ifndef TPGZ_MENUS_UTILS_MENU_MGR_H
#define TPGZ_MENUS_UTILS_MENU_MGR_H

#include <cstddef>
#include <boot/include/utils/containers/stack.h>
#include "utils/rels.h"
#include "utils/cursor.h"
#include "menus/menu.h"

// Namespace for internal classes.
namespace menus {
struct MenuState {
    MenuState(int id, const char* relPath);
    virtual ~MenuState();
    int id;
    tpgz::dyn::GZModule rel;
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
    bool isEmpty() const;

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
    template <typename T = void>
    inline void setPersistentData(T* data) {
        if (!states.empty()) {
            (*states.begin())->data = data;
        }
    }
    /**
     * @brief Get the Persistent Data object of the current menu.
     *
     * @return void* Pointer to the data kept between load/unload.
     */
    template <typename T = void>
    inline T* getPersistentData() {
        if (!states.empty()) {
            return (T*)(*states.begin())->data;
        }
        return nullptr;
    }

    /**
     * @brief Set the Permanent Data object of the current menu.
     *
     * @param data Pointer to the data to keep all the time.
     */
    template <typename T = void>
    inline void setPermanentData(T* data) {
        if (!states.empty()) {
            permanentData[(*states.begin())->id] = data;
        }
    }
    /**
     * @brief Get the Permanent Data object of the current menu.
     *
     * @return void* Pointer to the data kept all the time.
     */
    template <typename T = void>
    inline T* getPermanentData() {
        if (!states.empty()) {
            return (T*)permanentData[(*states.begin())->id];
        }
        return nullptr;
    }

    /**
     * @brief Set the function to call when loading the menu for the first
     *        time. It's a good place to setup the persistent data for the
     *        menu. (Acts on the top module of the stack)
     *
     * @param createHook
     */
    void setCreateHook(void (*createHook)());
    /**
     * @brief Set the function to call everytime we load the menu.
     *        It's a good place to hook the module's functions to the
     *        appropriate listeners. (Acts on the top module of the stack)
     *
     * @param loadHook
     */
    void setLoadHook(void (*loadHook)());
    /**
     * @brief Set the function to call everytime we unload the menu.
     *        (Acts on the top module of the stack)
     *
     * @param unloadHook
     */
    void setUnloadHook(void (*unloadHook)());
    /**
     * @brief Set the function to call right before unloading and destroying
     *        the menu. It's a good place to destroy the persistent data.
     *        (Acts on the top module of the stack)
     *
     * @param deleteHook
     */
    void setDeleteHook(void (*deleteHook)());

private:
    tpgz::containers::stack<menus::MenuState*> states;
    void* permanentData[MN_COUNT];
    bool is_open;
    menus::MenuCommand command;

    void handleOpen();
    void handleHide();

    void handlePush(int menu_id);
    void handlePop();
    void handleClear();
};

extern MenuMgr* g_menuMgr;

#endif  // !TPGZ_MENUS_UTILS_MENU_MGR_H