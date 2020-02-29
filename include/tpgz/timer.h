#pragma once
#include "tpgz/font.h"

extern bool timer_visible;
extern bool timer_started;
extern bool reset_timer;

namespace Timer {
    void render(Font& font);
}