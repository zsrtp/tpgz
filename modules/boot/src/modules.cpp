#include "modules.h"
#include "libtp_c/include/defines.h"

#include "commands.h"
#include "global_data.h"
#include "settings.h"
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
    auto* stng_input_viewer = GZStng_getSetting(STNG_TOOLS_INPUT_VIEWER);
    return stng_input_viewer && *(bool*)stng_input_viewer->data;
}

KEEP_FUNC bool freeCam_active() {
    auto* stng_free_cam = GZStng_getSetting(STNG_TOOLS_FREE_CAM);
    return stng_free_cam && *(bool*)stng_free_cam->data;
}

KEEP_FUNC bool moveLink_active() {
    auto* stng_move_link = GZStng_getSetting(STNG_TOOLS_MOVE_LINK);
    return stng_move_link && *(bool*)stng_move_link->data;
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
    auto* stng_transform_indicator = GZStng_getSetting(STNG_TOOLS_TRANSFORM_INDICATOR);
    return stng_transform_indicator && *(bool*)stng_transform_indicator->data;
}

KEEP_FUNC bool umd_active() {
    auto* stng_umd = GZStng_getSetting(STNG_TOOLS_UMD);
    return stng_umd && *(bool*)stng_umd->data;
}

#ifdef WII_PLATFORM
KEEP_FUNC bool bit_active() {
    auto* stng_bit = GZStng_getSetting(STNG_TOOLS_BIT);
    return stng_bit && *(bool*)stng_bit->data;
}
#endif

KEEP_FUNC bool corotd_active() {
    auto* stng_corotd = GZStng_getSetting(STNG_TOOLS_COROTD);
    return stng_corotd && *(bool*)stng_corotd->data;
}

KEEP_FUNC bool mash_checker_active() {
    auto* stng_mash_checker = GZStng_getSetting(STNG_TOOLS_MASH_CHECKER);
    return stng_mash_checker && *(bool*)stng_mash_checker->data;
}

KEEP_FUNC bool gorge_active() {
    auto* stng_gorge = GZStng_getSetting(STNG_TOOLS_GORGE);
    return stng_gorge && *(bool*)stng_gorge->data;
}

KEEP_FUNC bool rollcheck_active() {
    auto* stng_roll = GZStng_getSetting(STNG_TOOLS_ROLL);
    return stng_roll && *(bool*)stng_roll->data;
}

KEEP_FUNC bool moon_jump_active() {
    auto* stng = GZStng_getSetting(STNG_CHEATS_MOON_JUMP);
    return stng && *(bool*)stng->data;
}
