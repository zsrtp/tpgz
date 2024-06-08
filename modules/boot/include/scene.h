#pragma once

#define SCENE_AMNT 7

enum SceneIndex {
    DISABLE_BG_INDEX,
    DISABLE_SFX_INDEX,
    FREEZE_ACTOR_INDEX,
    FREEZE_CAMERA_INDEX,
    HIDE_ACTOR_INDEX,
    HIDE_HUD_INDEX,
    FREEZE_TIME_INDEX,
    TIME_HOURS_INDEX,
    TIME_MINUTES_INDEX,
    ACTOR_MENU_INDEX,
    ACTOR_LIST_INDEX,
    COLLISION_VIEW_INDEX,
    PROJECTION_VIEW_INDEX,
    TRIGGER_VIEW_INDEX,

    SCENE_MENU_MAX
};

struct SceneItem {
    enum SceneIndex id;
    bool active;
};

void GZ_freezeTime();
void GZ_freezeCamera();
void GZ_unfreezeCamera();
void GZ_hideHUD();
void GZ_showHUD();
void GZ_freezeActors();
void GZ_unfreezeActors();
void GZ_hideActors();
void GZ_showActors();
