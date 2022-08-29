#include <main.h>
#include "input_viewer.h"
#include "rels/include/cxx.h"
#include "handlers/draw_handler.h"

namespace tpgz::modules {
void main() {
    g_drawHandler->addHandler(InputViewer::draw);
}
void exit() {
    g_drawHandler->removeHandler(InputViewer::draw);
}

}  // namespace tpgz::modules