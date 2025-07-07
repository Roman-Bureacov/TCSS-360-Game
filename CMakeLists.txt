cmake_minimum_required(VERSION 3.15)
project(TCSS-360-Game)

set(CMAKE_CXX_STANDARD 20)

# Set SDL3 root path
set(SDL3_DIR "SDL3-3.2.16/cmake")

# Find SDL3 using CMake's config
find_package(SDL3 REQUIRED CONFIG)

add_executable(TCSS-360-Game main.cpp)

# Link SDL3
target_link_libraries(TCSS-360-Game SDL3::SDL3)