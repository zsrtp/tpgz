#include <main.h>
#include "fifo_queue.h"
#include "font.h"
#include "menu.h"
#include "menus/position_settings_menu.h"
#include "utils/card.h"
#include "utils/draw.h"
#include "utils/link.h"
#include "utils/hook.h"
#include "rels/include/cxx.h"

namespace tpgz::modules {
void main() {
    Hook::applyHooks();
    Font::loadFont("/tpgz/fonts/consola.fnt");
    Draw::init();
    Menu::init();
    PosSettingsMenu::initDefaults();
    g_fifoVisible = true;
    GZ_patchLinkColor();
#ifdef WII_PLATFORM
    g_tmpBuf = new (-0x200) uint8_t[0x4000];
#endif
}
void exit() {}

}  // namespace tpgz::modules