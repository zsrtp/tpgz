#include "global_data.h"
#include "trigger_view.h"
#include "rels/include/defines.h"

KEEP_VAR bool g_freeCamEnabled;
KEEP_VAR bool g_moveLinkEnabled;

KEEP_VAR TriggerViewItem g_triggerViewFlags[TRIGGER_VIEW_MAX] = {
    {VIEW_LOAD_ZONES, false},
};