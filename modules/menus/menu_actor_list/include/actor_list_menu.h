#include "menu.h"

struct ActorListData {
    uint16_t l_index;
};

enum {
    ACTOR_ID_INDEX,
};

class ActorListMenu : public Menu {
public:
    ActorListMenu(Cursor&, ActorListData&);
    virtual ~ActorListMenu();
    virtual void draw();

private:
    uint16_t& l_index;
    Line lines[3];
};
