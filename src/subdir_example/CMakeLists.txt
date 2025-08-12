cmake_minimum_required(VERSION 4.1.0)

file(GLOB MYLIB_SOURCES "*.cpp")
add_library(subdir_example OBJECT ${MYLIB_SOURCES})
target_include_directories(subdir_example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
