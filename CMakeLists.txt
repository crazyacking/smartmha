cmake_minimum_required(VERSION 3.22)
project(smartmha VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(third_party/cxxopts/include)
include_directories(third_party/loguru/include)
include_directories(third_party/yaml-cpp-0.7.0/include)

aux_source_directory(src DIR_SRC)
add_executable(smartmha ${DIR_SRC} third_party/loguru/include/loguru.cpp)