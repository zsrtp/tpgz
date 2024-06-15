#pragma once
#include "utils/rels.h"
#include "utils/containers/deque.h"

struct Module {
    bool (*active)();
    tpgz::dyn::GZModule rel;
};

extern tpgz::containers::deque<Module*> g_modules;

void GZ_handleModules();
bool inputViewer_active();
bool freeCam_active();
bool moveLink_active();
bool projectionView_active();
bool triggerViewer_active();
bool actorView_active();
bool transformIndicator_active();
bool umd_active();
#ifdef WII_PLATFORM
bool bit_active();
#endif
bool corotd_active();
bool mash_checker_active();
bool gorge_active();
bool rollcheck_active();
bool moon_jump_active();
bool freeze_actor_active();
bool hide_actor_active();
bool freeze_camera_active();
