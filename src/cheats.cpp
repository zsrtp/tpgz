#include "libtp_c/include/controller.h"
#include "libtp_c/include/inventory.h"
#include "libtp_c/include/items.h"
#include "libtp_c/include/tp.h"

namespace Cheats {
    using namespace Controller;

    void apply_cheats() {
        if (tp_mPadStatus.sval == (Pad::R | Pad::A)) {
            if (tp_gameInfo.momentum_ptr) {
                tp_gameInfo.momentum_ptr->link_momentum.y = 56.0f;
            }
            Inventory::set_rupee_flags();
            Controller::set_buttons_down(0x0);
            Controller::set_buttons_pressed(0x0);
            tp_mPadButton.sval = 0x0;
            tp_mPadStatus.sval = 0x0;
        }
    }
}  // namespace Cheats