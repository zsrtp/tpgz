#include "menus/actor_spawn_menu.h"
#include "menus/settings_menu.h"
#include "controller.h"
#include "font.h"
#include "utils/cursor.h"
#include "utils/lines.h"
#include "libtp_c/include/msl_c/string.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"

#define LINES 4

static Cursor cursor = {0, 0};
bool lock_cursor_y = false;
bool lock_cursor_x = false;
bool init_once = false;

int16_t actor_id = 0;
uint32_t actor_params = 0;
int8_t actor_type = -1;
uint8_t param_index = 0;
bool params_selected = false;

Line lines[LINES] = {{"actor id:", ACTOR_ID_INDEX, "Actor ID (Dpad / X/Y to scroll)", false},
                     {"actor params:", ACTOR_PARAM_INDEX, "Actor Parameters (default: 0)", false},
                     {"actor subtype:", ACTOR_SUBTYPE_INDEX, "Actor subtype (default: -1) (Dpad / X/Y to scroll)", false},
                     {"spawn", ACTOR_SPAWN_INDEX, "Spawn actor at current position", false}};

void actorFastCreateAtLink(short id, uint32_t parameters, int8_t subtype) {
    fopAcM_create(id, parameters, &dComIfGp_getPlayer()->mCurrent.mPosition,
                  dComIfGp_getPlayer()->mCurrent.mRoomNo, &dComIfGp_getPlayer()->mCurrent.mAngle,
                  nullptr, subtype);
}

// returns the width of the rendered string
float render_selected_number_selector(const char* str, float x, float y, size_t selected_char_index,
                                      size_t max_char, uint32_t color) {
    float pos = 0.0f;
    for (size_t i = 0; i <= max_char; ++i) {
        Font::gz_renderChar(str[i], x + pos, y, selected_char_index == i ? CURSOR_RGBA : color,
                            g_drop_shadows);
        pos += Font::get_char_width(str[i]);
    }
    return pos;
}

void ActorSpawnMenu::render() {
    if (button_is_pressed(BACK_BUTTON)) {
        if (params_selected) {
            lock_cursor_y = false;
            params_selected = false;
        } else {
            init_once = false;
            MenuRendering::set_menu(MN_SCENE_INDEX);
            return;
        }
    }

    if (!init_once) {
        current_input = 0;
        init_once = true;
    }

    if (current_input == SELECTION_BUTTON && a_held == false) {
        switch (cursor.y) {
        case ACTOR_PARAM_INDEX: {
            lock_cursor_y = true;
            params_selected = true;
            break;
        }
        case ACTOR_SPAWN_INDEX: {
            actorFastCreateAtLink(actor_id, actor_params, actor_type);
            break;
        }
        }
    }

    switch (cursor.y) {
    case ACTOR_ID_INDEX: {
        if (button_is_pressed(Controller::DPAD_RIGHT)) {
            actor_id++;
        } else if (button_is_pressed(Controller::DPAD_LEFT)) {
            actor_id--;
        } else if (button_is_pressed(Controller::X)) {
            actor_id += 10;
        } else if (button_is_pressed(Controller::Y)) {
            actor_id -= 10;
        }
        break;
    }
    case ACTOR_SUBTYPE_INDEX: {
        if (button_is_pressed(Controller::DPAD_RIGHT)) {
            actor_type++;
        } else if (button_is_pressed(Controller::DPAD_LEFT)) {
            actor_type--;
        } else if (button_is_pressed(Controller::X)) {
            actor_type += 10;
        } else if (button_is_pressed(Controller::Y)) {
            actor_type -= 10;
        }
        break;
    }
    }

    char buf[9];
    tp_sprintf(buf, "%08X", actor_params);
    if (params_selected) {
        if (button_is_pressed(Controller::DPAD_RIGHT)) {
            if (param_index == 7) {
                param_index = 0;
            } else if (param_index >= 0 && param_index < 8) {
                param_index++;
            }
        }
        if (button_is_pressed(Controller::DPAD_LEFT)) {
            if (param_index == 0) {
                param_index = 7;
            } else if (param_index >= 0 && param_index < 8) {
                param_index--;
            }
        }
        if (button_is_pressed(Controller::DPAD_UP)) {
            switch (param_index) {
            case 0: {
                actor_params += 0x10000000;
                break;
            }
            case 1: {
                actor_params += 0x1000000;
                break;
            }
            case 2: {
                actor_params += 0x100000;
                break;
            }
            case 3: {
                actor_params += 0x10000;
                break;
            }
            case 4: {
                actor_params += 0x1000;
                break;
            }
            case 5: {
                actor_params += 0x100;
                break;
            }
            case 6: {
                actor_params += 0x10;
                break;
            }
            case 7: {
                actor_params += 0x1;
                break;
            }
            }
        }
        if (button_is_pressed(Controller::DPAD_DOWN)) {
            switch (param_index) {
            case 0: {
                actor_params -= 0x10000000;
                break;
            }
            case 1: {
                actor_params -= 0x1000000;
                break;
            }
            case 2: {
                actor_params -= 0x100000;
                break;
            }
            case 3: {
                actor_params -= 0x10000;
                break;
            }
            case 4: {
                actor_params -= 0x1000;
                break;
            }
            case 5: {
                actor_params -= 0x100;
                break;
            }
            case 6: {
                actor_params -= 0x10;
                break;
            }
            case 7: {
                actor_params -= 0x1;
                break;
            }
            }
        }
        render_selected_number_selector(buf, 170.0f, 80.0f, param_index, 7, 0xFFFFFFFF);
    } else {
        Font::gz_renderChars(buf, 170.0f, 80.0f, (cursor.y == ACTOR_PARAM_INDEX ? CURSOR_RGBA : 0xFFFFFFFF),
                             g_drop_shadows);
    }

    tp_sprintf(lines[ACTOR_ID_INDEX].value, " <%d>", actor_id);
    tp_sprintf(lines[ACTOR_SUBTYPE_INDEX].value, " <%d>", actor_type);

    Utilities::move_cursor(cursor, LINES, 8, lock_cursor_x, lock_cursor_y, false, true);
    Utilities::render_lines(lines, cursor.y, LINES);
};
