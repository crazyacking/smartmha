set(module smartmha)



add_subdirectory(base)
add_subdirectory(raft)
add_subdirectory(common)

#message(STATUS "==> Lib ${module}")
#aux_source_directory(. SOURCE_FILE_LIST)
#message(STATUS "source files: ${SOURCE_FILE_LIST}")
#add_executable(${PROJECT_NAME} ${SOURCE_FILE_LIST})
#target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp spdlog::spdlog cxxopts::cxxopts CURL::libcurl)

#add_library(lib${module} STATIC ${SOURCE_FILE_LIST})


#install(TARGETS lib${module} DESTINATION ${SMARTMHA_INSTALL_LIB_DIR})