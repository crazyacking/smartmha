
add_library(raft INTERFACE)
add_library(raft::raft ALIAS raft)

aux_source_directory(. SOURCE_FILE_LIST)
message(STATUS "source files: ${SOURCE_FILE_LIST}")