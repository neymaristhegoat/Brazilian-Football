/**
 * Player System Tests
 */

#include "gameplay/Player.h"

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

TEST(PlayerCreation) {
    bf::game::Player player;
    player.SetName("Test Player");
    
    ASSERT(player.GetName() == "Test Player");
    ASSERT(player.GetStats().stamina == 100.0f);
    
    return true;
}

TEST(PlayerMovement) {
    bf::game::Player player;
    glm::vec3 direction(1.0f, 0.0f, 0.0f);
    
    player.Move(direction);
    ASSERT(player.GetState() == bf::game::PlayerState::Running);
    
    return true;
}

TEST(PlayerStamina) {
    bf::game::Player player;
    player.Sprint(true);
    
    float initialStamina = player.GetStats().stamina;
    player.Update(1.0f); // 1 second
    
    // Stamina should decrease when sprinting
    // Note: This test requires access to current stamina, might need getter
    
    return true;
}
