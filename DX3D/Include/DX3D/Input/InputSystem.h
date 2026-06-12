#pragma once
#include <DX3D/Core/Common.h>   // KeyCode, InputSystemDesc, BaseDesc
#include <DX3D/Core/Base.h>    
#include <DX3D/Math/Vec2.h>     // Vec2 (mouse position / delta)
#include <DX3D/Math/Rect.h>     // mouse border
#include <array>

namespace dx3d
{
    class InputSystem final : public Base
    {
    public:
        explicit InputSystem(const InputSystemDesc& desc);

        bool isKeyDown(KeyCode key) const;
        bool isKeyPressed(KeyCode key) const;
        bool isKeyReleased(KeyCode key) const;

        Vec2 getMousePosition() const noexcept;
        Vec2 getMouseDelta() const noexcept;

        void setCursorVisible(bool visible);
        void setCursorLocked(bool locked);
        void setCursorLockArea(const Rect& rect);

        void update();
    private:
        short getInternalKeyCode(const KeyCode& key);
        void centerCursor();
    private:
        std::array<bool, static_cast<std::size_t>(KeyCode::Count)> m_currentKeys{};
        std::array<bool, static_cast<std::size_t>(KeyCode::Count)> m_previousKeys{};
        Vec2 m_mousePosition{};
        Vec2 m_previousMousePosition{};
        Vec2 m_mouseDelta{};
        Rect m_lockArea{};
        bool m_cursorVisible{ true };
        bool m_cursorLocked{ false };
    };
}