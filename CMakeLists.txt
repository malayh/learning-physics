cmake_minimum_required(VERSION 4.1.0)
project(phy)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(glfw3 REQUIRED)

#
# subdires here
#
add_subdirectory(src/graphics)


#
# Build the main executables
#
add_executable(main ./src/main.cpp)
target_link_libraries(main PRIVATE graphics)
target_link_libraries(main PRIVATE glfw)