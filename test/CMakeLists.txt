set(module test_smartmha)

option(BUILD_TESTS "build tests" ON)
set(BUILD_TESTS ON)

message("-- BUILD_TESTS: ${BUILD_TESTS}")
if (NOT BUILD_TESTS)
    return()
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}   -fstack-protector-all")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector-all")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(
        ${PROJECT_SOURCE_DIR}/modules/base/include
        ${PROJECT_SOURCE_DIR}/modules/raft/include
        ${PROJECT_SOURCE_DIR}/modules/common/include
)

file(GLOB TEST_FILES *.cpp)
foreach (TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WLE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME}
            gtest_main
            ${PROJECT_NAME}::base
            ${PROJECT_NAME}::raft
            ${PROJECT_NAME}::common
    )
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach ()