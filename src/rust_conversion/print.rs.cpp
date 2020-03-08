#include "rust_conversion/lib.h"

void setup_draw() {
    State state = get_state();
    state.font.setupRendering();
}

void printf(const char * s, float x, float y, uint32_t top_color) {
    State state = get_state();
    if (state.settings.drop_shadow) {
        state.font.renderChars(s, x + 2.0, y + 2.0, 0x000000FF);
    }
    state.font.renderChars(s, x, y, top_color);
}

void printf_select(const char * s, int word_index, int char_index, float x, float y, uint32_t top_color) {
    State state = get_state();

    // not sure how to split/enumerate like this

    
    //let split = s.split(' ');
    // for (i, s) in split.into_iter().enumerate() {
    //     for (c_i, c) in s.chars().enumerate() {
    //         if settings.drop_shadow {
    //             font.render_char(c, x + 2.0, y + 2.0, 0x00_00_00_FF);
    //         }
    //         x = font.render_char(
    //             c,
    //             x,
    //             y,
    //             if let Some(char_index) = char_index {
    //                 if i == word_index && char_index == c_i {
    //                     0x00_00_FF_FF
    //                 } else {
    //                     top_color
    //                 }
    //             } else if i == word_index {
    //                 0x00_00_FF_FF
    //             } else {
    //                 top_color
    //             },
    //         );
    //     }
    //     x = font.render_char(' ', x, y, top_color);
    // }
}