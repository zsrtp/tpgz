#include <main.h>
#include "fast_eel_regrab_check.h"
#include "gz_flags.h"

namespace tpgz::modules {
void main() {
    GZFlg_addFlag(new GZFlag{GZFLG_FAST_EEL_REGRAB, ACTIVE_FUNC(STNG_TOOLS_FAST_EEL_REGRAB), GAME_LOOP,
                             FastEelRegrabChecker::execute});
}
void exit() {
    auto* flg = GZFlg_removeFlag(GZFLG_FAST_EEL_REGRAB);
    delete flg;
}

}  // namespace tpgz::modules