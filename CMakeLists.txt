cmake_minimum_required(VERSION 3.10)

project(credential_manager)

include_directories(${CMAKE_SOURCE_DIR}/external)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(credential_management_lib)

