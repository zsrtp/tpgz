
#include "menus/item_wheel_menu.h"
#include "font.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/msl_c/string.h"
#include "gz_flags.h"

#define ITEM_WHEEL_SLOTS 24
#define LINE_NUM ITEM_WHEEL_SLOTS
#define MAX_ITEMS 58

#ifdef GCN_PLATFORM
#define DEFAULT_BTN_TXT "Z"
#define DEFAULT_BTN GZPad::Z
#endif

#ifdef WII_PLATFORM
#define DEFAULT_BTN_TXT "+"
#define DEFAULT_BTN GZPad::PLUS
#endif

Cursor ItemWheelMenu::cursor;

const uint8_t l_validItems[] = {
    DUNGEON_EXIT,    DUNGEON_BACK,
    TKS_LETTER,      HAWK_EYE,
    BOOMERANG,       SPINNER,
    IRONBALL,        BOW,
    HOOKSHOT,        HVY_BOOTS,
    COPY_ROD,        W_HOOKSHOT,
    KANTERA,         MASTER_SWORD,
    FISHING_ROD_1,   PACHINKO,
    BOMB_BAG_LV1,    BEE_ROD,
    JEWEL_ROD,       WORM_ROD,
    JEWEL_BEE_ROD,   JEWEL_WORM_ROD,
    EMPTY_BOTTLE,    RED_BOTTLE,
    GREEN_BOTTLE,    BLUE_BOTTLE,
    MILK_BOTTLE,     HALF_MILK_BOTTLE,
    OIL_BOTTLE,      WATER_BOTTLE,
    UGLY_SOUP,       HOT_SPRING,
    FAIRY,           NORMAL_BOMB,
    WATER_BOMB,      POKE_BOMB,
    FAIRY_DROP,      WORM,
    BEE_CHILD,       CHUCHU_RARE,
    CHUCHU_RED,      CHUCHU_BLUE,
    CHUCHU_GREEN,    CHUCHU_YELLOW,
    CHUCHU_PURPLE,   LV1_SOUP,
    LV2_SOUP,        LV3_SOUP,
    LETTER,          BILL,
    WOOD_STATUE,     IRIAS_PENDANT,
    HORSE_FLUTE,     RAFRELS_MEMO,
    ASHS_SCRIBBLING, ANCIENT_DOCUMENT,
    AIR_LETTER,      ANCIENT_DOCUMENT2,
    NO_ITEM,
};

const uint8_t l_defaultItems[ITEM_WHEEL_SLOTS] = {
    BOOMERANG,     KANTERA,      SPINNER,          HVY_BOOTS,    BOW,
    HAWK_EYE,      IRONBALL,     NO_ITEM,          COPY_ROD,     HOOKSHOT,
    W_HOOKSHOT,    EMPTY_BOTTLE, EMPTY_BOTTLE,     EMPTY_BOTTLE, EMPTY_BOTTLE,
    BOMB_BAG_LV1,  BOMB_BAG_LV1, BOMB_BAG_LV1,     DUNGEON_EXIT, RAFRELS_MEMO,
    FISHING_ROD_1, HORSE_FLUTE,  ANCIENT_DOCUMENT, PACHINKO,
};

const ItemLookup l_lookupTbl[MAX_ITEMS] = {
    {DUNGEON_EXIT, "Ooccoo Sr."},
    {DUNGEON_BACK, "Ooccoo Jr."},
    {TKS_LETTER, "Ooccoo's note"},
    {HAWK_EYE, "hawkeye"},
    {BOOMERANG, "gale boomerang"},
    {SPINNER, "spinner"},
    {IRONBALL, "ball and chain"},
    {BOW, "hero's bow"},
    {HOOKSHOT, "clawshot"},
    {HVY_BOOTS, "iron boots"},
    {COPY_ROD, "dominion rod"},
    {W_HOOKSHOT, "double clawshot"},
    {KANTERA, "lantern"},
    {PACHINKO, "slingshot"},
    {FISHING_ROD_1, "fishing rod"},
    {BOMB_BAG_LV1, "empty bomb bag"},
    {BEE_ROD, "fishing rod (bee larva)"},
    {JEWEL_ROD, "fishing rod (coral earring)"},
    {WORM_ROD, "fishing rod (worm)"},
    {JEWEL_BEE_ROD, "fishing rod (coral earring/bee larva)"},
    {JEWEL_WORM_ROD, "fishing rod (coral earring/worm)"},
    {EMPTY_BOTTLE, "empty bottle"},
    {RED_BOTTLE, "red potion"},
    {GREEN_BOTTLE, "magic potion"},
    {BLUE_BOTTLE, "blue potion"},
    {MILK_BOTTLE, "milk"},
    {HALF_MILK_BOTTLE, "half milk"},
    {OIL_BOTTLE, "lantern oil"},
    {WATER_BOTTLE, "water"},
    {UGLY_SOUP, "nasty soup"},
    {HOT_SPRING, "hot spring water"},
    {FAIRY, "fairy"},
    {NORMAL_BOMB, "regular bombs"},
    {WATER_BOMB, "water bombs"},
    {POKE_BOMB, "bomblings"},
    {FAIRY_DROP, "fairy tears"},
    {WORM, "worm"},
    {BEE_CHILD, "bee larva"},
    {CHUCHU_RARE, "rare chu"},
    {CHUCHU_RED, "red chu"},
    {CHUCHU_BLUE, "blue chu"},
    {CHUCHU_GREEN, "green chu"},
    {CHUCHU_YELLOW, "yellow chu"},
    {CHUCHU_PURPLE, "purple chu"},
    {LV1_SOUP, "simple soup"},
    {LV2_SOUP, "good soup"},
    {LV3_SOUP, "superb soup"},
    {LETTER, "Renado's letter"},
    {BILL, "invoice"},
    {WOOD_STATUE, "wooden statue"},
    {IRIAS_PENDANT, "Ilia's charm"},
    {HORSE_FLUTE, "horse call"},
    {RAFRELS_MEMO, "Auru's memo"},
    {ASHS_SCRIBBLING, "Ashei's sketch"},
    {ANCIENT_DOCUMENT, "ancient sky book (empty)"},
    {AIR_LETTER, "ancient sky book (partial)"},
    {ANCIENT_DOCUMENT2, "ancient sky book (filled)"},
    {NO_ITEM, "no item"},
};

