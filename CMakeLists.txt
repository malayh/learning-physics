cmake_minimum_required(VERSION 4.1.0)
project(phy)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# subdires here
#
add_subdirectory(src/subdir_example)


#
# Build the main executables
#
add_executable(example ./src/example.cpp)
target_link_libraries(example PRIVATE subdir_example)

add_executable(main ./src/main.cpp)