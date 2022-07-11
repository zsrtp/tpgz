#include "menu.h"

class MemoryEditorMenu : public Menu {
public:
    MemoryEditorMenu() : Menu() {}
    static void draw();
    static void drawMemEditor();

    static Cursor cursor;
    static uint32_t mAddressIndex;
};
