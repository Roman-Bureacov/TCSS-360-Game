project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${SDL3_ROOT}/include)
link_directories(${SDL3_ROOT}/lib/x64)

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
)

add_custom_command(TARGET Google_Tests_run POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_ROOT}/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:Google_Tests_run>
)
