#include <main.h>
#include "features/projection_view/include/projection_view.h"
#include "rels/include/cxx.h"
#include "events/pre_loop_listener.h"

namespace tpgz::modules {
void main() {
    g_PreLoopListener->addListener(ProjectionViewer::execute);
}
void exit() {
    g_PreLoopListener->removeListener(ProjectionViewer::execute);
}

}  // namespace tpgz::modules