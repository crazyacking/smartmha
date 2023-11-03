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

#include "mha/log.h"
#include "spdlog/sinks/daily_file_sink.h"

MHA_NAMESPACE_BEGIN

std::shared_ptr<spdlog::logger> log::logger_ = nullptr;

void log::init() {
    spdlog::set_pattern("[%Y-%m-%d %T.%e][%L][%t][%s:%#][%!] %v");

    // create a daily logger - a new file is created every day on 2:30am.
    log::logger_ = spdlog::daily_logger_mt("smartmha", "smartmha.log", 2, 30, false, 7);
    log::logger_->set_level(spdlog::level::debug);
    spdlog::set_default_logger(log::logger_);
}

MHA_NAMESPACE_END