set(module test_smartmha)

option(BUILD_TESTS "build tests" ON)
set(BUILD_TESTS ON)

message("-- BUILD_TESTS: ${BUILD_TESTS}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}   -fstack-protector-all")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector-all")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)

if (BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    file(GLOB TEST_FILES tests/*.cpp)
    foreach (TEST_FILE ${TEST_FILES})
        get_filename_component(TEST_NAME ${TEST_FILE} NAME_WLE)
        add_executable(${TEST_NAME} ${TEST_FILE})
        target_link_libraries(${TEST_NAME}
                gtest_main
                ${PROJECT_NAME}::base
                ${PROJECT_NAME}::raft
                ${PROJECT_NAME}::common
                ${PROJECT_NAME}::http
        )
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endforeach ()
endif ()