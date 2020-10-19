#include "menu.h"

#define SPRITES_AMNT 7
enum SpritesIndex {
    MENU_INDEX = 0,
    VIEWER_INDEX = 1,
    DEBUG_INFO_INDEX = 2,
    TIMER_SPR_INDEX = 3,
    LOAD_TIMER_SPR_INDEX = 4,
    IGT_TIMER_SPR_INDEX = 5,
    FIFO_SPR_INDEX = 6
};

extern Vec2 sprite_offsets[SPRITES_AMNT];

class PosSettingsMenu : public Menu {
   public:
    static void initDefaults();
    PosSettingsMenu() : Menu() {}
    static void render();
};