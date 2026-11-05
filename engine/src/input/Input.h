#pragma once

#include <string>
#include <memory>

namespace bf {

class Window;

namespace input {

enum class KeyCode {
    Unknown = -1,
    Space = 32,
    Apostrophe = 39,
    Comma = 44,
    Minus = 45,
    Period = 46,
    Slash = 47,
    Key0 = 48, Key1, Key2, Key3, Key4, Key5, Key6, Key7, Key8, Key9,
    Semicolon = 59,
    Equal = 61,
    A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    LeftBracket = 91,
    Backslash = 92,
    RightBracket = 93,
    Escape = 256,
    Enter, Tab, Backspace, Insert, Delete,
    Right, Left, Down, Up,
    PageUp, PageDown, Home, End,
    CapsLock = 280,
    ScrollLock, NumLock, PrintScreen, Pause,
    F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    LeftShift = 340,
    LeftControl, LeftAlt, LeftSuper,
    RightShift, RightControl, RightAlt, RightSuper
};

enum class MouseButton {
    Left = 0,
    Right = 1,
    Middle = 2,
    Button4 = 3,
    Button5 = 4
};

enum class GamepadButton {
    A = 0, B, X, Y,
    LeftBumper, RightBumper,
    Back, Start, Guide,
    LeftThumb, RightThumb,
    DPadUp, DPadRight, DPadDown, DPadLeft
};

enum class GamepadAxis {
    LeftX = 0,
    LeftY,
    RightX,
    RightY,
    LeftTrigger,
    RightTrigger
};

class Input {
public:
    Input();
    ~Input();

    void Initialize(Window* window);
    void Update();

    // Keyboard
    bool IsKeyDown(KeyCode key) const;
    bool IsKeyPressed(KeyCode key) const;
    bool IsKeyReleased(KeyCode key) const;

    // Mouse
    bool IsMouseButtonDown(MouseButton button) const;
    bool IsMouseButtonPressed(MouseButton button) const;
    bool IsMouseButtonReleased(MouseButton button) const;

    void GetMousePosition(float& x, float& y) const;
    void GetMouseDelta(float& dx, float& dy) const;
    float GetMouseScroll() const;

    // Gamepad
    bool IsGamepadConnected(int gamepadID) const;
    bool IsGamepadButtonDown(int gamepadID, GamepadButton button) const;
    bool IsGamepadButtonPressed(int gamepadID, GamepadButton button) const;
    float GetGamepadAxis(int gamepadID, GamepadAxis axis) const;

    void SetCursorVisible(bool visible);
    void SetCursorLocked(bool locked);

private:
    struct InputState;
    std::unique_ptr<InputState> m_State;
};

} // namespace input
} // namespace bf
