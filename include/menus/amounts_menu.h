#include "menu.h"

enum AmountsIndex {
    ARROW_AMMO_INDEX,
    BOMB_BAG_1_AMMO_INDEX,
    BOMB_BAG_2_AMMO_INDEX,
    BOMB_BAG_3_AMMO_INDEX,
    SLINGSHOT_AMMO_INDEX,
    HEART_PIECE_COUNT_INDEX,
    POE_COUNT_INDEX,
    RUPEE_COUNT_INDEX
};

class AmountsMenu : public Menu {
public:
    AmountsMenu() : Menu() {}
    static void render();
};