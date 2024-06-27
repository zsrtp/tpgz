
#include "menus/menu_item_wheel/include/item_wheel_menu.h"
#include <cstdio>
#include "font.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "gz_flags.h"
#include "rels/include/defines.h"
#include "menus/utils/menu_mgr.h"

#define ITEM_WHEEL_SLOTS 24
#define MAX_ITEMS 58

#ifdef GCN_PLATFORM
#define DEFAULT_BTN_TXT "Z"
#define DEFAULT_BTN GZPad::Z
#define RESET_BTN_TXT "X"
#define RESET_BUTTON GZPad::X
#endif

#ifdef WII_PLATFORM
#define DEFAULT_BTN_TXT "+"
#define DEFAULT_BTN GZPad::PLUS
#define RESET_BTN_TXT "-"
#define RESET_BUTTON GZPad::MINUS
#endif

KEEP_FUNC ItemWheelMenu::ItemWheelMenu(Cursor& cursor, ItemWheelData& data)
    : Menu(cursor), l_listIdx(data.l_listIdx), lines{
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
                                               } {}

ItemWheelMenu::~ItemWheelMenu() {}

const uint8_t l_validItems[] = {
    NO_ITEM,            ANCIENT_DOCUMENT,
    ANCIENT_DOCUMENT2,  AIR_LETTER,
    ASHS_SCRIBBLING,    RAFRELS_MEMO,
    IRONBALL,           BEE_CHILD,
    CHUCHU_BLUE,        BLUE_BOTTLE,
    POKE_BOMB,          HOOKSHOT,
    COPY_ROD,           W_HOOKSHOT,
    BOMB_BAG_LV1,       EMPTY_BOTTLE,
    FAIRY,              FAIRY_DROP,
    FISHING_ROD_1,      BEE_ROD,
    JEWEL_ROD,          JEWEL_BEE_ROD,
    JEWEL_WORM_ROD,     WORM_ROD,
    BOOMERANG,          LV2_SOUP,
    CHUCHU_GREEN,       HALF_MILK_BOTTLE,
    HAWK_EYE,           BOW,
    HORSE_FLUTE,        HOT_SPRING,
    IRIAS_PENDANT,      BILL,
    HVY_BOOTS,          KANTERA,
    OIL_BOTTLE,         GREEN_BOTTLE,
    MILK_BOTTLE,        UGLY_SOUP,
    DUNGEON_BACK,       DUNGEON_EXIT,
    TKS_LETTER,         CHUCHU_PURPLE,
    CHUCHU_RARE,        CHUCHU_RED,
    RED_BOTTLE,         NORMAL_BOMB,
    LETTER,             LV1_SOUP,
    PACHINKO,           SPINNER,
    LV3_SOUP,           WATER_BOTTLE,
    WATER_BOMB,         WOOD_STATUE,
    WORM,               CHUCHU_YELLOW
};

const uint8_t l_defaultItems[ITEM_WHEEL_SLOTS] = {
    BOOMERANG,     KANTERA,      SPINNER,          HVY_BOOTS,    BOW,
    HAWK_EYE,      IRONBALL,     NO_ITEM,          COPY_ROD,     HOOKSHOT,
    W_HOOKSHOT,    EMPTY_BOTTLE, EMPTY_BOTTLE,     EMPTY_BOTTLE, EMPTY_BOTTLE,
    BOMB_BAG_LV1,  BOMB_BAG_LV1, BOMB_BAG_LV1,     DUNGEON_EXIT, RAFRELS_MEMO,
    FISHING_ROD_1, HORSE_FLUTE,  ANCIENT_DOCUMENT, PACHINKO,
};

