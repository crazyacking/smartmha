set(module smartmha)
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
message("================ 3")
#set(PROJECT_TEST_BINARY_DIR .)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TEST_BINARY_DIR})
set(CMAKE_CXX_STANDARD 14)
add_executable(test_utils test_utils.cpp)

#file(GLOB_RECURSE SRCS *.cpp)
#foreach (src ${SRCS})
#    message("================ 4")
#    message(${src})
#    string(
#            REGEX
#            REPLACE "(^.*/|.cpp$)"
#            ""
#            exe
#            ${src})
#    message("add_executable: " " " ${exe} " " ${src})
#    add_executable(${exe} ${src})
#    target_link_libraries(
#            ${exe}
#            PRIVATE ${ZLIB_LIBRARIES}
#            -Wl,${LINK_OPTION_WHOLE_ARCHIVE}
#            ${MDK_MODULES}
#            ${LINK_OPTION_NO_WHOLE_ARCHIVE}
#            ${CONAN_LIBS})
#    target_include_directories(${exe} PUBLIC ${INCS} ${PROJECT_BINARY_DIR}/include ${CONAN_INCLUDE_DIRS})
#    install(TARGETS ${exe} RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT runtime)
#endforeach (src)