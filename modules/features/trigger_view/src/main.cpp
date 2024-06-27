#include <main.h>
#include "features/trigger_view/include/trigger_view.h"
#include "rels/include/cxx.h"
#include "events/pre_loop_listener.h"

namespace tpgz::modules {
void main() {
    g_PreLoopListener->addListener(TriggerViewer::execute);
}
void exit() {
    g_PreLoopListener->removeListener(TriggerViewer::execute);
}

}  // namespace tpgz::modules