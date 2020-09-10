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
            font.renderChars("A", 550.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0x00CC00FF);
        }

        if (button_is_down(B)) {
            font.renderChars("B", 535.f + viewer_x_offset, 440.0f + viewer_y_offset, 0xDC143CFF);
        }

        if (button_is_down(X)) {
            font.renderChars("X", 565.f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(Y)) {
            font.renderChars("Y", 550.f + viewer_x_offset, 425.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(Z)) {
            font.renderChars("Z", 565.f + viewer_x_offset, 425.0f + viewer_y_offset, 0x8A2BE2FF);
        }

        if (button_is_down(START)) {
            font.renderChars("S", 500.f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_LEFT)) {
            font.renderChars("DL", 432.f + viewer_x_offset, 427.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_DOWN)) {
            font.renderChars("DD", 450.f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_RIGHT)) {
            font.renderChars("DR", 470.f + viewer_x_offset, 427.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(DPAD_UP)) {
            font.renderChars("DU", 450.f + viewer_x_offset, 414.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(L)) {
            font.renderChars("L", 500.f + viewer_x_offset, 425.0f + viewer_y_offset, 0xFFFFFFFF);
        }

        if (button_is_down(R)) {
            font.renderChars("R", 515.f + viewer_x_offset, 425.0f + viewer_y_offset, 0xFFFFFFFF);
        }

		// stick inputs
        char control_x[5];  // control stick x
        char control_y[5];  // control stick y
        char c_x[5];        // c stick x
        char c_y[5];        // c stick y

        sprintf(control_x, "%d", tp_mPadSticks.control_x);
        sprintf(control_y, "%d", tp_mPadSticks.control_y);
        sprintf(c_x, "%d", tp_mPadSticks.c_x);
        sprintf(c_y, "%d", tp_mPadSticks.c_y);

        font.gz_renderChars(control_x, 295.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFFFFFFF, g_drop_shadows);
        font.gz_renderChars(control_y, 330.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFFFFFFF, g_drop_shadows);
        font.gz_renderChars(c_x, 365.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFD138FF, g_drop_shadows);
        font.gz_renderChars(c_y, 400.0f + viewer_x_offset, 440.0f + viewer_y_offset, 0xFFD138FF, g_drop_shadows);

		// analog input viewer
        font.gz_renderChars(".", 313.0f + viewer_x_offset, 405.0f + viewer_y_offset, 0xFFFFFFFF, g_drop_shadows);
        font.gz_renderChars("o", (310.0f + viewer_x_offset) + (tp_mPadSticks.control_x * 0.20), (408.0f + viewer_y_offset) - (tp_mPadSticks.control_y * 0.20), 0xFFFFFFFF, g_drop_shadows);  // radius decreased to 20%
        font.gz_renderChars(".", 383.0f + viewer_x_offset, 405.0f + viewer_y_offset, 0xFFD138FF, g_drop_shadows);
        font.gz_renderChars("o", (380.0f + viewer_x_offset) + (tp_mPadSticks.c_x * 0.20), (408.0f + viewer_y_offset) - (tp_mPadSticks.c_y * 0.20), 0xFFD138FF, g_drop_shadows);  // radius decreased to 20%
    }
}  // namespace InputViewer