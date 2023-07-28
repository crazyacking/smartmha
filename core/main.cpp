#include "config.h"
#include "global.h"
#include "http_client.h"
#include "log.h"
#include "utils.h"

using namespace MHA_NAMESPACE;
using namespace std;

int main(int argc, char *argv[]) {
    log::init();
    auto options    = Option::init();
    const auto args = options.parse(argc, argv);

    const GlobalInitializer global_initializer;

    if (args.count("help")) {
        std::cout << options.help() << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    configuration config(args);
    SPDLOG_INFO("member name: {}", config.member.name);

    const auto client_ = std::make_unique<HttpClient>("https://www.cnblogs.com/");

    int status{-1};
    std::string response_body = client_->get("", {}, &status);
    if (status == 200) {
        SPDLOG_INFO("response_body={}", response_body);
    }
    SPDLOG_INFO("----------- smartmha end -----------");
    return 0;
}
