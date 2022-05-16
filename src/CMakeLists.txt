cmake_minimum_required(VERSION 3.10)

include(sourceList.cmake)

add_executable(${PROJECT_NAME} ${SOURCE_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC  ${CMAKE_SOURCE_DIR}/credential_management_lib/include
                                            ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE CredentialManagementLib)