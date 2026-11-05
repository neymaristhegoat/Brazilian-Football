/**
 * Scene System Tests
 */

#include "scene/Scene.h"
#include "scene/Entity.h"

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

TEST(SceneCreation) {
    bf::scene::Scene scene("TestScene");
    ASSERT(scene.GetName() == "TestScene");
    return true;
}

TEST(EntityCreation) {
    bf::scene::Scene scene("TestScene");
    auto* entity = scene.CreateEntity("TestEntity");
    
    ASSERT(entity != nullptr);
    ASSERT(entity->GetName() == "TestEntity");
    ASSERT(entity->GetScene() == &scene);
    
    return true;
}

TEST(FindEntityByName) {
    bf::scene::Scene scene("TestScene");
    scene.CreateEntity("Entity1");
    scene.CreateEntity("Entity2");
    
    auto* found = scene.FindEntityByName("Entity1");
    ASSERT(found != nullptr);
    ASSERT(found->GetName() == "Entity1");
    
    return true;
}
