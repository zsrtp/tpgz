#include <main.h>
#include "features/moveactor/include/moveactor.h"
#include "rels/include/cxx.h"
#include "events/pre_loop_listener.h"

namespace tpgz::modules {
void main() {
    g_PreLoopListener->addListener(MoveActor::execute);
}
void exit() {
    g_PreLoopListener->removeListener(MoveActor::execute);
}

}  // namespace tpgz::modules