#include "core/Window.h"
#include "core/Logger.h"

namespace bf {
namespace core {

Window::Window()
    : m_NativeWindow(nullptr)
    , m_Width(0)
    , m_Height(0)
    , m_ShouldClose(false)
{
}

Window::~Window() {
    Destroy();
}

bool Window::Create(const std::string& title, uint32_t width, uint32_t height) {
    m_Title = title;
    m_Width = width;
    m_Height = height;

    // TODO: Implement platform-specific window creation (GLFW/SDL)
    BF_LOG_INFO("Creating window: {} ({}x{})", title, width, height);
    
    return true;
}

void Window::Destroy() {
    if (m_NativeWindow) {
        BF_LOG_INFO("Destroying window");
        // TODO: Cleanup platform window
        m_NativeWindow = nullptr;
    }
}

void Window::PollEvents() {
    // TODO: Platform event polling
}

void Window::SwapBuffers() {
    // TODO: Platform buffer swap
}

bool Window::ShouldClose() const {
    return m_ShouldClose;
}

void Window::SetShouldClose(bool value) {
    m_ShouldClose = value;
}

float Window::GetAspectRatio() const {
    return static_cast<float>(m_Width) / static_cast<float>(m_Height);
}

} // namespace core
} // namespace bf
