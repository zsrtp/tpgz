#pragma once

#include "libtp_c/include/dolphin/types.h"

enum TriggerViewIndex {
    VIEW_LOAD_ZONES,
    VIEW_MIDNA_STOPS,
    VIEW_SWITCH_AREAS,
    VIEW_EVENT_AREAS,
    VIEW_TW_GATES,
    VIEW_PATHS,
    VIEW_CHG_RESTARTS,
    VIEW_PLUMM_TAGS,
    VIEW_TRANSFORM_DISTS,
    VIEW_ATTN_DISTS,
    VIEW_MIST_AVOID,

    TRIGGER_VIEW_MAX,
};

struct TriggerViewItem {
    enum TriggerViewIndex id;
    bool active;
};

extern TriggerViewItem g_triggerViewFlags[TRIGGER_VIEW_MAX];