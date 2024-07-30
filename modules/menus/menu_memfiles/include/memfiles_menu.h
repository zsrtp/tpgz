#include "menus/menu.h"
#include "libtp_c/include/dolphin/mtx/vec.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"

#define MEMFILE_SLOT_INDEX 0
#define MEMFILE_SAVE_INDEX 1
#define MEMFILE_LOAD_INDEX 2
#define MEMFILE_DELETE_INDEX 3

struct MemfilesData {
    Cursor cursor;
    uint8_t l_fileNo = 1;
};

class MemfilesMenu : public Menu {
public:
    MemfilesMenu(MemfilesData&);
    virtual ~MemfilesMenu();
    virtual void draw();

private:
    uint8_t& l_fileNo;

    Line lines[4];
};