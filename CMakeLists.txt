cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(smartmha VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
include(FetchContent)

FetchContent_Declare(cxxopts URL https://github.com/jarro2783/cxxopts/archive/refs/tags/v3.0.0.tar.gz)
FetchContent_Declare(yaml-cpp URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.tar.gz)
FetchContent_Declare(spdlog URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz)
FetchContent_Declare(curl URL https://github.com/curl/curl/archive/refs/tags/curl-7_79_1.tar.gz)

FetchContent_MakeAvailable(
        cxxopts
        yaml-cpp
        spdlog
        curl
)

aux_source_directory(src DIR_SRC)
add_executable(${PROJECT_NAME} ${DIR_SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp spdlog::spdlog cxxopts::cxxopts CURL::libcurl)