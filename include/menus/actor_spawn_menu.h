#include "menu.h"

enum {
    ACTOR_ID_INDEX,
    ACTOR_PARAM_INDEX,
    ACTOR_SUBTYPE_INDEX,
    ACTOR_SPAWN_INDEX,
};

class ActorSpawnMenu : public Menu {
public:
    ActorSpawnMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};

class ActorListMenu : public Menu {
public:
    ActorListMenu() : Menu() {}
    static void draw();

    static Cursor cursor;
};