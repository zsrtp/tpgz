#include "menu.h"

enum ItemID {
    OOCCOO_SR = 37,
    OOCCOO_JR = 39,
    OOCCOOS_NOTE = 45,
    HAWKEYE = 62,
    GALE_BOOMERANG = 64,
    SPINNER,
    BALL_AND_CHAIN,
    HEROS_BOW,
    CLAWSHOT,
    IRON_BOOTS,
    DOMINION_ROD,
    DOUBLE_CLAWSHOT,
    LANTERN,
    MASTER_SWORD,
    FISHING_ROD,
    SLINGSHOT,
    EMPTY_BOMBBAG = 80,
    ROD_BEE_LARVA = 91,
    ROD_CORAL_EARRING,
    ROD_WORM,
    ROD_CORAL_EARRING_BEE_LARVA,
    ROD_CORAL_EARRING_WORM,
    EMPTY_BOTTLE,
    RED_POTION,
    MAGIC_POTION,
    BLUE_POTION,
    MILK,
    HALF_MILK,
    LANTERN_OIL,
    WATER,
    NASTY_SOUP = 106,
    HOT_SPRING_WATER,
    FAIRY,
    REGULAR_BOMBS = 112,
    WATER_BOMBS,
    BOMBLINGS,
    FAIRY_TEARS,
    WORM,
    BEE_LARVA = 118,
    RARE_CHU,
    RED_CHU,
    BLUE_CHU,
    GREEN_CHU,
    YELLOW_CHU,
    PURPLE_CHU,
    SIMPLE_SOUP,
    GOOD_SOUP,
    SUPERB_SOUP,
    RENADOS_LETTER,
    INVOICE,
    WOODEN_STATUE,
    ILIAS_CHARM,
    HORSE_CALL,
    AURUS_MEMO = 144,
    ASHEIS_SKETCH,
    ANCIENT_SKY_BOOK_EMPTY = 233,
    ANCIENT_SKY_BOOK_PARTIAL,
    ANCIENT_SKY_BOOK_FILLED,
    NO_ITEM = 255
};

enum Slot {
    SLOT_0,
    SLOT_1,
    SLOT_2,
    SLOT_3,
    SLOT_4,
    SLOT_5,
    SLOT_6,
    SLOT_7,
    SLOT_8,
    SLOT_9,
    SLOT_10,
    SLOT_11,
    SLOT_12,
    SLOT_13,
    SLOT_14,
    SLOT_15,
    SLOT_16,
    SLOT_17,
    SLOT_18,
    SLOT_19,
    SLOT_20,
    SLOT_21,
    SLOT_22,
    SLOT_23
};

struct ItemLookup {
    enum ItemID item_id;
    char item_description[40];
};

class ItemWheelMenu : public Menu {
public:
    ItemWheelMenu() : Menu() {}
    static void render(Font& font);
};