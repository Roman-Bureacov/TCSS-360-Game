cmake_minimum_required(VERSION 3.15)
project(TCSS-360-Game)

set(CMAKE_CXX_STANDARD 20)

# Find SDL3 using CMake's config
option(MYGAME_VENDORED "Use vendored libraries" OFF)

if(MYGAME_VENDORED)
    # This assumes you have added SDL as a submodule in vendored/SDL
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
    # 1. Look for a SDL3 package,
    # 2. look for the SDL3-shared component, and
    # 3. fail if the shared component cannot be found.
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

add_executable(TCSS-360-Game src/main.cpp)

# Link SDL3
target_link_libraries(TCSS-360-Game SDL3::SDL3)