/**
 * Brazilian Football
 * Main Entry Point
 */

#include "core/Application.h"
#include "core/Logger.h"
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) {
    try {
        bf::core::Logger::Init();
        BF_LOG_INFO("Starting Brazilian Football...");
        
        bf::core::Application app;
        if (!app.Initialize(argc, argv)) {
            BF_LOG_ERROR("Failed to initialize application");
            return 1;
        }
        
        return app.Run();
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}
