set(module base)

message(STATUS "Lib ${module}")

# sources
set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/src")

aux_source_directory(src SOURCE_FILE_LIST)
message(STATUS "source files: ${SOURCE_FILE_LIST}")

file(GLOB HEADER_FILES "include/*.h")
message(STATUS "header files: ${HEADER_FILES}")

# create library
add_library(${module} ${HEADER_FILES} ${SOURCE_FILE_LIST})