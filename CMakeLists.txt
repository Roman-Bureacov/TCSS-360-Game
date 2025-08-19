cmake_minimum_required(VERSION 3.31)
project(TCSS-360-Game)

set(CMAKE_CXX_STANDARD 23)

# path to SDL3
set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/SDL3-3.2.16")
set(SQLITE_ROOT "${CMAKE_SOURCE_DIR}/sqlite")

# Add include directories for SLD and SQLite
include_directories("${SDL3_ROOT}/include")
include_directories("${SQLITE_ROOT}/include")

# Add include directory for our project files
include_directories("${CMAKE_SOURCE_DIR}/include")

# Link SDL3 directory
link_directories("${SDL3_ROOT}/lib/x64")

# Add source files
add_executable(TCSS-360-Game
        src/main.cpp
        src/app/model/Characters/AbstractCharacter.cpp
        src/app/model/Hitbox.cpp
        src/app/model/Characters/Weapons/Weapon.cpp
        src/app/model/ObserverPattern.cpp
        src/app/model/Enviroment/Dungeon.cpp
        src/app/model/Enviroment/Room.cpp
        src/app/model/Enviroment/Interactable.cpp
        src/db/DatabaseManager.cpp
        ${SQLITE_ROOT}/lib/sqlite3.c
        src/app/model/Characters/Player.cpp
        src/app/model/Characters/NPC.cpp
        src/eng/Bitz.cpp
        src/eng/Clock.cpp
        src/app/view/View.cpp
        src/app/view/GUINOW.cpp
        src/include/GUINOW.h

)

# static libraries, primarily for testing purposes
add_library(engine STATIC
        src/eng/Bitz.cpp
        src/eng/Clock.cpp
)

add_library(model STATIC
        src/include/Utils.h
        src/app/model/Characters/AbstractCharacter.cpp
        src/app/model/Characters/Dummy.h # header-only implementation
        src/app/model/Hitbox.cpp
        src/app/model/Characters/Weapons/Weapon.cpp
        src/include/Weapon.h
        src/app/model/ObserverPattern.cpp
        src/app/model/Enviroment/Dungeon.cpp
        src/app/model/Enviroment/Room.cpp
        src/app/model/Enviroment/Interactable.cpp
        src/db/DatabaseManager.cpp
        ${SQLITE_ROOT}/lib/sqlite3.c
        src/app/model/Characters/Player.cpp
        src/app/model/Characters/NPC.cpp
        src/include/Player.h


)

target_include_directories(model PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SQLITE_ROOT}/include
        ${SDL3_ROOT}/include
)


target_include_directories(engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        src/db/sqlite_test.cpp
        "${SQLITE_ROOT}/lib/sqlite3.c"
        src/app/model/Enviroment/Dungeon.cpp
        src/include/Dungeon.h
        src/app/model/Enviroment/Room.cpp
        src/include/Room.h
        src/include/DungeonTextures.h
        src/db/DatabaseManager.cpp
        src/include/DatabaseManager.h
        src/app/model/ObserverPattern.cpp
        src/test/TestMain.cpp
)

# adds tests to their own separate ecosystem.
# the tests have their own main so they need to be in,
# a different place.
add_executable(TCSS-360-Tests
        src/app/model/Enviroment/Dungeon.cpp
        src/app/model/Enviroment/Room.cpp
        src/db/DatabaseManager.cpp
        src/app/model/ObserverPattern.cpp
        src/test/TestMain.cpp
        "${SQLITE_ROOT}/lib/sqlite3.c"
        src/test/TestEnviroment/TestRoom.cpp
        src/test/TestEnviroment/TestDungeon.cpp
        src/eng/Bitz.cpp
        src/eng/Clock.cpp
)

#Adds the test ecosystem
target_include_directories(TCSS-360-Tests PRIVATE src/include)

# Link against SDL3
target_link_libraries(TCSS-360-Game SDL3)

# Copy SDL3.dll to the executable output directory
add_custom_command(TARGET TCSS-360-Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:TCSS-360-Game>)

#Include Path to Shaders
add_custom_command(TARGET TCSS-360-Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/shaders"
        $<TARGET_FILE_DIR:TCSS-360-Game>/shaders)

# Copy PNG assets into the build output directory
add_custom_command(TARGET TCSS-360-Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/assets"
        $<TARGET_FILE_DIR:TCSS-360-Game>/assets
)


add_subdirectory(Google_tests)