#include "menu.h"

enum PauseIndex {
    ORDON_SWORD_INDEX,
    MASTER_SWORD_INDEX,
    WOOD_SHIELD_INDEX,
    HYLIAN_SHIELD_INDEX,
    HERO_TUNIC_INDEX,
    ZORA_ARMOR_INDEX,
    MAGIC_ARMOR_INDEX,
    BOMB_CAPACITY_INDEX,
    WALLET_INDEX,
    ARROW_CAPACITY_INDEX,
    ENDING_BLOW_INDEX,
    SHIELD_BASH_INDEX,
    BACKSLICE_INDEX,
    HELM_SPLITTER_INDEX,
    MORTAL_DRAW_INDEX,
    JUMP_STRIKE_INDEX,
    GREAT_SPIN_INDEX
};

class PauseMenu : public Menu {
   public:
    PauseMenu() : Menu() {}
    static void render();
};