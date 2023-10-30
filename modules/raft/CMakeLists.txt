set(module raft)

message(STATUS "==> Lib ${module}")

file(GLOB_RECURSE headers include/mha/*.h)
file(GLOB_RECURSE sources src/*.cpp)

message(STATUS "header files: ${headers}")
message(STATUS "source files: ${sources}")

add_library(${module} ${headers} ${sources})
add_library(${META_PROJECT_NAME}::${module} ALIAS ${module})