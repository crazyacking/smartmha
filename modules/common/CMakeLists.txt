set(module common)

message(STATUS "==> Lib ${module}")

include(FetchContent)
FetchContent_Declare(cxxopts URL https://github.com/jarro2783/cxxopts/archive/refs/tags/v3.1.1.tar.gz)
FetchContent_Declare(yaml-cpp URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/0.8.0.tar.gz)
FetchContent_Declare(spdlog URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz)
FetchContent_MakeAvailable(cxxopts yaml-cpp spdlog)

file(GLOB_RECURSE headers include/mha/*.h)
file(GLOB_RECURSE sources src/*.cpp)

message(STATUS "header files: ${headers}")
message(STATUS "source files: ${sources}")

include_directories(include)

add_library(${module} ${headers} ${sources})
add_library(${PROJECT_NAME}::${module} ALIAS ${module})

target_include_directories(${module} INTERFACE
        include
        yaml-cpp::yaml-cpp
        spdlog::spdlog
        cxxopts::cxxopts
        ${PROJECT_NAME}::base
        ${PROJECT_NAME}::raft
)

target_link_libraries(${module} PUBLIC
        yaml-cpp::yaml-cpp
        spdlog::spdlog
        cxxopts::cxxopts
        ${PROJECT_NAME}::base
        ${PROJECT_NAME}::raft
)