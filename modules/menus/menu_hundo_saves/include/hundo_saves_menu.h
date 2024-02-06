#pragma once

#include "menu.h"

#define HND_SPECIALS_AMNT 27

enum HundoPracticeIndex {
    HND_GOATS_1_INDEX,
    HND_ORDON_GATE_CLIP_INDEX,
    HND_GOATS_2_INDEX,
    HND_FARON_TWILIGHT_INDEX,
    HND_EMS_INDEX,
    HND_MIST_INDEX,
    HND_FRST_BIT_INDEX,
    HND_FRST_2_INDEX,
    HND_OOKLESS_INDEX,
    HND_ELDIN_TWILIGHT_INDEX,
    HND_BOMB_HOUSE_SKIP_INDEX,
    HND_LANAYRU_GATE_CLIP_INDEX,
    HND_PILLAR_CLIP_INDEX,
    HND_LAKEBED_1_INDEX,
    HND_TOAD_INDEX,
    HND_KARG_INDEX,
    HND_LANAYRU_TWILIGHT_INDEX,
    HND_BOSS_BUG_INDEX,
    HND_KB_2_INDEX,
    HND_ESCORT_INDEX,
    HND_COROTD_INDEX,
    HND_GM_INDEX,
    HND_DANGORO_INDEX,
    HND_POST_GM_INDEX,
    HND_LAKEBED_BK_SKIP_INDEX,
    HND_MORPHEEL_INDEX,
    HND_MDH_TOWER_INDEX,
    HND_MDH_BRIDGE_INDEX,
    HND_POST_MDH_INDEX,
    HND_STAR_1_INDEX,
    HND_KB1_INDEX,
    HND_IZA_1_SKIP_INDEX,
    HND_LH_CAVE_INDEX,
    HND_BULBLIN_CAMP_INDEX,
    HND_AG_INDEX,
    HND_POE_1_SKIP_INDEX,
    HND_DSS_INDEX,
    HND_STALLORD_INDEX,
    HND_POST_AG_INDEX,
    HND_SPR_INDEX,
    HND_DARK_HAMMER_INDEX,
    HND_SPR_SUPERJUMP_INDEX,
    HND_SPR_BK_LJA_INDEX,
    HND_SPR_BK_ROOM_INDEX,
    HND_BLIZZETA_INDEX,
    HND_FARON_BOOST_INDEX,
    HND_GROVE_SKIP_INDEX,
    HND_GROVE_BOOST_INDEX,
    HND_TOT_INDEX,
    HND_EARLY_POE_INDEX,
    HND_STATUE_THROWS_INDEX,
    HND_EARLY_HP_INDEX,
    HND_DARKNUT_INDEX,
    HND_DOT_SKIP_INDEX,
    HND_POST_TOT_INDEX,
    HND_HOTSPRING_INDEX,
    HND_GORGE_ARC_INDEX,
    HND_PUZZLE_INDEX,
    HND_ARCHERY_INDEX,
    HND_CITY_1_INDEX,
    HND_AERALFOS_INDEX,
    HND_CITY_2_INDEX,
    HND_POE_CYCLE_INDEX,
    HND_FAN_TOWER_INDEX,
    HND_ARGOROK_INDEX,
    HND_STAR_2_INDEX,
    HND_PALACE_1_INDEX,
    HND_PALACE_2_INDEX,
    HND_EARLY_PLATFORM_INDEX,
    HND_ZANT_INDEX,
    HND_COO_INDEX,
    HND_COO_10_INDEX,
    HND_COO_20_INDEX,
    HND_COO_30_INDEX,
    HND_COO_40_INDEX,
    HND_CATS_INDEX,
    HND_HYRULE_INDEX,
    HND_DARKNUT_SKIP_INDEX,
    HND_FINAL_TOWER_INDEX,
    HND_BEAST_GANON_INDEX,
    HND_HORSEBACK_GANON_INDEX,

    HND_SAVES_MAX,
};

class HundoSavesMenu : public Menu {
public:
    HundoSavesMenu(Cursor&);
    virtual ~HundoSavesMenu();
    virtual void draw();

private:
    Line lines[HND_SAVES_MAX];
};