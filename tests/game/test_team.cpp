/**
 * Team System Tests
 */

#include "gameplay/Team.h"
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

TEST(TeamCreation) {
    bf::game::Team team("Test Team");
    ASSERT(team.GetName() == "Test Team");
    return true;
}

TEST(TeamAddPlayer) {
    bf::game::Team team("Test Team");
    auto player = std::make_shared<bf::game::Player>();
    player->SetName("Player 1");
    
    team.AddPlayer(player);
    ASSERT(team.GetPlayers().size() == 1);
    
    return true;
}

TEST(TeamFormation) {
    bf::game::Team team("Test Team");
    team.SetFormation(bf::game::Formation::F_4_3_3);
    
    ASSERT(team.GetFormation() == bf::game::Formation::F_4_3_3);
    
    return true;
}
