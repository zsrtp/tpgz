#pragma once
#include "menu.h"
#include "save_manager.h"

#define ANY_INDEX 0
#define HUNDO_INDEX 1
#define AD_INDEX 2
#define REQ_POS 1
#define REQ_CAM 2
extern bool g_injectSave;
extern int last_save_index;
extern char last_category[5];
extern special* last_special_ptr;
extern int last_special_size;

class PracticeMenu : public Menu {
public:
    PracticeMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};