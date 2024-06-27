#include "menus/menu.h"

struct FlagRecordsData {
    uint8_t l_bitIdx;
    uint8_t l_recIdx;
    Texture l_flagOnTex;
    Texture l_flagOffTex;
};

class FlagRecordsMenu : public Menu {
public:
    FlagRecordsMenu(Cursor&, FlagRecordsData&);
    virtual ~FlagRecordsMenu();
    virtual void draw();
    void drawFlagRecord(uint8_t* record);

private:
    uint8_t& l_bitIdx;
    uint8_t& l_recIdx;
    Texture& l_flagOnTex;
    Texture& l_flagOffTex;
};