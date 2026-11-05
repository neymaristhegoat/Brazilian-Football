cmake_minimum_required(VERSION 3.20)
project(BrazilianFootball VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /WX-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Options
option(BUILD_TESTS "Build test suite" ON)
option(BUILD_TOOLS "Build development tools" ON)
option(BUILD_LAUNCHER "Build game launcher" ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/engine/src
    ${CMAKE_SOURCE_DIR}/game/src
    ${CMAKE_SOURCE_DIR}/external/include
)

# Add subdirectories
add_subdirectory(engine)
add_subdirectory(game)

if(BUILD_TOOLS)
    add_subdirectory(tools)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Main executable
add_executable(BrazilianFootball
    src/main.cpp
)

target_link_libraries(BrazilianFootball
    PRIVATE
    BFEngine
    BFGame
)

# Install targets
install(TARGETS BrazilianFootball
    RUNTIME DESTINATION bin
)
