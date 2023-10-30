cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(smartmha VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ARG_DOWNLOAD_EXTRACT_TIMESTAMP TRUE)

execute_process(COMMAND hostname OUTPUT_VARIABLE HOSTNAME OUTPUT_STRIP_TRAILING_WHITESPACE)
message("-- Hostname: ${HOSTNAME}")
message("-- System arch: ${CMAKE_SYSTEM_PROCESSOR}")
message("-- Output path: ${PROJECT_OUTPUT_DIR}")

add_subdirectory(modules)
add_subdirectory(test)