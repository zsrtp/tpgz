#include <main.h>
#include "features/free_cam/include/free_cam.h"
#include "rels/include/cxx.h"
#include "events/pre_loop_listener.h"

void handleFreeCam() {
    FreeCam::execute();
}

namespace tpgz::modules {
void main() {
    g_PreLoopListener->addListener(handleFreeCam);
}
void exit() {
    g_PreLoopListener->removeListener(handleFreeCam);
}

}  // namespace tpgz::modules