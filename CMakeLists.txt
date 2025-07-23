cmake_minimum_required(VERSION 3.31)
project(TCSS-360-Game)

set(CMAKE_CXX_STANDARD 23)

# path to SDL3
set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/SDL3-3.2.16")

# Add include directory
include_directories("${SDL3_ROOT}/include")

# Add include directory for our files
include_directories("${CMAKE_SOURCE_DIR}/include")

# Link directory
link_directories("${SDL3_ROOT}/lib/x64")

# Add source file
add_executable(TCSS-360-Game src/main.cpp
        src/app/model/Characters/AbstractCharacter.cpp
        src/include/AbstractCharacter.h
        src/include/Utils.h
        src/app/model/Characters/Weapons/Hitbox.cpp
        src/include/Hitbox.h
)

# Link against SDL3
target_link_libraries(TCSS-360-Game SDL3)

# Copy SDL3.dll to the executable output directory
add_custom_command(TARGET TCSS-360-Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:TCSS-360-Game>)
