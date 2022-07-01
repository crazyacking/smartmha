#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "utils.hpp"
#include "config.hpp"
#include "logging.hpp"
#include "http_client.hpp"
#include "http_client_impl.hpp"

int main(int argc, char *argv[]) {
    logging::OnInit();

    auto options = Option::OnInit();
    auto args = options.parse(argc, argv);

    if (args.count("help")) {
        std::cout << options.help() << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    configuration config(args);

    std::cout << config.member.name << std::endl;

    std::shared_ptr<HttpClient> client_ = std::make_shared<HttpClientImpl>("https://www.cnblogs.com/");
    int status = -1;

    std::string response_body = client_->get("", {}, &status);
    std::cout << response_body << std::endl;


    return 0;
}
