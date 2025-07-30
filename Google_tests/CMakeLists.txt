project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(
        Google_Tests_run
        EngineTest.cpp
)

target_link_libraries(
        Google_Tests_run
        engine
        model
        gtest
        gtest_main
)