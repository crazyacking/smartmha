include(FetchContent)
FetchContent_Declare(cxxopts URL https://github.com/jarro2783/cxxopts/archive/refs/tags/v3.0.0.tar.gz)
FetchContent_Declare(yaml-cpp URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.tar.gz)
FetchContent_Declare(spdlog URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.tar.gz)
FetchContent_Declare(curl URL https://github.com/curl/curl/archive/refs/tags/curl-7_79_1.tar.gz)
FetchContent_MakeAvailable(cxxopts yaml-cpp spdlog curl)

add_subdirectory(raft)
add_subdirectory(base)

aux_source_directory(. SOURCE_FILE_LIST)
message(STATUS "source files: ${SOURCE_FILE_LIST}")
add_executable(${PROJECT_NAME} ${SOURCE_FILE_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp spdlog::spdlog cxxopts::cxxopts CURL::libcurl)

add_library(libsmartmha STATIC ${SOURCE_FILE_LIST})
target_link_libraries(lib${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp spdlog::spdlog cxxopts::cxxopts CURL::libcurl)

install(TARGETS libsmartmha DESTINATION ${SMARTMHA_INSTALL_LIB_DIR})