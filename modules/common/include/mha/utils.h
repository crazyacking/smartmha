// Copyright (c) 2023 Dylan Jiang(crazyacking). All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Authors: Dylan Jiang(crazyacking@gmail.com)

#pragma once

#include "mha/base.h"
#include <atomic>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <mutex>
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

static auto GetDate() -> std::string {
    auto now = std::chrono::system_clock::now();
    auto itt = std::chrono::system_clock::to_time_t(now);

    std::ostringstream ss;
    ss << std::put_time(std::localtime(&itt), "%Y-%m-%d");
    return ss.str();
}

MHA_NAMESPACE_END