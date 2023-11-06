set(module http)

message(STATUS "==> Lib ${module}")

include(FetchContent)
FetchContent_Declare(curl URL https://github.com/curl/curl/archive/refs/tags/curl-8_4_0.tar.gz)
FetchContent_MakeAvailable(cxxopts yaml-cpp spdlog curl)

file(GLOB_RECURSE headers include/mha/*.h)
file(GLOB_RECURSE sources src/*.cpp)

message(STATUS "header files: ${headers}")
message(STATUS "source files: ${sources}")

include_directories(include)

add_library(${module} ${headers} ${sources})
add_library(${PROJECT_NAME}::${module} ALIAS ${module})

target_include_directories(${module} INTERFACE
        include
        CURL::libcurl
        ${PROJECT_NAME}::base
        ${PROJECT_NAME}::common
)

target_link_libraries(${module} PUBLIC
        CURL::libcurl
        ${PROJECT_NAME}::base
        ${PROJECT_NAME}::common
)