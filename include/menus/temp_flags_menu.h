#include "menu.h"

struct AreaNode {
    uint8_t offset;
    bool bit[8];
    bool line_selected = false;
};

class TempFlagsMenu : public Menu {
public:
    TempFlagsMenu() : Menu() {}
    static void render(Font& font);
};