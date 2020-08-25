#define NOLOG
#pragma once
#include <giac/config.h>
#include <giac/giac.h>
#ifndef NOLOG
    #include "spdlog/fmt/ostr.h"
    #include "spdlog/sinks/stdout_color_sinks.h"
    #include "spdlog/spdlog.h"
#else
    #include <stdio.h>
#endif


using giac::gen;

#ifndef NOLOG
    #define LOG(...) spdlog::info(__VA_ARGS__)
    #define WRN(...) spdlog::warn(__VA_ARGS__)

    template <typename OStream> OStream &operator<<(OStream &os, const gen &g) {
    return os << g;
    }

#else

    #define LOG(...) std::cout << "\33[37mlog suppressed\33[0m" << std::endl; //printf( __VA_ARGS__)
    #define WRN(...) std::cout << "\33[37mlog suppressed\33[0m" << std::endl; //printf( __VA_ARGS__)

#endif


void init_logging();