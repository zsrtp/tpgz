#pragma once
#include "rust_conversion/menu.h"
#include "rust_conversion/settings.h"
#include "../include/font.h"

struct State {
    Font font;
    Menu menu;
    Settings settings;
};

State get_state();