#include <main.h>
#include "features/movelink/include/movelink.h"
#include "rels/include/cxx.h"
#include "events/pre_loop_listener.h"

namespace tpgz::modules {
void main() {
    g_PreLoopListener->addListener(MoveLink::execute);
}
void exit() {
    g_PreLoopListener->removeListener(MoveLink::execute);
}

}  // namespace tpgz::modules