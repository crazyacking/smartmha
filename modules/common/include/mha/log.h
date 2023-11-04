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
#include "spdlog/spdlog.h"

MHA_NAMESPACE_BEGIN

class log {
  public:
    static void init();
    static std::shared_ptr<spdlog::logger> getAppLogger() {
        if (!logger_) {
            init();
        }
        return logger_;
    }

  private:
    static std::shared_ptr<spdlog::logger> logger_;
};

// logging macros
#define MHA_LOG_TRACE(...) log::getAppLogger()->trace(__VA_ARGS__)
#define MHA_LOG_DEBUG(...) log::getAppLogger()->debug(__VA_ARGS__)
#define MHA_LOG_INFO(...)  log::getAppLogger()->info(__VA_ARGS__)
#define MHA_LOG_WARN(...)  log::getAppLogger()->warn(__VA_ARGS__)
#define MHA_LOG_ERROR(...) log::getAppLogger()->error(__VA_ARGS__)
#define MHA_LOG_FATAL(...) log::getAppLogger()->fatal(__VA_ARGS__)

MHA_NAMESPACE_END