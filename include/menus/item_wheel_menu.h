#include "menu.h"
#include "libtp_c/include/d/save/d_save.h"

struct ItemLookup {
    enum ItemTable item_id;
    char name[40];
};

class ItemWheelMenu : public Menu {
public:
    ItemWheelMenu() : Menu() {}
    static void draw();
    static void updateListIdx();
    static void fixSpecialItems(int i);

    static Cursor cursor;
};