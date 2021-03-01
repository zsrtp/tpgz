#include "menu.h"

#define MEMFILE_SLOT_INDEX 0
#define MEMFILE_SAVE_INDEX 1
#define MEMFILE_LOAD_INDEX 2

struct PositionData {
    Vec3 link;
    CameraMatrix cam;
    uint16_t angle;
};

extern bool set_position_data;
extern int8_t memfile_load_delay;
extern PositionData memfile_posdata;

void set_memfile_position();

class MemfilesMenu : public Menu {
public:
    MemfilesMenu() : Menu() {}
    static void render();
};