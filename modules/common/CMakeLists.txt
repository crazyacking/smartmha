set(module mha_common)

message(STATUS "==> Lib ${module}")

include(FetchContent)
FetchContent_Declare(cxxopts URL https://github.com/jarro2783/cxxopts/archive/refs/tags/v3.0.0.tar.gz)
FetchContent_Declare(yaml-cpp URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.tar.gz)
FetchContent_Declare(spdlog URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz)
FetchContent_Declare(curl URL https://github.com/curl/curl/archive/refs/tags/curl-7_79_1.tar.gz)
FetchContent_MakeAvailable(cxxopts yaml-cpp spdlog curl)

file(GLOB_RECURSE headers include/mha/*.h)
file(GLOB_RECURSE sources src/*.cpp)

message(STATUS "header files: ${headers}")
message(STATUS "source files: ${sources}")

#target_link_libraries(${module} PRIVATE yaml-cpp::yaml-cpp spdlog::spdlog cxxopts::cxxopts CURL::libcurl ${META_PROJECT_NAME}::base ${META_PROJECT_NAME}::raft)
add_library(${module} ${headers} ${sources})
add_library(${META_PROJECT_NAME}::${module} ALIAS ${module})
target_link_libraries(${module} PRIVATE yaml-cpp::yaml-cpp spdlog::spdlog cxxopts::cxxopts CURL::libcurl)