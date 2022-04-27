#include "logging.hpp"
#include "spdlog/sinks/daily_file_sink.h"

std::shared_ptr<spdlog::logger> logging::AppLogger;

void logging::OnInit() {
    spdlog::set_pattern("%m-%d %T.%e [%^%L%$] [%n] - %v");

    // create a daily logger - a new file is created every day on 2:30am.
    AppLogger = spdlog::daily_logger_mt(
            "app_logger", "logs/smartmha.log", 2, 30, false, 7);
    AppLogger->set_level(spdlog::level::info);
}