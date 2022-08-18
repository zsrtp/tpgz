#pragma once
#include <cinttypes>
#include "utils/rels.h"

namespace tpgz::modules {
/***********************************************************************************
 * We're creating a cusutom REL file and thus the real main function already ran
 * before we even load this program.
 * That's also why we create a custom namespace to avoid confusing the compiler with the actual main
 *function whilst still having a neat starting function for you to begin your Twilight Princess mod
 *development! Note: If you want to change the namespace "mod" you will have to make adjustments to
 *rel.cpp in external/rels!
 *
 * This main function is going to be executed once at the beginning of the game,
 * assuming the REL got loaded in the first place.
 ***********************************************************************************/
void main();
void exit();

}  // namespace tpgz::modules

extern tpgz::dyn::GZModule g_InputViewer_rel;
void GZ_controlTools();
void GZ_controlMenu();
void GZ_controlCardLoad();
void GZ_controlSavingTmp();
void GZ_controlFlags_PreLoop();
void GZ_controlFlags_PostLoop();
void GZ_controlTurbo();

void GZ_renderMenuTitle();
void GZ_renderPlayPause();

extern "C" {
void game_loop();
void post_game_loop();
void draw();
}