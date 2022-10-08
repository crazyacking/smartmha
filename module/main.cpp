#include "utils.h"
#include "config.h"
#include "logging.h"
#include "http_client.h"
#include "http_client_impl.h"

int main(int argc, char *argv[]) {
    logging::OnInit();

    auto options = Option::OnInit();
    auto args    = options.parse(argc, argv);

    if (args.count("help")) {
        std::cout << options.help() << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    configuration config(args);

    SPDLOG_INFO("member name: {}", config.member.name);

    std::shared_ptr<HttpClient> client_ = std::make_shared<HttpClientImpl>("https://www.cnblogs.com/");

    int         status        = -1;
    std::string response_body = client_->get("", {}, &status);
    SPDLOG_INFO("----------- smartmha end -----------");
    return 0;
}
