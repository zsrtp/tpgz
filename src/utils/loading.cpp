#include "utils/loading.hpp"
#include "libtp_c/include/tp.h"
#include "save_injector.h"
#include "menu.h"
#include "log.h"

bool loading_initiated = false;
int apply_after_counter = 0;

namespace Utilities {
    static Log log;
        void trigger_load() {
        if (tp_fopScnRq.isLoading == 0 && !loading_initiated) {
            log.PrintLog("Initiating warp", INFO);
            if (practice_file.inject_options_before_load) {
                practice_file.inject_options_before_load();
            }
            tp_gameInfo.warp.enabled = true;
        }

        if (tp_fopScnRq.isLoading == 1) {
            if (practice_file.inject_options_during_load) {
                practice_file.inject_options_during_load();
            }
            loading_initiated = true;
        }

        if (loading_initiated == true) {
            if (tp_fopScnRq.isLoading == 0) {
                if (practice_file.inject_options_after_load) {
                    practice_file.inject_options_after_load();
                }
                if (practice_file.inject_options_after_counter == apply_after_counter) {
                    apply_after_counter = 0;
                    practice_file.inject_options_after_counter = 0;
                    loading_initiated = false;
                    inject_save_flag = false;
                } else {
                    apply_after_counter++;
                }
            }
        }
    }
}