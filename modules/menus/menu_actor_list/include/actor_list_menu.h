#include "menu.h"

struct ActorListData {
    Cursor cursor;
    uint16_t l_index;
};

enum {
    ACTOR_ID_INDEX,
};

class ActorListMenu : public Menu {
public:
    ActorListMenu(ActorListData&);
    virtual ~ActorListMenu();
    virtual void draw();

    Cursor& cursor;

private:
    uint16_t& l_index;
    Line lines[1];
};
