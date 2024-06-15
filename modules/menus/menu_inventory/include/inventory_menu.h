#include "menus/menu.h"

#define ITEM_WHEEL_INDEX 0
#define PAUSE_MENU_INDEX 1
#define AMOUNTS_MENU_INDEX 2

class InventoryMenu : public Menu {
public:
    InventoryMenu(Cursor&);
    virtual ~InventoryMenu();
    virtual void draw();

private:
    Line lines[3];
};