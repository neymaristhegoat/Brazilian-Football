cmake_minimum_required(VERSION 3.20)

# Engine library
set(ENGINE_SOURCES
    # Core
    src/core/Application.cpp
    src/core/Window.cpp
    src/core/Logger.cpp
    
    # Math
    src/math/Transform.cpp
    src/math/Geometry.cpp
    
    # Renderer
    src/renderer/Renderer.cpp
    src/renderer/Camera.cpp
    src/renderer/Mesh.cpp
    src/renderer/Shader.cpp
    src/renderer/Texture.cpp
    src/renderer/Material.cpp
    
    # Audio
    src/audio/AudioSystem.cpp
    
    # Input
    src/input/Input.cpp
    
    # Physics
    src/physics/PhysicsWorld.cpp
    
    # Network
    src/network/NetworkManager.cpp
    
    # Scene
    src/scene/Scene.cpp
    src/scene/Entity.cpp
    src/scene/components/TransformComponent.cpp
    
    # Resources
    src/resources/ResourceManager.cpp
)

add_library(BFEngine STATIC ${ENGINE_SOURCES})

target_include_directories(BFEngine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external/include
)

# Link external libraries (OpenGL, GLFW, etc)
# TODO: Add find_package() calls for dependencies
