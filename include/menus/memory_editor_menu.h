#include "menu.h"

class MemoryEditorMenu : public Menu {
public:
    MemoryEditorMenu() : Menu() {}
    static void render();
};

extern uint32_t address_index;
