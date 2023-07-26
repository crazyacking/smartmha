set(module smartmha)
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)

message("===> BUILD TEST")
set(PROJECT_TEST_BINARY_DIR .)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TEST_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/module)

file(GLOB_RECURSE TEST_FILE_LIST *.cpp)
foreach (test_file ${TEST_FILE_LIST})
    string(REGEX REPLACE "(^.*/|.cpp$)" "" exe ${test_file})
    message("add_executable: ${exe} ${test_file}")
    add_executable(${exe} ${test_file})
#    target_link_libraries(${exe} libsmartmha)
    install(TARGETS ${exe} RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT runtime)
endforeach (test_file)