#pragma once

#include "menu.h"

#define GL_SPECIALS_AMNT 3

enum GlitchlessPracticeIndex {
    GL_FARON_TWILIGHT_INDEX,
    GL_FOREST_INDEX,
    GL_DIABABA_INDEX,
    GL_ELDIN_TWILIGHT_INDEX,
    GL_POST_TWILIGHT_INDEX,
    GL_KB1_INDEX,
    GL_MINES_INDEX,
    GL_DANGORO_INDEX,
    GL_LANAYRU_TWILIGHT_INDEX,
    GL_ESCORT_INDEX,
    GL_LAKEBED_INDEX,
    GL_TOAD_INDEX,
    GL_MDH_INDEX,
    GL_POST_MDH_INDEX,
    GL_POST_MS_INDEX,
    GL_AG_INDEX,
    GL_DEATH_SWORD_INDEX,
    GL_POST_AG_INDEX,
    GL_SPR_INDEX,
    GL_DARKHAMMER_INDEX,
    GL_POST_SPR_INDEX,
    GL_TOT_INDEX,
    GL_DARKNUT_INDEX,
    GL_POST_TOT_INDEX,
    GL_HV_INDEX,
    GL_CITY_INDEX,
    GL_AERALFOS_INDEX,
    GL_PALACE_INDEX,
    GL_ZANT_INDEX,
    GL_HYRULE_INDEX,
    GL_BEAST_GANON_INDEX,
    GL_HORSEBACK_GANON_INDEX,

    GL_SAVES_NUM,
};

class GlitchlessSavesMenu : public Menu {
public:
    GlitchlessSavesMenu(Cursor&);
    virtual ~GlitchlessSavesMenu();
    virtual void draw();

private:
    Line lines[GL_SAVES_NUM];
};