cmake_minimum_required(VERSION 3.31)
project(TCSS-360-Game)

set(CMAKE_CXX_STANDARD 23)

# path to SDL3
set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/SDL3-3.2.16")
set(SQLITE_ROOT "${CMAKE_SOURCE_DIR}/sqlite")

# Add include directory
include_directories("${SDL3_ROOT}/include")
include_directories("${SQLITE_ROOT}/include")

# Link directory
link_directories("${SDL3_ROOT}/lib/x64")

# Add source file
add_executable(TCSS-360-Game
        src/main.cpp
        src/db/sqlite_test.cpp
        ${SQLITE_ROOT}/lib/sqlite3.c
)

# Link against SDL3 & SQLite
target_link_libraries(TCSS-360-Game SDL3)

# Copy SDL3.dll to the executable output directory
add_custom_command(TARGET TCSS-360-Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:TCSS-360-Game>)

