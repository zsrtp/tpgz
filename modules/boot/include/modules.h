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
bool triggerViewer_active();
bool actorView_active();
bool transformIndicator_active();
