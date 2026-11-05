/**
 * Math System Tests
 */

#include "math/Transform.h"
#include "math/Geometry.h"
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
#define ASSERT_EQ(a, b) if ((a) != (b)) return false

TEST(TransformIdentity) {
    bf::math::Transform transform;
    glm::mat4 matrix = transform.GetMatrix();
    
    // Check that identity transform produces identity matrix
    ASSERT(matrix == glm::mat4(1.0f));
    
    return true;
}

TEST(TransformTranslation) {
    bf::math::Transform transform;
    transform.SetPosition(glm::vec3(10.0f, 20.0f, 30.0f));
    
    glm::vec3 pos = transform.GetPosition();
    ASSERT(pos.x == 10.0f && pos.y == 20.0f && pos.z == 30.0f);
    
    return true;
}

TEST(AABBIntersection) {
    bf::math::AABB box1(glm::vec3(0.0f), glm::vec3(10.0f));
    bf::math::AABB box2(glm::vec3(5.0f), glm::vec3(15.0f));
    bf::math::AABB box3(glm::vec3(20.0f), glm::vec3(30.0f));
    
    ASSERT(box1.Intersects(box2));
    ASSERT(!box1.Intersects(box3));
    
    return true;
}

TEST(AABBContains) {
    bf::math::AABB box(glm::vec3(0.0f), glm::vec3(10.0f));
    
    ASSERT(box.Contains(glm::vec3(5.0f, 5.0f, 5.0f)));
    ASSERT(!box.Contains(glm::vec3(15.0f, 5.0f, 5.0f)));
    
    return true;
}

TEST(BoundingSphereIntersection) {
    bf::math::BoundingSphere sphere1(glm::vec3(0.0f), 5.0f);
    bf::math::BoundingSphere sphere2(glm::vec3(8.0f, 0.0f, 0.0f), 5.0f);
    bf::math::BoundingSphere sphere3(glm::vec3(20.0f, 0.0f, 0.0f), 5.0f);
    
    ASSERT(sphere1.Intersects(sphere2));
    ASSERT(!sphere1.Intersects(sphere3));
    
    return true;
}
