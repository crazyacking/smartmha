cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(smartmha VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ARG_DOWNLOAD_EXTRACT_TIMESTAMP TRUE)

execute_process(COMMAND hostname OUTPUT_VARIABLE HOSTNAME OUTPUT_STRIP_TRAILING_WHITESPACE)
message("-- Hostname: ${HOSTNAME}")
message("-- System arch: ${CMAKE_SYSTEM_PROCESSOR}")
message("-- Output path: ${PROJECT_OUTPUT_DIR}")

include(FetchContent)
FetchContent_Declare(cxxopts URL https://github.com/jarro2783/cxxopts/archive/refs/tags/v3.0.0.tar.gz)
FetchContent_Declare(yaml-cpp URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.tar.gz)
FetchContent_Declare(spdlog URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz)
FetchContent_Declare(curl URL https://github.com/curl/curl/archive/refs/tags/curl-7_79_1.tar.gz)
FetchContent_MakeAvailable(cxxopts yaml-cpp spdlog curl)

aux_source_directory(core SOURCE_FILE_LIST)
message(STATUS "source files: ${SOURCE_FILE_LIST}")
add_executable(${PROJECT_NAME} ${SOURCE_FILE_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp spdlog::spdlog cxxopts::cxxopts CURL::libcurl)

add_library(libsmartmha STATIC ${SOURCE_FILE_LIST} )
target_link_libraries(lib${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp spdlog::spdlog cxxopts::cxxopts CURL::libcurl)

install(TARGETS libsmartmha DESTINATION ${SMARTMHA_INSTALL_LIB_DIR})

set(BUILD_TESTS ON)

if (BUILD_TESTS)
    message("BUILD_TESTS: ON")
    add_subdirectory(test)
endif ()