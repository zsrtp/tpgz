#include "menu.h"

enum MainMenuIndex {
    CHEAT_INDEX,
    FLAGS_INDEX,
    INVENTORY_INDEX,
    MEMORY_INDEX,
    PRACTICE_INDEX,
    SCENE_INDEX,
    SETTINGS_INDEX,
    TOOLS_INDEX,
    WARPING_INDEX,
};

class MainMenu : public Menu {
public:
    MainMenu(Cursor&);
    virtual ~MainMenu();
    virtual void draw();

    Cursor& m_cursor;

private:
    Line lines[9];
};