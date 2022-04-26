cmake_minimum_required(VERSION 3.22)
project(smartmha VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)


#include(ExternalProject)
#set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
#
#ExternalProject_Add(
#        cxxopts
#        GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
#        GIT_TAG v3.0.0
#        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
#        STEP_TARGETS build
#)

include_directories(third_party/cxxopts/include)
include_directories(third_party/loguru/include)

aux_source_directory(src DIR_SRC)
add_executable(smartmha ${DIR_SRC} third_party/loguru/include/loguru.cpp)