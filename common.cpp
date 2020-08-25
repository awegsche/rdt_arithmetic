#include "common.h"

void init_logging() {
    #ifndef NOLOG
    auto console = spdlog::stdout_color_st("logger");
    #endif
}