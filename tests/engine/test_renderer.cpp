/**
 * Renderer System Tests
 */

#include "renderer/Camera.h"
#include <glm/glm.hpp>

extern struct TestCase;
extern std::vector<TestCase> g_Tests;

#define TEST(name) bool Test_##name(); \
    static bool Register_##name = []() { \
        extern std::vector<TestCase> g_Tests; \
        g_Tests.push_back({#name, Test_##name}); \
        return true; \
    }(); \
    bool Test_##name()

#define ASSERT(condition) if (!(condition)) return false

TEST(CameraInitialization) {
    bf::renderer::Camera camera;
    
    // Check default values
    ASSERT(camera.GetFOV() == 45.0f);
    ASSERT(camera.GetNearPlane() == 0.1f);
    ASSERT(camera.GetFarPlane() == 1000.0f);
    
    return true;
}

TEST(CameraSetPosition) {
    bf::renderer::Camera camera;
    camera.SetPosition(glm::vec3(10.0f, 5.0f, 0.0f));
    
    glm::vec3 pos = camera.GetPosition();
    ASSERT(pos.x == 10.0f && pos.y == 5.0f && pos.z == 0.0f);
    
    return true;
}

TEST(CameraPerspective) {
    bf::renderer::Camera camera;
    camera.SetPerspective(60.0f, 16.0f/9.0f, 0.1f, 100.0f);
    
    ASSERT(camera.GetFOV() == 60.0f);
    ASSERT(camera.GetAspectRatio() == 16.0f/9.0f);
    
    return true;
}
