cmake_minimum_required(VERSION 3.10)


include(sourceList.cmake)

add_library(CredentialManagementLib ${SOURCE_LIST})
target_include_directories(CredentialManagementLib PUBLIC   ${CMAKE_SOURCE_DIR}/credential_management_lib/include
                                                             ${CMAKE_SOURCE_DIR}/external)
