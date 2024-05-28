#pragma once

#include "libtp_c/include/dolphin/types.h"

enum TriggerViewIndex {
    VIEW_ATTN_DISTS,
    VIEW_EVENT_AREAS,
    VIEW_LOAD_ZONES,
    VIEW_MIDNA_STOPS,
    VIEW_PATHS,
    VIEW_MIST_AVOID,
    VIEW_CHG_RESTARTS,
    VIEW_SWITCH_AREAS,
    VIEW_TRANSFORM_DISTS,
    VIEW_TW_GATES,

    TRIGGER_VIEW_MAX,
};

struct TriggerViewItem {
    enum TriggerViewIndex id;
    bool active;
};

extern TriggerViewItem g_triggerViewFlags[TRIGGER_VIEW_MAX];