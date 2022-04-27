cmake_minimum_required(VERSION 3.22)
project(smartmha VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
include(FetchContent)

FetchContent_Declare(yaml-cpp URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.tar.gz)
FetchContent_Declare(spdlog URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz)

FetchContent_MakeAvailable(yaml-cpp)
FetchContent_MakeAvailable(spdlog)

include_directories(3rdparty/cxxopts/include)
include_directories(3rdparty/loguru/include)

aux_source_directory(src DIR_SRC)
add_executable(${PROJECT_NAME} ${DIR_SRC} 3rdparty/loguru/include/loguru.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp spdlog::spdlog)