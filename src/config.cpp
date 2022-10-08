#include <map>
#include "config.h"
#include "config_yaml.h"

configuration::configuration(cxxopts::ParseResult args) {
    if (args.count("config-file")) {
        config_file = args["config-file"].as<std::string>();
        if (config_file.empty()) {
            parse_yaml();
            return;
        }
    }
    SPDLOG_ERROR("required args: --config-file");
}

void configuration::parse_yaml() {
    try {
        config_yaml = YAML::LoadFile(config_file);

        // print yaml
        YAML::Emitter emitter;
        emitter << config_yaml;
        SPDLOG_DEBUG("load config yaml:{}\n", emitter.c_str());

        Config config = config_yaml.as<Config>();

        member     = config.server;
        clustering = config.raft;
        mysql      = config.mysql;

    } catch (const std::exception &e) {
        SPDLOG_ERROR("load yaml error: {}", e.what());
        std::exit(EXIT_FAILURE);
    }
}