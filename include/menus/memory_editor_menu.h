#include "menu.h"

struct MemoryLine {
    bool line_selected = false;
    bool value_selected = false;
};

class MemoryEditorMenu : public Menu {
public:
    MemoryEditorMenu() : Menu() {}
    static void render();
};

extern uint32_t address_index;
