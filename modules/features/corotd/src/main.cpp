#include <main.h>
#include "corotdcheck.h"
#include "gz_flags.h"

namespace tpgz::modules {
void main() {
    GZFlg_addFlag(
        new GZFlag{GZFLG_COROTD, &g_tools[COROTD_INDEX].active, GAME_LOOP, CoroTDChecker::execute});
}
void exit() {
    auto* flg = GZFlg_removeFlag(GZFLG_COROTD);
    delete flg;
}

}  // namespace tpgz::modules