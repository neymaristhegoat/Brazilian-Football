cmake_minimum_required(VERSION 3.20)

# Test executable
enable_testing()

set(TEST_SOURCES
    test_main.cpp
    engine/test_math.cpp
    engine/test_renderer.cpp
    engine/test_scene.cpp
    game/test_player.cpp
    game/test_team.cpp
    game/test_match.cpp
)

add_executable(BFTests ${TEST_SOURCES})

target_link_libraries(BFTests
    PRIVATE
    BFEngine
    BFGame
)

target_include_directories(BFTests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/engine/src
    ${CMAKE_SOURCE_DIR}/game/src
)

# Register tests
add_test(NAME EngineTests COMMAND BFTests)
