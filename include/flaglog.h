#pragma once

extern bool g_flag_log_active;

namespace FlagLog {
void run();
void display_log(const char* name, uint8_t record*, uint8_t saved_record[], int record_size);
void save_record(uint8_t record*, uint8_t saved_record[], int record_size);
}  // namespace FlagLog