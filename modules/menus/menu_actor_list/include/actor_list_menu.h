#include "menus/menu.h"
#include "libtp_c/include/f_op/f_op_actor_mng.h"

struct ActorListData {
    uint16_t l_index;
};

/**
 * @struct procBinData
 * @brief Structure for entries in res/proc_info/procs.bin
 */
struct procBinData {
    s16 procId;
    char procName[30];
}__attribute__((aligned(32)));

enum {
    ACTOR_NAME_INDEX,
    ACTOR_POSITION_X_INDEX,
    ACTOR_POSITION_Y_INDEX,
    ACTOR_POSITION_Z_INDEX,
    ACTOR_ANGLE_X_INDEX,
    ACTOR_ANGLE_Y_INDEX,
    ACTOR_ANGLE_Z_INDEX,
    ACTOR_PROC_INDEX,
    ACTOR_PARAMS_INDEX,

    ACTOR_LIST_LINE_COUNT,
};

class ActorListMenu : public Menu {
public:
    ActorListMenu(Cursor&, ActorListData&);
    virtual ~ActorListMenu();
    virtual void draw();

private:
    void updateActorData();
    template <typename T>
    void updateValue(T*, bool, bool, bool);
    void loadActorName();
    void checkAndCloseMenu();
    void checkAndRestoreMenu();
    
    u16& l_index;

    Line lines[ACTOR_LIST_LINE_COUNT];
    s32 l_cameraPlay;
    bool l_halt;
    u8 l_menuStatus;
    u8 l_windowStatus;
    cXyz l_cameraPos;
    cXyz l_cameraTarget;
};