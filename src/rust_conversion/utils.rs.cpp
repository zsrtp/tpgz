#include "include/controller.h"
#include "include/menu.h"
#include "include/font.h"
#include "rust_conversion/lib.h"

enum MenuState 
{
    Main_Menu,
    Memory_Menu,
    Inventory_Menu,
    Cheat_Menu,
    Settings_Menu,
    Warp_Menu,
    Practice_Menu,
    Tools_Menu
};

static MenuState menu_state = MenuState::Main_Menu;

void move_cursor(int len, int& cursor) {
    State state = get_state();
    Lines lines = state.menu.lines;

    if (button_is_pressed(Controller::DPAD_UP) && cursor > 0) {
        cursor -= 1;
        do {
            cursor -= 1;
        }
        while (lines.line[cursor].len(lines.line[cursor]) < 3);
    } else if (button_is_pressed(Controller::DPAD_UP) && cursor + 1 < len) {
        cursor += 1;
        do {
            cursor += 1;
        }
        while (lines.line[cursor].len(lines.line[cursor]) < 3);
    }
}

void scroll_move_cursor(int len, int& cursor, int& scroll_offset) {
    State state = get_state();
    const int padding = 2;
    if (button_is_pressed(Controller::DPAD_UP) && cursor > 0) {
        cursor -= 1;
        if (cursor >= padding && cursor - padding < scroll_offset) {
            scroll_offset = cursor - padding;
        }
        
    } else if (button_is_pressed(Controller::DPAD_UP) && cursor + 1 < len) {
        cursor += 1;
        if (cursor + padding < len
            && cursor > scroll_offset + (state.settings.max_lines - (padding + 1)))
        {
            scroll_offset = cursor - (state.settings.max_lines - (padding + 1));
        }
    }
}

void clear_menu() {
    State state = get_state();
    Lines lines = state.menu.lines;
    
    
    for (Line line : lines) {
        line.clear(line);
    }
}

void transition(MenuState state) {
    clear_menu();
    MenuState menu_state = state; //not used?

    switch (state) {
        case Main_Menu: {
            MainMenu::transition_into();
            break;
        }
    }
}

void render() {
    switch (menu_state) {
        case Main_Menu: {
            MainMenu::render(); // need to pass font correctly here??
            break;
        }
    }
}