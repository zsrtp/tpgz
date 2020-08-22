#include <stdio.h>
#include "libtp_c/include/tp.h"
#include "libtp_c/include/controller.h"
#include "libtp_c/include/system.h"
#include "libtp_c/include/flag.h"
#include "controller.h"
#include "font.h"
#include "input_viewer.h"
#include "menu.h"

bool iv_visible;

namespace InputViewer {
    void render(Font& font) {
        using namespace Controller;

        if (button_is_down(A)) {
            font.renderChars("A", 150.0f, 440.0f, 0x00CC00FF);
        }

        if (button_is_down(B)) {
            font.renderChars("B", 165.f, 440.0f, 0xDC143CFF);
        }

        if (button_is_down(X)) {
            font.renderChars("X", 180.f, 440.0f, 0xFFFFFFFF);
        }

        if (button_is_down(Y)) {
            font.renderChars("Y", 195.f, 440.0f, 0xFFFFFFFF);
        }

        if (button_is_down(Z)) {
            font.renderChars("Z", 210.f, 440.0f, 0x8A2BE2FF);
        }

        if (button_is_down(START)) {
            font.renderChars("S", 225.f, 440.0f, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_LEFT)) {
            font.renderChars("DL", 240.f, 440.0f, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_DOWN)) {
            font.renderChars("DD", 265.f, 440.0f, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_RIGHT)) {
            font.renderChars("DR", 290.f, 440.0f, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_UP)) {
            font.renderChars("DU", 315.f, 440.0f, 0xFFFFFFFF);
        }

        if (button_is_down(L)) {
            font.renderChars("L", 340.f, 440.0f, 0xFFFFFFFF);
        }

        if (button_is_down(R)) {
            font.renderChars("R", 355.f, 440.0f, 0xFFFFFFFF);
        }

		// stick inputs
        char control_x[5]; // control stick x
        char control_y[5]; // control stick y
        char c_x[5]; // c stick x
        char c_y[5]; // c stick y

		sprintf(control_x, "%d", tp_mPadSticks.control_x);
        sprintf(control_y, "%d", tp_mPadSticks.control_y);
		sprintf(c_x, "%d", tp_mPadSticks.c_x);
        sprintf(c_y, "%d", tp_mPadSticks.c_y);

		font.gz_renderChars(control_x, 10.0f, 440.0f, 0xFFFFFFFF, g_drop_shadows);
        font.gz_renderChars(control_y, 45.0f, 440.0f, 0xFFFFFFFF, g_drop_shadows);
		font.gz_renderChars(c_x, 80.0f, 440.0f, 0xFFD138FF, g_drop_shadows);
        font.gz_renderChars(c_y, 115.0f, 440.0f, 0xFFD138FF, g_drop_shadows);
		
    }
}  // namespace InputViewer
