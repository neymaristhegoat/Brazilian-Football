/**
 * Match System Tests
 */

#include "gameplay/Match.h"
#include "gameplay/Team.h"

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

TEST(MatchCreation) {
    bf::game::Team homeTeam("Home Team");
    bf::game::Team awayTeam("Away Team");
    
    bf::game::Match match(&homeTeam, &awayTeam);
    
    ASSERT(match.GetHomeTeam() == &homeTeam);
    ASSERT(match.GetAwayTeam() == &awayTeam);
    ASSERT(match.GetHomeScore() == 0);
    ASSERT(match.GetAwayScore() == 0);
    
    return true;
}

TEST(MatchScoring) {
    bf::game::Team homeTeam("Home Team");
    bf::game::Team awayTeam("Away Team");
    
    bf::game::Match match(&homeTeam, &awayTeam);
    match.Initialize();
    
    match.ScoreGoal(&homeTeam);
    ASSERT(match.GetHomeScore() == 1);
    
    match.ScoreGoal(&awayTeam);
    ASSERT(match.GetAwayScore() == 1);
    
    return true;
}

TEST(BallPhysics) {
    bf::game::Ball ball;
    ball.Initialize();
    
    glm::vec3 initialPos = ball.GetPosition();
    ball.SetVelocity(glm::vec3(10.0f, 0.0f, 0.0f));
    
    ball.Update(1.0f);
    
    // Ball should have moved
    ASSERT(ball.GetPosition().x > initialPos.x);
    
    return true;
}
