cmake_minimum_required(VERSION 4.1.0)

file(GLOB MYLIB_SOURCES "*.cpp")

add_library(graphics OBJECT ${MYLIB_SOURCES})
target_link_libraries(graphics PRIVATE glfw)

target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
