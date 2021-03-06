#include "menu.h"

#define AD_SPECIALS_AMNT 12

enum ADPracticeIndex {
    AD_ORDON_GATE_CLIP_INDEX,
    AD_BIT_INDEX,
    AD_GOATS_INDEX,
    AD_HUGO_INDEX,
    AD_FARON_TWILGHT_INDEX,
    AD_EMS_INDEX,
    AD_MIST_INDEX,
    AD_FRST_BIT_INDEX,
    AD_FRST_ESCAPE_INDEX,
    AD_PILLAR_CLIP_INDEX,
    AD_LAKEBED_1_INDEX,
    AD_TOAD_INDEX,
    AD_KARG_INDEX,
    AD_FT2_INDEX,
    AD_DIABABA_INDEX,
    AD_ELDIN_TWILIGHT_INDEX,
    AD_LANAYRU_TWILIGHT_INDEX,
    AD_POST_LANAYRU_INDEX,
    AD_BK_SKIP_INDEX,
    AD_MORPHEEL_INDEX,
    AD_MDH_INDEX,
    AD_MOUNTAIN_INDEX,
    AD_SPR_INDEX,
    AD_DARK_HAMMER_INDEX,
    AD_SPR_BOOST_INDEX,
    AD_BLIZZETA_INDEX,
    AD_AG_INDEX,
    AD_POE_SKIP_INDEX,
    AD_DSS_INDEX,
    AD_STALLORD_INDEX,
    AD_EARLY_ELE_INDEX,
    AD_GM_INDEX,
    AD_DANGORO_INDEX,
    AD_RUPEE_INDEX,
    AD_CITS_1_INDEX,
    AD_AERALFOS_INDEX,
    AD_CITS_2_INDEX,
    AD_ARGOROK_INDEX,
    AD_FARON_BOOST_INDEX,
    AD_GROVE_2_INDEX,
    AD_TOT_INDEX,
    AD_DARKNUT_INDEX,
    AD_DOT_SKIP_INDEX,
    AD_PALACE_1_INDEX,
    AD_PALACE_2_INDEX,
    AD_EARLY_PLATFORM_INDEX,
    AD_ZANT_INDEX,
    AD_HC_INDEX,
    AD_BEAST_GANON_INDEX,
    AD_HORSEBACK_INDEX
};

class ADSavesMenu : public Menu {
public:
    ADSavesMenu() : Menu() {}
    static void render();
};