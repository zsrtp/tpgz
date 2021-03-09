#include "menu.h"

#define ANY_INDEX 0
#define HUNDO_INDEX 1
#define AD_INDEX 2
#define REQ_POS 1
#define REQ_CAM 2
extern bool inject_save_flag;
extern int last_save_index;
extern char last_category[5];
CameraMatrix camera;
uint16_t angle = 0;
Vec3 position = {0, 0, 0};

struct PracticeSaveInfo {
    uint8_t requirements;
    uint8_t _p0[1];
    uint16_t angle;
    Vec3 position;
    Vec3 cam_pos;
    Vec3 cam_target;
    uint32_t counter;
    char filename[32];
    uint8_t _p1[4];
} __attribute__((packed));

class PracticeMenu : public Menu {
public:
    PracticeMenu() : Menu() {}
    static void render();
};