#include "menu.h"

class FlagRecordsMenu : public Menu {
public:
    FlagRecordsMenu();
    virtual void draw();
    void drawFlagRecord(uint8_t* record);

    Cursor cursor;
private:
    uint8_t l_bitIdx;
    uint8_t l_recIdx;
    Texture l_flagOnTex;
    Texture l_flagOffTex;
};