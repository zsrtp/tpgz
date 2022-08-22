#include "menu.h"

struct FlagRecordsData {
    Cursor cursor;
    uint8_t l_bitIdx;
    uint8_t l_recIdx;
    Texture l_flagOnTex;
    Texture l_flagOffTex;
};

class FlagRecordsMenu : public Menu {
public:
    FlagRecordsMenu(FlagRecordsData&);
    virtual ~FlagRecordsMenu();
    virtual void draw();
    void drawFlagRecord(uint8_t* record);

    Cursor& cursor;

private:
    uint8_t& l_bitIdx;
    uint8_t& l_recIdx;
    Texture& l_flagOnTex;
    Texture& l_flagOffTex;
};