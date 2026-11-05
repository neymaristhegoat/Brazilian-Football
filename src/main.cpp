/**
 * Brazilian Football
 * Main Entry Point with Demo Scene
 */

#include "core/Application.h"
#include "core/Window.h"
#include "core/Logger.h"
#include "renderer/Renderer.h"
#include "demo/DemoScene.h"
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) {
    try {
        bf::core::Logger::Init();
        BF_LOG_INFO("===========================================");
        BF_LOG_INFO("   Brazilian Football - Graphics Demo");
        BF_LOG_INFO("===========================================");
        
        bf::core::Application app;
        if (!app.Initialize(argc, argv)) {
            BF_LOG_ERROR("Failed to initialize application");
            return 1;
        }
        
        // Create demo scene
        bf::demo::DemoScene demoScene;
        if (!demoScene.Initialize()) {
            BF_LOG_ERROR("Failed to initialize demo scene");
            return 1;
        }
        
        BF_LOG_INFO("Starting render loop...");
        BF_LOG_INFO("Press ESC to exit");
        
        // Custom render loop with demo scene
        auto lastTime = std::chrono::high_resolution_clock::now();
        
        while (!app.GetWindow()->ShouldClose()) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> deltaTime = currentTime - lastTime;
            lastTime = currentTime;
            
            // Process input
            app.GetWindow()->PollEvents();
            
            // Update demo scene
            demoScene.Update(deltaTime.count());
            
            // Render
            app.GetRenderer()->Clear(0.1f, 0.1f, 0.15f, 1.0f);
            app.GetRenderer()->BeginFrame();
            
            demoScene.Render(app.GetRenderer());
            
            app.GetRenderer()->EndFrame();
            app.GetWindow()->SwapBuffers();
        }
        
        BF_LOG_INFO("Exiting...");
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}
