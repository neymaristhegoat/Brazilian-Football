cmake_minimum_required(VERSION 3.20)

# Try to find OpenGL
find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
    message(STATUS "Found OpenGL: ${OPENGL_LIBRARIES}")
endif()

# Try different methods to find GLFW
find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(GLFW QUIET glfw3)
        if(GLFW_FOUND)
            message(STATUS "Found GLFW via pkg-config")
            set(GLFW_LIBRARIES ${GLFW_LIBRARIES})
            set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIRS})
        endif()
    endif()
endif()

# Try to find GLEW
find_package(GLEW QUIET)
if(NOT GLEW_FOUND)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(GLEW QUIET glew)
        if(GLEW_FOUND)
            message(STATUS "Found GLEW via pkg-config")
        endif()
    endif()
endif()

# Try to find GLM
find_package(glm QUIET)
if(NOT glm_FOUND)
    # GLM is header-only, try to find it manually
    find_path(GLM_INCLUDE_DIR glm/glm.hpp
        PATHS
        /usr/include
        /usr/local/include
        ${CMAKE_SOURCE_DIR}/external/include
    )
    if(GLM_INCLUDE_DIR)
        message(STATUS "Found GLM: ${GLM_INCLUDE_DIR}")
        set(GLM_FOUND TRUE)
    endif()
endif()

# Check if we have all required libraries
if(NOT GLFW_FOUND AND NOT glfw3_FOUND)
    message(FATAL_ERROR "GLFW not found. Please install libglfw3-dev:\n  sudo apt-get install libglfw3-dev")
endif()

if(NOT GLEW_FOUND)
    message(FATAL_ERROR "GLEW not found. Please install libglew-dev:\n  sudo apt-get install libglew-dev")
endif()

if(NOT GLM_FOUND AND NOT glm_FOUND)
    message(FATAL_ERROR "GLM not found. Please install libglm-dev:\n  sudo apt-get install libglm-dev")
endif()

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
    src/renderer/Lighting.cpp
    src/renderer/Framebuffer.cpp
    src/renderer/Buffer.cpp
    src/renderer/RenderCommand.cpp
    src/renderer/RenderPipeline.cpp
    
    # Demo
    src/demo/DemoScene.cpp
    
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
    ${OPENGL_INCLUDE_DIR}
)

# Add GLFW include directories
if(glfw3_FOUND)
    target_include_directories(BFEngine PUBLIC ${glfw3_INCLUDE_DIRS})
elseif(GLFW_FOUND)
    target_include_directories(BFEngine PUBLIC ${GLFW_INCLUDE_DIRS})
endif()

# Add GLEW include directories
if(GLEW_FOUND)
    target_include_directories(BFEngine PUBLIC ${GLEW_INCLUDE_DIRS})
endif()

# Add GLM include directories
if(glm_FOUND)
    target_include_directories(BFEngine PUBLIC ${glm_INCLUDE_DIRS})
elseif(GLM_FOUND)
    target_include_directories(BFEngine PUBLIC ${GLM_INCLUDE_DIR})
endif()

# Link libraries
target_link_libraries(BFEngine
    PUBLIC
    ${OPENGL_LIBRARIES}
)

# Link GLFW
if(glfw3_FOUND)
    target_link_libraries(BFEngine PUBLIC glfw)
elseif(GLFW_FOUND)
    target_link_libraries(BFEngine PUBLIC ${GLFW_LIBRARIES})
endif()

# Link GLEW
if(TARGET GLEW::GLEW)
    target_link_libraries(BFEngine PUBLIC GLEW::GLEW)
elseif(GLEW_FOUND)
    target_link_libraries(BFEngine PUBLIC ${GLEW_LIBRARIES})
endif()

# Platform-specific libraries
if(UNIX AND NOT APPLE)
    target_link_libraries(BFEngine PUBLIC dl pthread X11 m)
elseif(APPLE)
    target_link_libraries(BFEngine PUBLIC "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()

message(STATUS "BFEngine configured successfully")
