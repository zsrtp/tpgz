#pragma once

enum TriggerViewIndex {
    VIEW_LOAD_ZONES,
    VIEW_MIDNA_STOPS,
    VIEW_SWITCH_AREAS,
    VIEW_TW_GATES,

    TRIGGER_VIEW_MAX,
};

struct TriggerViewItem {
    enum TriggerViewIndex id;
    bool active;
};

extern TriggerViewItem g_triggerViewFlags[TRIGGER_VIEW_MAX];