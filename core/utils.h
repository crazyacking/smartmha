#pragma once

#include "base.h"
#include <chrono>
#include <shared_mutex>
#include <string>

MHA_NAMESPACE_BEGIN

#define MSTR(x) stringify(x) // Stringify a macro
#if defined __clang__
#define COMPILER_STR "CLANG " __clang_version__
#elif defined __GNUC__
#define COMPILER_STR "GCC " MSTR(__GNUC__) "." MSTR(__GNUC_MINOR__) "." MSTR(__GNUC_PATCHLEVEL__)
#elif defined _MSC_VER
#define COMPILER_STR "MSC " MSTR(_MSC_FULL_VER)
#else
#define COMPILER_STR "UNKNOWN COMPILER"
#endif

#define SMARTMHA_VERSION "v1.0.0"

#ifndef NDEBUG
#define SMARTMHA_VERSION_STR                                                                                           \
    "smartmha " SMARTMHA_VERSION " (debug)"                                                                            \
    " (" COMPILER_STR ")"
#else
#define SMARTMHA_VERSION_STR "smartmha " SMARTMHA_VERSION " (" COMPILER_STR ")"
#endif

typedef std::shared_timed_mutex mha_lock_mutex;
typedef std::unique_lock<mha_lock_mutex> mha_write_lock;
typedef std::shared_lock<mha_lock_mutex> mha_read_lock;

static auto GetDate() -> std::string {
    auto now = std::chrono::system_clock::now();
    auto tt  = std::chrono::system_clock::to_time_t(now);
    auto tm  = localtime(&tt);
    char buff[12];
    std::sprintf(buff, "%d-%02d-%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    return buff;
}
MHA_NAMESPACE_END