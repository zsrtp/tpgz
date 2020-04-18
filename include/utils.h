#pragma once

#include "controller.h"
#include "font.h"
#include "menu.h"
#include "cheats.h"
#include "save_injector.h"
#include "gcn_c/include/card.h"

namespace Utilities {
    void move_cursor(int& cursor, int LINES);
    void menu_anim(Font& font, int idx);
    void render_lines(Font& font, Line lines[], int cursor, int LINES);
    void trigger_load();
    void change_tunic_color();
    void disable_bg_music();
    void enable_bg_music();
    void disable_sfx();
    void enable_sfx();
    void load_gz_card(bool &card_load);
    void change_font(Font& font, const _Font& font_bytes, const char* font_texture_data);
    void load_mem_card(MemCard::Card &card, SaveLayout &save_layout);
}  // namespace Utilities