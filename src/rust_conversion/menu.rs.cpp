#include <string.h>
#include "rust_conversion/menu.h"
#include "rust_conversion/lib.h"

Menu Menu::New(float x, float y) {
    // finish
}

void Line::push_str(Line line, const char* string) {
    line.text.push_str(string);  // push_str isn't implemented here in the rust code so idk how this works
}

int Line::len(Line line) {
    // wouldn't this always be 128? 
    return line.text.length();
}

bool Line::is_empty(Line line) {
    return line.len(line) == 0;
}
void Line::clear(Line line) {
    line.text.clear(); // clear isn't implemented here in the rust code so idk how this works
    line.selected = false;
}

LineWriter Line::write_at(Line line, int pos) {
    LineWriter line_writer;
    line_writer.line = line;
    line_writer.position = pos;
    return line_writer;
}

LineWriter append(Line line) {
    int len = line.len(); // how do i get the line length?
    LineWriter line_writer;
    line_writer.line = line;
    line_writer.position = len;
    return line_writer;
}

LineWriter begin(Line line) {
    line.clear(line);
    LineWriter line_writer;
    line_writer.line = line;
    line_writer.position = 0;
    return line_writer;
}

Line New() {
    Line line;
    strcpy(line.text, "");
    line.selected = false;
    return line;
}

Menu Default() {
    Menu menu;
    menu.x = 20.0;
    menu.y = 20.0;
    menu.offset = 1.2;
    menu.selected_color = 0x0000FFFF;
    menu.color = 0xFFFFFFFF;
    menu.lines[32] = Line::New(); // not sure how to properly set this
    menu.selected_word = None; // what is 'None'
    menu.selected_char = None; // what is ;None'
    return menu;
}

void clear(Menu menu) {
    Lines lines = menu.lines;
    for (Line line: lines) { // something is missing here but not sure
        line.clear(line);
    }
}

Lines lines(Menu menu) {
    return menu.lines;
}

Line line(Menu menu, int idx) {
    return menu.lines.line[idx];
}

void draw(Menu menu) {
    State state = get_state();

    // this enumeration logic might be wrong
    for (int index = 0; index < 0; index++) {
        Line line = menu.lines.line[index];
        float y = menu.y + (state.font.font.size * menu.offset) * (float)index;
        uint32_t color;
        if (line.selected) {
            color = menu.selected_color;
        } else {
            color = menu.color;
        }

        if (line.is_empty()) {
            continue;
        }

        if (line.selected && menu.selected_word) {
            printf_select(line.text.as_str(), menu.selected_word, menu.selected_char, menu.x, y,
                          menu.color);
        } else {
            printf(line.text.as_str(), menu.x, y, color);
        }
    }
}

// impl<'a> Write for LineWriter<' a> {
//     fn write_str(&mut self, s
//                  : &str)
//         ->Result<(), Error> {
//         if
//             s.len() > 128 {
//                 self.line.push_str(&s[..128]);
//             }
//         else {
//             self.line.push_str(s);
//         }
//         self.position += s.len();
//         Ok(())
//     }
// }