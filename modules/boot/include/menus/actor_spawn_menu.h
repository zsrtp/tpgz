#include "menu.h"

enum {
    ACTOR_ID_INDEX,
    ACTOR_PARAM_INDEX,
    ACTOR_SUBTYPE_INDEX,
    ACTOR_SPAWN_INDEX,
};

class ActorSpawnMenu : public Menu {
public:
    ActorSpawnMenu();
    virtual void draw();

    Cursor cursor;

private:
    uint16_t l_actorID;
    uint32_t l_actorParams;
    int8_t l_actorType;
    uint8_t l_paramIdx;
    bool l_paramsSelected;

    Line lines[4];
};

class ActorListMenu : public Menu {
public:
    ActorListMenu();
    virtual void draw();

    Cursor cursor;
private:
    uint16_t l_index;
    Line lines[1];
};