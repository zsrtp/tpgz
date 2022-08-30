#include <main.h>
#include "input_viewer.h"
#include "rels/include/cxx.h"
#include "events/draw_listener.h"

namespace tpgz::modules {
void main() {
    g_drawListener->addListener(InputViewer::draw);
}
void exit() {
    g_drawListener->removeListener(InputViewer::draw);
}

}  // namespace tpgz::modules