const ItemLookup l_lookupTbl[MAX_ITEMS] = {
    {NO_ITEM, "n/a"},
    {ANCIENT_DOCUMENT, "ancient sky book (empty)"},
    {ANCIENT_DOCUMENT2, "ancient sky book (filled)"},
    {AIR_LETTER, "ancient sky book (partial)"},
    {ASHS_SCRIBBLING, "ashei's sketch"},
    {RAFRELS_MEMO, "auru's memo"},
    {IRONBALL, "ball and chain"},
    {BEE_CHILD, "bee larva"},
    {CHUCHU_BLUE, "blue chu"},
    {BLUE_BOTTLE, "blue potion"},
    {POKE_BOMB, "bomblings"},
    {HOOKSHOT, "clawshot"},
    {COPY_ROD, "dominion rod"},
    {W_HOOKSHOT, "double clawshot"},
    {BOMB_BAG_LV1, "empty bomb bag"},
    {EMPTY_BOTTLE, "empty bottle"},
    {FAIRY, "fairy"},
    {FAIRY_DROP, "fairy tears"},
    {FISHING_ROD_1, "fishing rod"},
    {BEE_ROD, "fishing rod (bee larva)"},
    {JEWEL_ROD, "fishing rod (coral earring)"},
    {JEWEL_BEE_ROD, "fishing rod (coral earring/bee larva)"},
    {JEWEL_WORM_ROD, "fishing rod (coral earring/worm)"},
    {WORM_ROD, "fishing rod (worm)"},
    {BOOMERANG, "gale boomerang"},
    {LV2_SOUP, "good soup"},
    {CHUCHU_GREEN, "green chu"},
    {HALF_MILK_BOTTLE, "half milk"},
    {HAWK_EYE, "hawkeye"},
    {BOW, "hero's bow"},
    {HORSE_FLUTE, "horse call"},
    {HOT_SPRING, "hot spring water"},
    {IRIAS_PENDANT, "Ilia's charm"},
    {BILL, "invoice"},
    {HVY_BOOTS, "iron boots"},
    {KANTERA, "lantern"},
    {OIL_BOTTLE, "lantern oil"},
    {GREEN_BOTTLE, "magic potion"},
    {MILK_BOTTLE, "milk"},
    {UGLY_SOUP, "nasty soup"},
    {DUNGEON_BACK, "ooccoo Jr."},
    {DUNGEON_EXIT, "ooccoo Sr."},
    {TKS_LETTER, "ooccoo's note"},
    {CHUCHU_PURPLE, "purple chu"},
    {CHUCHU_RARE, "rare chu"},
    {CHUCHU_RED, "red chu"},
    {RED_BOTTLE, "red potion"},
    {NORMAL_BOMB, "regular bombs"},
    {LETTER, "renado's letter"},
    {LV1_SOUP, "simple soup"},
    {PACHINKO, "slingshot"},
    {SPINNER, "spinner"},
    {LV3_SOUP, "superb soup"},
    {WATER_BOTTLE, "water"},
    {WATER_BOMB, "water bombs"},
    {WOOD_STATUE, "wooden statue"},
    {WORM, "worm"},
    {CHUCHU_YELLOW, "yellow chu"}
};

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
        g_menuMgr->pop();
        return;
    }

    for (size_t slot_no = 0; slot_no < MENU_LINE_NUM; slot_no++) {
        int item_id = dComIfGs_getItem(slot_no, false);

        for (int j = 0; j < MAX_ITEMS; j++) {
            if (l_lookupTbl[j].item_id == item_id) {
                lines[slot_no].printf(" <%s>", item_id != NO_ITEM ? l_lookupTbl[j].name : "n/a");
            }

            if (l_lookupTbl[j].item_id == l_defaultItems[slot_no]) {
                snprintf(lines[slot_no].description, sizeof(lines[slot_no].description),
                         "Slot %d default: %s. Press " DEFAULT_BTN_TXT " to set to default; " RESET_BTN_TXT " to reset.",
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

    if (GZ_getButtonTrig(RESET_BUTTON)) {
        dComIfGs_setItem(cursor.y, NO_ITEM);
    }

    cursor.move(0, MENU_LINE_NUM);
    GZ_drawMenuLines(lines, cursor.y, MENU_LINE_NUM);
}
