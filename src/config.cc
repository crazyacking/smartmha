#include <map>
#include "config.hpp"
#include "config_yaml.hpp"

configuration::configuration(cxxopts::ParseResult args) {
    if (args.count("config-file")) {
        config_file = args["config-file"].as<std::string>();
        parse_yaml();
    } else {
        // todo: parse from args
    }
}

void configuration::parse_yaml() {
    try {

        config_yaml = YAML::LoadFile(config_file);

        // print yaml
        YAML::Emitter emitter;
        emitter << config_yaml;
        logger->info(std::string("load config yaml:\n") + emitter.c_str());

        Config config = config_yaml.as<Config>();

        member     = config.server;
        clustering = config.raft;
        mysql      = config.mysql;

    } catch (const std::exception &e) {
        logger->error("load yaml error: {}", e.what());
        std::exit(EXIT_FAILURE);
    }
}