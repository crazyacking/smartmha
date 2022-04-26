#include <iostream>
#include "cxxopts.hpp"
#include "loguru.hpp"
#include "args_helper.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {
    loguru::init(argc, argv);
    loguru::add_file(
            (std::string("/tmp/smartmha/") + GetDate() + ".log").c_str(),
            loguru::Append,
            loguru::Verbosity_WARNING);

    cxxopts::Options options = InitOptions();
    auto args = options.parse(argc, argv);

    if (args.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    return 0;
}
