cmake_minimum_required(VERSION 3.31)
project(TCSS-360-Game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add the std module
set(STD_MODULE "${CMAKE_SOURCE_DIR}/std")
set(STD_IFC "${STD_MODULE}/std.ifc")
set(STD_OBJ "${STD_MODULE}/std.obj")

# set up SDL3
set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/SDL3-3.2.16")
include_directories("${SDL3_ROOT}/include")
link_directories("${SDL3_ROOT}/lib/x64")

add_executable(TCSS-360-Game src/main.cpp)

target_compile_options(TCSS-360-Game PRIVATE /std:c++latest /experimental:module /reference "${STD_IFC}")
target_link_options(TCSS-360-Game PRIVATE "${STD_OBJ}")

# link SDL3 library
target_link_libraries(TCSS-360-Game SDL3)

# Copy SDL3.dll to the executable output directory
add_custom_command(TARGET TCSS-360-Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:TCSS-360-Game>)
