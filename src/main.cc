#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "utils.hpp"
#include "config.hpp"
#include "logging.hpp"

int main(int argc, char *argv[]) {
    logging::OnInit();

    auto options = Option::OnInit();
    auto args    = options.parse(argc, argv);

    if (args.count("help")) {
        std::cout << options.help() << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    configuration config(args);

    std::cout << config.member.name << std::endl;

    return 0;
}
