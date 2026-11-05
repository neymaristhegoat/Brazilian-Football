/**
 * Test Main Entry Point
 * Simple test framework for Brazilian Football
 */

#include <iostream>
#include <vector>
#include <string>
#include <functional>

struct TestCase {
    std::string name;
    std::function<bool()> func;
};

std::vector<TestCase> g_Tests;

#define TEST(name) \
    bool Test_##name(); \
    static bool Register_##name = []() { \
        g_Tests.push_back({#name, Test_##name}); \
        return true; \
    }(); \
    bool Test_##name()

#define ASSERT(condition) \
    if (!(condition)) { \
        std::cerr << "  FAILED: " << #condition << " at line " << __LINE__ << std::endl; \
        return false; \
    }

#define ASSERT_EQ(a, b) \
    if ((a) != (b)) { \
        std::cerr << "  FAILED: " << #a << " != " << #b << " at line " << __LINE__ << std::endl; \
        return false; \
    }

int main(int argc, char* argv[]) {
    std::cout << "Running Brazilian Football Tests..." << std::endl;
    std::cout << "===================================" << std::endl;

    int passed = 0;
    int failed = 0;

    for (const auto& test : g_Tests) {
        std::cout << "\nRunning test: " << test.name << std::endl;
        
        try {
            if (test.func()) {
                std::cout << "  PASSED" << std::endl;
                passed++;
            } else {
                failed++;
            }
        } catch (const std::exception& e) {
            std::cerr << "  EXCEPTION: " << e.what() << std::endl;
            failed++;
        }
    }

    std::cout << "\n===================================" << std::endl;
    std::cout << "Results: " << passed << " passed, " << failed << " failed" << std::endl;

    return failed > 0 ? 1 : 0;
}
