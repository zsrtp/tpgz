#include "modules.h"
#include "libtp_c/include/defines.h"

#include "commands.h"
#include "global_data.h"
#include "tools.h"
#include "trigger_view.h"

KEEP_VAR tpgz::containers::deque<Module*> g_modules;

/**
 * @brief   Handles when to load or unload REL modules.
 *          Registered to run before the main loop.
 */
KEEP_FUNC void GZ_handleModules() {
    for (auto mod : g_modules) {
        if (mod->active() && !mod->rel.isLoaded()) {
            mod->rel.loadFixed(true);
        }
        if (!mod->active() && mod->rel.isLoaded()) {
            mod->rel.close();
        }
    }
}

KEEP_FUNC bool inputViewer_active() {
    return g_tools[INPUT_VIEWER_INDEX].active;
}

KEEP_FUNC bool freeCam_active() {
    return g_tools[FREE_CAM_INDEX].active;
}

KEEP_FUNC bool moveLink_active() {
    return g_tools[MOVE_LINK_INDEX].active;
}

KEEP_FUNC bool triggerViewer_active() {
    int active_flags = 0;
    for (int i = 0; i < TRIGGER_VIEW_MAX; i++) {
        if (g_triggerViewFlags[i].active) {
            active_flags++;
        }
    }
    return active_flags > 0;
}

KEEP_FUNC bool actorView_active() {
    return g_actorViewEnabled;
}

KEEP_FUNC bool transformIndicator_active() {
    return g_tools[TRANSFORM_INDICATOR_INDEX].active;
}

KEEP_FUNC bool umd_active() {
    return g_tools[UMD_INDEX].active;
}

#ifdef WII_PLATFORM
KEEP_FUNC bool bit_active() {
    return g_tools[BIT_INDEX].active;
}
#endif

KEEP_FUNC bool corotd_active() {
    return g_tools[COROTD_INDEX].active;
}

KEEP_FUNC bool mash_checker_active() {
    return g_tools[MASH_CHECKER_INDEX].active;
}

KEEP_FUNC bool gorge_active() {
    return g_tools[GORGE_INDEX].active;
}
