#include "menu.h"

class FlagRecordsMenu : public Menu {
public:
    FlagRecordsMenu() : Menu() {}
    static void draw();
    static void drawFlagRecord(uint8_t* record);

    static Cursor cursor;
};