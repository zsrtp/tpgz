#include "menu.h"

class MemoryEditorMenu : public Menu {
public:
    MemoryEditorMenu();
    virtual void draw();
    static uint32_t mAddressIndex;
private:
    void drawMemEditor();

    Cursor cursor;
};
