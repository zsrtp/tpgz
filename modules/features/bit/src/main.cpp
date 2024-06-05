#include <main.h>
#ifdef WII_PLATFORM
#include "bit.h"
#endif
#include "gz_flags.h"

namespace tpgz::modules {
void main() {
#ifdef WII_PLATFORM
    GZCmd_addCmd(
        new Command{CMD_BIT, g_commandStates[CMD_BIT], BACK_IN_TIME_BUTTONS, GZCmd_bitPractice});
    GZFlg_addFlag(
        new GZFlag{GZFLG_BIT, &g_tools[BIT_INDEX].active, GAME_LOOP, BiTIndicator::execute});
#endif
}
void exit() {
#ifdef WII_PLATFORM
    auto* flg = GZFlg_removeFlag(GZFLG_BIT);
    delete flg;
    auto* cmd = GZCmd_removeCmd(CMD_BIT);
    delete cmd;
#endif
}

}  // namespace tpgz::modules