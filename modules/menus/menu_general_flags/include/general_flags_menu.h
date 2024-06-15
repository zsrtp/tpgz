#pragma once
#include "menus/menu.h"

struct GeneralFlagsData {
    bool l_bossFlag;
    bool l_rupeeFlag;
    bool l_midnaCharge;
    bool l_transformWarp;
    bool l_midnaZ;
    bool l_eponaStolen;
    bool l_eponaTamed;
    bool l_mapWarping;
    bool l_midnaHealed;
    bool l_midnaRide;
    bool l_wolfSense;
};

enum GeneralFlagsIndex {
    BOSS_FLAG_INDEX,
    RUPEE_CS_FLAG_INDEX,
    EPONA_STOLEN_INDEX,
    EPONA_TAMED_INDEX,
    MAP_WARPING_INDEX,
    MIDNA_CHARGE_INDEX,
    MIDNA_HEALTHY,
    MIDNA_ON_BACK,
    MIDNA_Z_INDEX,
    TRANSFORM_WARP_INDEX,
    WOLF_SENSE_INDEX
};

extern GeneralFlagsData* generalFlagsData;

class GeneralFlagsMenu : public Menu {
public:
    GeneralFlagsMenu(Cursor&);
    virtual ~GeneralFlagsMenu();
    virtual void draw();

private:
    Line lines[11];
};
