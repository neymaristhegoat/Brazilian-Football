cmake_minimum_required(VERSION 3.20)

# Game library
set(GAME_SOURCES
    src/BrazilianFootballGame.cpp
    
    # Gameplay
    src/gameplay/GameState.cpp
    src/gameplay/Player.cpp
    src/gameplay/Team.cpp
    src/gameplay/Match.cpp
    
    # AI
    src/ai/AIController.cpp
    
    # UI
    src/ui/GameUI.cpp
    
    # Story Mode
    src/story/StoryManager.cpp
    
    # Multiplayer
    src/multiplayer/MultiplayerManager.cpp
)

add_library(BFGame STATIC ${GAME_SOURCES})

target_include_directories(BFGame
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    PRIVATE
    ${CMAKE_SOURCE_DIR}/engine/src
)

target_link_libraries(BFGame
    PUBLIC
    BFEngine
)
