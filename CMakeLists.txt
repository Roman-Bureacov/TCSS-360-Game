cmake_minimum_required(VERSION 3.31)
project(TCSS-360-Game)

set(CMAKE_CXX_STANDARD 23)

# path to SDL3
set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/SDL3-3.2.16")
set(SQLITE_ROOT "${CMAKE_SOURCE_DIR}/sqlite")

# Add include directory
include_directories("${SDL3_ROOT}/include")
include_directories("${SQLITE_ROOT}/include")

# Add include directory for our files
include_directories("${CMAKE_SOURCE_DIR}/include")

# Link directory
link_directories("${SDL3_ROOT}/lib/x64")

# Add source files
add_executable(TCSS-360-Game src/main.cpp
        src/app/model/Characters/AbstractCharacter.cpp
        src/include/AbstractCharacter.h
        src/include/Utils.h
        src/app/model/Characters/Weapons/Hitbox.cpp
        src/include/Hitbox.h
        src/db/sqlite_test.cpp
        "${SQLITE_ROOT}/lib/sqlite3.c"
        src/app/model/Enviroment/Dungeon.cpp
        src/include/Dungeon.h
        src/app/model/Enviroment/Room.cpp
        src/include/Room.h
)

# Link against SDL3 & SQLite
target_link_libraries(TCSS-360-Game SDL3)

# Copy SDL3.dll to the executable output directory
add_custom_command(TARGET TCSS-360-Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:TCSS-360-Game>)

