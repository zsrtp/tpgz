#include "menu.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"

struct ActorListData {
    uint16_t l_index;
    bool l_dataLoaded;
};

enum {
    ACTOR_NAME_INDEX,
    ACTOR_POSITION_X_INDEX,
    ACTOR_POSITION_Y_INDEX,
    ACTOR_POSITION_Z_INDEX,
    ACTOR_ANGLE_X_INDEX,
    ACTOR_ANGLE_Y_INDEX,
    ACTOR_ANGLE_Z_INDEX,

    ACTOR_LIST_LINE_COUNT,
};

class ActorListMenu : public Menu {
public:
    ActorListMenu(Cursor&, ActorListData&);
    void updateActorData();
    void loadActorName();
    virtual ~ActorListMenu();
    virtual void draw();

private:
    uint16_t& l_index;
    bool& l_dataLoaded;

    Line lines[ACTOR_LIST_LINE_COUNT];
    s32 l_cameraPlay;
    bool l_halt;
    fopAc_ac_c* l_currentActor;
};