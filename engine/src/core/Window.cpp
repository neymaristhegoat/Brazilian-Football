#include "core/Window.h"
#include "core/Logger.h"
#include <GLFW/glfw3.h>

namespace bf {
namespace core {

static void GLFWErrorCallback(int error, const char* description) {
    BF_LOG_ERROR("GLFW Error ({}): {}", error, description);
}

static void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // Note: Framebuffer callback - would normally update viewport
    // For now, dimensions are queried directly from GLFW when needed
    (void)window;
    (void)width;
    (void)height;
}

static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Input handling will be done through Input system
}

Window::Window()
    : m_NativeWindow(nullptr)
    , m_Title("Window")
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

    BF_LOG_INFO("Creating window: {} ({}x{})", title, width, height);
    
    // Initialize GLFW
    if (!glfwInit()) {
        BF_LOG_ERROR("Failed to initialize GLFW");
        return false;
    }

    glfwSetErrorCallback(GLFWErrorCallback);

    // OpenGL 4.1 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Window hints
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        BF_LOG_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return false;
    }

    m_NativeWindow = window;
    glfwSetWindowUserPointer(window, this);
    
    // Set callbacks
    glfwSetFramebufferSizeCallback(window, GLFWFramebufferSizeCallback);
    glfwSetKeyCallback(window, GLFWKeyCallback);

    // Make context current
    glfwMakeContextCurrent(window);
    
    // Enable VSync
    glfwSwapInterval(1);

    BF_LOG_INFO("Window created successfully");
    return true;
}

void Window::Destroy() {
    if (m_NativeWindow) {
        BF_LOG_INFO("Destroying window");
        GLFWwindow* window = static_cast<GLFWwindow*>(m_NativeWindow);
        glfwDestroyWindow(window);
        glfwTerminate();
        m_NativeWindow = nullptr;
    }
}

void Window::PollEvents() {
    glfwPollEvents();
    
    GLFWwindow* window = static_cast<GLFWwindow*>(m_NativeWindow);
    if (glfwWindowShouldClose(window)) {
        m_ShouldClose = true;
    }
}

void Window::SwapBuffers() {
    GLFWwindow* window = static_cast<GLFWwindow*>(m_NativeWindow);
    glfwSwapBuffers(window);
}

bool Window::ShouldClose() const {
    return m_ShouldClose;
}

void Window::SetShouldClose(bool value) {
    m_ShouldClose = value;
    if (m_NativeWindow) {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_NativeWindow);
        glfwSetWindowShouldClose(window, value ? GLFW_TRUE : GLFW_FALSE);
    }
}

float Window::GetAspectRatio() const {
    return static_cast<float>(m_Width) / static_cast<float>(m_Height);
}

} // namespace core
} // namespace bf
