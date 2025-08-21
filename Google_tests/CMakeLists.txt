project(Google_tests)
add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${SDL3_ROOT}/include)
link_directories(${SDL3_ROOT}/lib/x64)

include_directories(${SDL3_IMG_ROOT}/x86_64-w64-mingw32/include)
link_directories(${SDL3_IMG_ROOT}/x86_64-w64-mingw32/lib)

# adding the Google_Tests_run target
add_executable(
        Google_Tests_run
        EngineTest.cpp
        HitboxTest.cpp
        CharacterAttackTest.cpp
        CharacterObserverTest.cpp
        ObserverTest.cpp
        ../src/app/model/Characters/NPC.cpp
        ../src/include/NPC.h
        DungeonRoomTest.cpp
        NPCTest.cpp
        PlayerTest.cpp
        EngineMovementTest.cpp


)

target_link_libraries(
        Google_Tests_run
        engine
        model
        gtest
        gtest_main
        SDL3
        SDL3_image
)

add_custom_command(TARGET Google_Tests_run POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:Google_Tests_run>



)

# Copy SDL3_image.dll to the executable output directory
add_custom_command(TARGET Google_Tests_run POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_IMG_ROOT}/x86_64-w64-mingw32/bin/SDL3_image.dll"
        $<TARGET_FILE_DIR:Google_Tests_run>)