Line lines[LINE_NUM] = {
    {"Slot 0:", SLOT_0, "", false, nullptr, false},
    {"Slot 1:", SLOT_1, "", false, nullptr, false},
    {"Slot 2:", SLOT_2, "", false, nullptr, false},
    {"Slot 3:", SLOT_3, "", false, nullptr, false},
    {"Slot 4:", SLOT_4, "", false, nullptr, false},
    {"Slot 5:", SLOT_5, "", false, nullptr, false},
    {"Slot 6:", SLOT_6, "", false, nullptr, false},
    {"Slot 7:", SLOT_7, "", false, nullptr, false},
    {"Slot 8:", SLOT_8, "", false, nullptr, false},
    {"Slot 9:", SLOT_9, "", false, nullptr, false},
    {"Slot 10:", SLOT_10, "", false, nullptr, false},
    {"Slot 11:", SLOT_11, "", false, nullptr, false},
    {"Slot 12:", SLOT_12, "", false, nullptr, false},
    {"Slot 13:", SLOT_13, "", false, nullptr, false},
    {"Slot 14:", SLOT_14, "", false, nullptr, false},
    {"Slot 15:", SLOT_15, "", false, nullptr, false},
    {"Slot 16:", SLOT_16, "", false, nullptr, false},
    {"Slot 17:", SLOT_17, "", false, nullptr, false},
    {"Slot 18:", SLOT_18, "", false, nullptr, false},
    {"Slot 19:", SLOT_19, "", false, nullptr, false},
    {"Slot 20:", SLOT_20, "", false, nullptr, false},
    {"Slot 21:", SLOT_21, "", false, nullptr, false},
    {"Slot 22:", SLOT_22, "", false, nullptr, false},
    {"Slot 23:", SLOT_23, "", false, nullptr, false},
};

int l_listIdx = 0;

void ItemWheelMenu::updateListIdx() {
    uint8_t item_id = dComIfGs_getSavedata().getPlayer().getItem().mItems[cursor.y];
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (item_id == l_validItems[i]) {
            l_listIdx = i;
        }
    }
}

void ItemWheelMenu::fixSpecialItems(int i) {
    if (l_validItems[i] == NORMAL_BOMB || l_validItems[i] == WATER_BOMB ||
        l_validItems[i] == POKE_BOMB) {
        switch (cursor.y) {
        case SLOT_15:
            dComIfGs_setBombNum(BOMB_BAG_1, 1);
            break;
        case SLOT_16:
            dComIfGs_setBombNum(BOMB_BAG_2, 1);
            break;
        case SLOT_17:
            dComIfGs_setBombNum(BOMB_BAG_3, 1);
            break;
        }
    }
}

void ItemWheelMenu::draw() {
    cursor.setMode(Cursor::MODE_LIST);
    updateListIdx();

    if (GZ_getButtonTrig(BACK_BUTTON)) {
        GZ_setMenu(GZ_INVENTORY_MENU);
        return;
    }

    for (int slot_no = 0; slot_no < LINE_NUM; slot_no++) {
        int item_id = dComIfGs_getItem(slot_no, false);

        for (int j = 0; j < MAX_ITEMS; j++) {
            if (l_lookupTbl[j].item_id == item_id) {
                tp_sprintf(lines[slot_no].value, " <%s>",
                           item_id != NO_ITEM ? l_lookupTbl[j].name : "none");
            }

            if (l_lookupTbl[j].item_id == l_defaultItems[slot_no]) {
                tp_sprintf(lines[slot_no].description,
                           "Slot %d default: %s. Press " DEFAULT_BTN_TXT " to set to default",
                           slot_no, l_lookupTbl[j].name);
            } else {
                continue;
            }
        }
    }

    if (GZ_getButtonRepeat(GZPad::DPAD_RIGHT)) {
        l_listIdx++;

        if (l_listIdx > MAX_ITEMS) {
            l_listIdx = 0;
        }

        fixSpecialItems(l_listIdx);
        dComIfGs_setItem(cursor.y, l_validItems[l_listIdx]);
    }

    if (GZ_getButtonRepeat(GZPad::DPAD_LEFT)) {
        l_listIdx--;

        if (l_listIdx < 0) {
            l_listIdx = MAX_ITEMS;
        }

        fixSpecialItems(l_listIdx);
        dComIfGs_setItem(cursor.y, l_validItems[l_listIdx]);
    }

    if (GZ_getButtonTrig(DEFAULT_BTN)) {
        dComIfGs_setItem(cursor.y, l_defaultItems[cursor.y]);
    }

    cursor.move(0, LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, LINE_NUM);
}
