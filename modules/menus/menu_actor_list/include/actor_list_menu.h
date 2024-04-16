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
    void loadPrevInfo(void* buffer, signed long& counter, signed long length, char max_num,
                      int offset);
    void loadNextInfo(void* buffer, signed long& counter, signed long length, char max_num,
                      int offset);
    void setStagePath(int current_stage_type);

    uint16_t& l_index;
    Line lines[3];
};