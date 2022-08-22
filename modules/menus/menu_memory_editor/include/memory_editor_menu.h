#include "menu.h"

class MemoryEditorMenu : public Menu {
public:
    MemoryEditorMenu(Cursor&);
    virtual ~MemoryEditorMenu();
    virtual void draw();

private:
    void drawMemEditor();

    Cursor& cursor;
};
