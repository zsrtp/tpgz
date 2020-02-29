#pragma once
#include "tpgz/font.h"

extern bool iv_visible;

namespace InputViewer {
    static bool active = false;

    void render(Font& font);
}