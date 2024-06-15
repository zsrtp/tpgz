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
    return GZStng_getSettingData(STNG_TOOLS_INPUT_VIEWER, false);
}

KEEP_FUNC bool freeCam_active() {
    return GZStng_getSettingData(STNG_TOOLS_FREE_CAM, false);
}

KEEP_FUNC bool moveLink_active() {
    return g_actorViewEnabled ? true : GZStng_getSettingData(STNG_TOOLS_MOVE_LINK, false);
}

KEEP_FUNC bool projectionView_active() {
    return GZStng_getSettingData(STNG_SCENE_LJA_PROJECTION, false) || GZStng_getSettingData(STNG_SCENE_MIDNA_CHARGE_PROJECTION, false);
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
    return GZStng_getSettingData(STNG_TOOLS_TRANSFORM_INDICATOR, false);
}

KEEP_FUNC bool umd_active() {
    return GZStng_getSettingData(STNG_TOOLS_UMD, false);
}

#ifdef WII_PLATFORM
KEEP_FUNC bool bit_active() {
    return GZStng_getSettingData(STNG_TOOLS_BIT, false);
}
#endif

KEEP_FUNC bool corotd_active() {
    return GZStng_getSettingData(STNG_TOOLS_COROTD, false);
}

KEEP_FUNC bool mash_checker_active() {
    return GZStng_getSettingData(STNG_TOOLS_MASH_CHECKER, false);
}

KEEP_FUNC bool gorge_active() {
    return GZStng_getSettingData(STNG_TOOLS_GORGE, false);
}

KEEP_FUNC bool rollcheck_active() {
    return GZStng_getSettingData(STNG_TOOLS_ROLL, false);
}

KEEP_FUNC bool moon_jump_active() {
    return GZStng_getSettingData(STNG_CHEATS_MOON_JUMP, false);
}

KEEP_FUNC bool freeze_actor_active() {
    return GZStng_getSettingData(STNG_SCENE_FREEZE_ACTOR, false);
}

KEEP_FUNC bool hide_actor_active() {
    return GZStng_getSettingData(STNG_SCENE_HIDE_ACTOR, false);
}

KEEP_FUNC bool freeze_camera_active() {
    return GZStng_getSettingData(STNG_SCENE_FREEZE_CAMERA, false);
}
