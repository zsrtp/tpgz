#include "settings.h"

ListMember g_font_opt[] = {"consola",   "calamity-bold",  "lib-sans",      "lib-sans-bold",
                         "lib-serif", "lib-serif-bold", "press-start-2p"};

bool g_dropShadows;
bool g_swap_equips_flag;
uint32_t g_reloadType;
uint32_t g_fontType = 0;
uint32_t g_cursorColorType;

void GZ_initFont() {
    if (g_fontType >= 0 && g_fontType < FONT_OPTIONS_COUNT) {
        char buf[40] = {0};
        sprintf(buf, "tpgz/fonts/%s.fnt", g_font_opt[g_fontType].member);
        Font::loadFont(buf);
    }
}