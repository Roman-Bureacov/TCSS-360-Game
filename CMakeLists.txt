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
        src/app/control/ObserverPattern.cpp
        src/app/control/control.cpp
        src/app/model/model.cpp
        src/app/view/view.cpp
        src/include/Clock.h
        src/eng/Clock.cpp
        src/include/AbstractCharacter.h
        src/include/Hitbox.h
        src/app/model/Characters/AbstractCharacter.cpp
        src/include/Bitz.h
        src/eng/Bitz.cpp
        src/include/Event.h
        src/app/model/Characters/Dummy.h
        src/app/model/Hitbox.cpp
)

# static libraries, primarily for testing purposes
add_library(engine STATIC
        src/eng/Bitz.cpp
        src/eng/Clock.cpp
)

add_library(model STATIC
        src/app/model/Characters/AbstractCharacter.cpp
        src/app/model/Characters/Dummy.h
        src/app/model/Hitbox.cpp
)

target_include_directories(engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link against SDL3
target_link_libraries(TCSS-360-Game SDL3)

# Copy SDL3.dll to the executable output directory
add_custom_command(TARGET TCSS-360-Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:TCSS-360-Game>)

add_subdirectory(Google_tests)