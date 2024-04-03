#pragma once

enum TriggerViewIndex {
    VIEW_LOAD_ZONES,
    TRIGGER_VIEW_MAX,
};

struct TriggerViewItem {
    enum TriggerViewIndex id;
    bool active;
};

extern TriggerViewItem g_triggerViewFlags[TRIGGER_VIEW_MAX];