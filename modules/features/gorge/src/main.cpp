#include <main.h>
#include "gz_flags.h"
#include "commands.h"
#include "gorge.h"

namespace tpgz::modules {
void main() {
    GZCmd_addCmd(new Command{CMD_GORGE_VOID, g_commandStates[CMD_GORGE_VOID], GORGE_VOID_BUTTONS,
                             GZCmd_loadGorgeVoid});
    GZCmd_enable(Commands::CMD_GORGE_VOID);
    GZFlg_addFlag(new GZFlag{GZFLG_GORGE_VOID, &g_tools[GORGE_INDEX].active, GAME_LOOP,
                             GorgeVoidIndicator::execute});
}
void exit() {
    auto* flg = GZFlg_removeFlag(GZFLG_GORGE_VOID);
    delete flg;
    GZCmd_disable(Commands::CMD_GORGE_VOID);
    auto* cmd = GZCmd_removeCmd(CMD_GORGE_VOID);
    delete cmd;
}

}  // namespace tpgz::modules