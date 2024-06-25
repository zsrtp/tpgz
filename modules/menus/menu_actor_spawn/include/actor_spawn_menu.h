#include "menus/menu.h"

#define MAX_ACTORS 10

/**
 * @struct procBinData
 * @brief Structure for entries in res/proc_info/procs.bin
 */
struct procBinData {
    s16 procId;
    char procName[30];
}__attribute__((aligned(32)));

struct ActorSpawnData {
    Cursor cursor;
    s16 l_actorID;
    uint32_t l_actorParams = 0xFFFFFFFF;
    int8_t l_actorType = -1;
    uint8_t l_paramIdx;
};

struct ActorSpawn {
    s16 id;
    uint32_t params;
    int8_t type;
};

enum {
    ACTOR_NAME_INDEX,
    ACTOR_PARAM_INDEX,
    ACTOR_SUBTYPE_INDEX,
    ACTOR_SPAWN_INDEX,
};

class ActorSpawnMenu : public Menu {
public:
    ActorSpawnMenu(ActorSpawnData&);
    virtual ~ActorSpawnMenu();
    virtual void draw();

private:
    void loadActorName(s16&);
    s16& l_actorID;
    uint32_t& l_actorParams;
    int8_t& l_actorType;
    uint8_t& l_paramIdx;
    bool l_paramsSelected;
    ActorSpawn l_actorQueue[MAX_ACTORS];

    Line lines[4];
};
