#include "menu.h"
#include "libtp_c/include/dolphin/mtx/vec.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"

#define MEMFILE_SLOT_INDEX 0
#define MEMFILE_SAVE_INDEX 1
#define MEMFILE_LOAD_INDEX 2
#define MEMFILE_DELETE_INDEX 3

struct PositionData {
    cXyz link;
    CameraMatrix cam;
    uint16_t angle;
};

extern bool set_position_data;
extern bool g_injectMemfile;
extern int8_t memfile_load_delay;
extern PositionData memfile_posdata;

class MemfilesMenu : public Menu {
public:
    MemfilesMenu();
    virtual void draw();
    static void setLinkPosition();

    Cursor cursor;

private:
    Line lines[4];
};