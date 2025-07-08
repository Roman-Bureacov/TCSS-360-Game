cmake_minimum_required(VERSION 3.31)
project(TCSS-360-Game)

set(CMAKE_CXX_STANDARD 23)

# path to SDL3
set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/SDL3-3.2.16")

# Add include directory
include_directories("${SDL3_ROOT}/include")

# Link directory
link_directories("${SDL3_ROOT}/lib/x64")

# Add source file
add_executable(TCSS-360-Game src/main.cpp
)

# Link against SDL3
target_link_libraries(TCSS-360-Game SDL3)
