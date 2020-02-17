#include <stdio.h>
#include "libtp_c/include/system.h"
#include "libtp_c/include/link.h"
#include "controller.h"
#include "fonts/consolas.h"
#include "font.h"

static Font Consolas;

extern "C" {

void init() {
    Consolas = Font(f_Consolas, consolas_bytes);
}

void game_loop() {
}

void draw() {
    Consolas.setupRendering();

    char buffx[64];
    char buffy[64];
    char buffz[64];
    auto pos = Link::get_position();

    sprintf(buffx, "X: %.6f", pos ? pos->x : 0.0f);
    sprintf(buffy, "Y: %.6f", pos ? pos->y : 0.0f);
    sprintf(buffz, "Z: %.6f", pos ? pos->z : 0.0f);

    Consolas.renderChars(buffx, 20.0f, 60.0f, 0xFFFFFFFF);
    Consolas.renderChars(buffy, 20.0f, 77.0f, 0xFFFFFFFF);
    Consolas.renderChars(buffz, 20.0f, 94.0f, 0xFFFFFFFF);
}
}