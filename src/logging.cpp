#include "logging.h"
#include "spdlog/sinks/daily_file_sink.h"

void logging::OnInit() {
    spdlog::set_pattern("[%Y-%m-%d %T.%e][%L][%t][%s:%#][%!] %v");

    // create a daily logger - a new file is created every day on 2:30am.
    auto default_logger = spdlog::daily_logger_mt(
            "smartmha", "logs/smartmha.log", 2, 30, false, 7);
    default_logger->set_level(spdlog::level::debug);
    spdlog::set_default_logger(default_logger);
}