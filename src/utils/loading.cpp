#include "utils/loading.hpp"
#include "libtp_c/include/tp.h"
#include "save_injector.h"
#include "fs.h"
#include "menu.h"

bool loading_initiated = false;
int apply_after_counter = 0;

namespace Utilities {
    void load_save_file(const char* fileName) {
        uint8_t qlog_bytes[2392] __attribute__ ((aligned (32)));
        loadFile(fileName, qlog_bytes, 2400, 0);
        // load file
        SaveInjector::inject_save(qlog_bytes);

    }
    void trigger_load() {
        if (tp_fopScnRq.isLoading == 0 && !loading_initiated) {
            
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
}  // namespace Utilities