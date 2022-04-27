#pragma once

#include "spdlog/spdlog.h"

class logging {
private:
    static std::shared_ptr<spdlog::logger> AppLogger;
public:
    static void OnInit();

    inline static std::shared_ptr<spdlog::logger> &getAppLogger() { return AppLogger; };
};

//logging macros
#ifdef _DEBUG
#define MHA_TRACE(...) logging::getAppLogger()->trace(__VA_ARGS__)
#define MHA_INFO(...)  logging::getAppLogger()->info(__VA_ARGS__)
#define MHA_WARN(...)  logging::getAppLogger()->warn(__VA_ARGS__)
#define MHA_ERROR(...) logging::getAppLogger()->error(__VA_ARGS__)
#define MHA_FATAL(...) logging::getAppLogger()->fatal(__VA_ARGS__)

#elif _NDEBUG
#define MHA_TRACE
#define MHA_INFO(...)  logging::getAppLogger()->info(__VA_ARGS__)
#define MHA_WARN(...)  logging::getAppLogger()->warn(__VA_ARGS__)
#define MHA_ERROR(...) logging::getAppLogger()->error(__VA_ARGS__)
#define MHA_FATAL(...) logging::getAppLogger()->fatal(__VA_ARGS__)
#endif

