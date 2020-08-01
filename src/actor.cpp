#include "actor.h"
#include "libtp_c/include/tp.h"
#include "libtp_c/include/actor.h"
#include "libtp_c/include/system.h"

namespace Actor {
    bool freeze_run_once;
    bool hide_run_once;

    void freeze_actors() {
        freeze_run_once = true;
        tp_actor.freeze = true;
    }

    void unfreeze_actors() {
        if (freeze_run_once){
            tp_actor.freeze = false;
            freeze_run_once = false;
        }
    }

    void hide_actors() {
        hide_run_once = true;
        tp_stopstatus.hide_actors = true;
    }

    void show_actors() {
        if (hide_run_once) {
            tp_stopstatus.hide_actors = false;
            hide_run_once = false;
        }
    }

}


