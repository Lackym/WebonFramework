cmake_minimum_required(VERSION 3.17)

project(WebonFramework LANGUAGES CXX)

if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  message(FATAL_ERROR "BINARY_DIR and SOURCE_DIR should not be the same")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_library(common_options INTERFACE)

# Set the output folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/Install)

if(WIN32)
	target_compile_definitions(common_options INTERFACE _WIN32_WINNT=0x0601)
endif()

#load vendors
add_subdirectory(vendors)

add_subdirectory(Webon)
add_subdirectory(Sandbox)