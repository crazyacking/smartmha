aux_source_directory(. SOURCE_FILE_LIST)
message(STATUS "source files: ${SOURCE_FILE_LIST}")
add_library(libraft STATIC ${SOURCE_FILE_LIST})