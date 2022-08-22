#include "menu.h"

struct AmountsData {
    Cursor cursor;
    uint8_t l_arrowNum;
    uint8_t l_bag1Num;
    uint8_t l_bag2Num;
    uint8_t l_bag3Num;
    uint8_t l_seedNum;
    uint8_t l_poeNum;
    uint16_t l_hpNum;
    uint16_t l_rupeeNum;
};

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
    AmountsMenu(AmountsData&);
    virtual ~AmountsMenu();
    virtual void draw();

    Cursor& cursor;

private:
    uint8_t& l_arrowNum;
    uint8_t& l_bag1Num;
    uint8_t& l_bag2Num;
    uint8_t& l_bag3Num;
    uint8_t& l_seedNum;
    uint8_t& l_poeNum;
    uint16_t& l_hpNum;
    uint16_t& l_rupeeNum;

    Line lines[8];
};