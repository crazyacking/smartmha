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

#include "mha/config.h"
#include "mha/config_yaml.h"
#include <map>

MHA_NAMESPACE_BEGIN

configuration::configuration(const cxxopts::ParseResult &args) {
    if (args.count("config-file")) {
        config_file = args["config-file"].as<std::string>();
        if (!config_file.empty()) {
            parse_yaml();
            return;
        }
    }
    MHA_LOG_ERROR("required args: --config-file");
}

void configuration::parse_yaml() {
    try {
        config_yaml = YAML::LoadFile(config_file);

        // print yaml
        YAML::Emitter emitter;
        emitter << config_yaml;
        MHA_LOG_DEBUG("load config yaml:{}", emitter.c_str());

        Config config = config_yaml.as<Config>();

        member     = config.server;
        clustering = config.raft;
        mysql      = config.mysql;
    } catch (const std::exception &e) {
        MHA_LOG_ERROR("load yaml error: {}", e.what());
        std::exit(EXIT_FAILURE);
    }
}

MHA_NAMESPACE_END