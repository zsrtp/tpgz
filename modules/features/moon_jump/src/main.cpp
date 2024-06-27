#include <main.h>
#include "commands.h"
#include "settings.h"
#include "libtp_c/include/d/com/d_com_inf_game.h"
#include "libtp_c/include/JSystem/JUtility/JUTGamePad.h"

KEEP_FUNC void GZCmd_moonJump() {
    if (dComIfGp_getPlayer()) {
        dComIfGp_getPlayer()->speed.y = 56.0f;
    }
}

KEEP_VAR bool active = false;

namespace tpgz::modules {
void main() {
    GZCmd_addCmd(new Command{CMD_MOON_JUMP,
                             GZStng_getData<uint16_t>(STNG_CMD_MOON_JUMP, MOON_JUMP_BUTTONS),
                             GZCmd_moonJump});
}
void exit() {
    auto* cmd = GZCmd_removeCmd(CMD_MOON_JUMP);
    delete cmd;
}

}  // namespace tpgz::modules