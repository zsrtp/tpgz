#include <main.h>
#include "features/free_cam/include/free_cam.h"
#include "rels/include/cxx.h"
#include "events/pre_loop_listener.h"

namespace tpgz::modules {
void main() {
    g_PreLoopListener->addListener(FreeCam::execute);
}
void exit() {
    g_PreLoopListener->removeListener(FreeCam::execute);
}

}  // namespace tpgz::modules