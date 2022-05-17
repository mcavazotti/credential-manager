cmake_minimum_required(VERSION 3.10)


include(sourceList.cmake)

include_directories(${CMAKE_SOURCE_DIR}/third_party/SQLiteCpp/include)

add_library(CredentialManagementLib ${SOURCE_LIST})
target_include_directories(CredentialManagementLib PUBLIC   ${CMAKE_SOURCE_DIR}/credential_management_lib/include
                                                             ${CMAKE_SOURCE_DIR}/third_party)
