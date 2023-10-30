set(module test_smartmha)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-fPIC)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}   -fstack-protector-all")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector-all")

set(BUILD_TESTS ON)

message("-- BUILD_TESTS: ${BUILD_TESTS}")
if (NOT BUILD_TESTS)
    return()
endif ()

set(PROJECT_TEST_BINARY_DIR .)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TEST_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/modules)

file(GLOB_RECURSE TEST_FILE_LIST *.cpp)
foreach (test_file ${TEST_FILE_LIST})
    string(REGEX REPLACE "(^.*/|.cpp$)" "" exe ${test_file})
    message("add_executable: ${exe} ${test_file}")
    add_executable(${exe} ${test_file})
    target_link_libraries(${exe} libsmartmha)
    install(TARGETS ${exe} RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT runtime)
endforeach (test_file)