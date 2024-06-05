#include <main.h>
#include "events/draw_listener.h"
#include "mash_checker.h"

namespace tpgz::modules {
void main() {
    g_drawListener->addListener(GZ_displayButtonMashInfo);
}
void exit() {
    g_drawListener->removeListener(GZ_displayButtonMashInfo);
}

}  // namespace tpgz::modules