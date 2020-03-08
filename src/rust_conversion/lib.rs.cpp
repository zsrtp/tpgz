#include "rust_conversion/lib.h"
#include "rust_conversion/menu.h"
#include "../include/font.h"

State get_state() {
    State state;
    Settings settings;
    settings.drop_shadow = true;
    settings.max_lines = 16;
    Consolas = Font(f_Consolas, consolas_bytes); // this already exists in the other lib.cpp so would be deleted when we merge
    state.font = Consolas;
    state.menu = Menu::Default();
    state.settings = settings;
    return state;
}