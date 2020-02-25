#include "controller.h"
#include "font.h"
#include "menu.h"

// struct Vec3 {
//     float x, y, z;
// };
// static_assert(sizeof(Vec3) == 0xC);

void move_cursor(int& cursor, int LINES);
void menu_anim(Font& font, int idx);
void render_lines(Font& font, Line lines[], int cursor, int LINES);