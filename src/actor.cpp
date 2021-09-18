#include "actor.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"

namespace Actor {
bool freeze_run_once;
bool hide_run_once;

void freeze_actors() {
    freeze_run_once = true;
    g_dComIfAc_gameInfo.freeze = true;
}

void unfreeze_actors() {
    if (freeze_run_once) {
        g_dComIfAc_gameInfo.freeze = false;
        freeze_run_once = false;
    }
}

void hide_actors() {
    hide_run_once = true;
    fopAc_ac_c__stopStatus |= 0x100;
}

void show_actors() {
    if (hide_run_once) {
        fopAc_ac_c__stopStatus &= ~0x100;
        hide_run_once = false;
    }
}

}  // namespace Actor
