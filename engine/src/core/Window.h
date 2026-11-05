#pragma once

#include <string>
#include <cstdint>

namespace bf {
namespace core {

class Window {
public:
    Window();
    ~Window();

    bool Create(const std::string& title, uint32_t width, uint32_t height);
    void Destroy();

    void PollEvents();
    void SwapBuffers();

    bool ShouldClose() const;
    void SetShouldClose(bool value);

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }
    float GetAspectRatio() const;

    void* GetNativeWindow() const { return m_NativeWindow; }

private:
    void* m_NativeWindow;
    std::string m_Title;
    uint32_t m_Width;
    uint32_t m_Height;
    bool m_ShouldClose;
};

} // namespace core
} // namespace bf
