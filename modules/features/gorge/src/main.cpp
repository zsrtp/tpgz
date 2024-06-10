#include <main.h>
#include "gz_flags.h"
#include "commands.h"
#include "gorge.h"

namespace tpgz::modules {
void main() {
    GZCmd_addCmd(new Command{CMD_GORGE_VOID, GORGE_VOID_BUTTONS,
                             GZCmd_loadGorgeVoid});
    GZFlg_addFlag(new GZFlag{GZFLG_GORGE_VOID, ACTIVE_FUNC(STNG_TOOLS_GORGE), GAME_LOOP,
                             GorgeVoidIndicator::execute});
}
void exit() {
    auto* flg = GZFlg_removeFlag(GZFLG_GORGE_VOID);
    delete flg;
    auto* cmd = GZCmd_removeCmd(CMD_GORGE_VOID);
    delete cmd;
}

}  // namespace tpgz::modules