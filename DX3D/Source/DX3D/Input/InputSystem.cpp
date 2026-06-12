#include <DX3D/Input/InputSystem.h>
#include <ranges>
#include <Windows.h>

dx3d::InputSystem::InputSystem(const InputSystemDesc& desc) : Base(desc.base) 
{
}


bool dx3d::InputSystem::isKeyDown(KeyCode key) const
{
    return m_currentKeys[static_cast<std::size_t>(key)];
}

bool dx3d::InputSystem::isKeyPressed(KeyCode key) const
{
    return m_currentKeys[static_cast<std::size_t>(key)] &&
        !m_previousKeys[static_cast<std::size_t>(key)];
}

bool dx3d::InputSystem::isKeyReleased(KeyCode key) const
{
    return !m_currentKeys[static_cast<std::size_t>(key)] &&
        m_previousKeys[static_cast<std::size_t>(key)];
}

dx3d::Vec2 dx3d::InputSystem::getMousePosition() const noexcept
{
    return m_mousePosition;
}

dx3d::Vec2 dx3d::InputSystem::getMouseDelta() const noexcept
{
    return m_mouseDelta;
}

void dx3d::InputSystem::setCursorVisible(bool visible)
{
    m_cursorVisible = visible;
    while (ShowCursor(visible) < 0 && visible) {}
    while (ShowCursor(visible) >= 0 && !visible) {}
}

void dx3d::InputSystem::setCursorLocked(bool locked)
{
    m_cursorLocked = locked;
    if (locked) centerCursor();
}

void dx3d::InputSystem::setCursorLockArea(const Rect& rect)
{
    m_lockArea = rect;
}

void dx3d::InputSystem::update()
{
    m_previousKeys = m_currentKeys;

    for (auto i : std::views::iota(0u, static_cast<std::size_t>(KeyCode::Count)))
    {
        const auto vk = getInternalKeyCode(static_cast<KeyCode>(i));
        m_currentKeys[i] = (GetAsyncKeyState(vk) & 0x8000) != 0;
    }

    m_previousMousePosition = m_mousePosition;

    POINT point{};
    GetCursorPos(&point);

    m_mousePosition.x = static_cast<f32>(point.x);
    m_mousePosition.y = static_cast<f32>(point.y);

    m_mouseDelta.x = m_mousePosition.x - m_previousMousePosition.x;
    m_mouseDelta.y = m_mousePosition.y - m_previousMousePosition.y;

    if (m_cursorLocked) centerCursor();
}

short dx3d::InputSystem::getInternalKeyCode(const KeyCode& key)
{
    const auto value = static_cast<int>(key);
    if (key >= KeyCode::A && key <= KeyCode::Z) return 'A' + (value - static_cast<int>(KeyCode::A));
    if (key >= KeyCode::Num0 && key <= KeyCode::Num9) return '0' + (value - static_cast<int>(KeyCode::Num0));

    switch (key)
    {
    case KeyCode::Shift:       return VK_SHIFT;
    case KeyCode::Escape:      return VK_ESCAPE;
    case KeyCode::Space:       return VK_SPACE;
    case KeyCode::Enter:       return VK_RETURN;
    case KeyCode::MouseLeft:   return VK_LBUTTON;
    case KeyCode::MouseMiddle: return VK_MBUTTON;
    case KeyCode::MouseRight:  return VK_RBUTTON;
    case KeyCode::Up:          return VK_UP;
    case KeyCode::Down:        return VK_DOWN;
    case KeyCode::Left:        return VK_LEFT;
    case KeyCode::Right:       return VK_RIGHT;
    default:                   return 0;
    }
}

void dx3d::InputSystem::centerCursor()
{
    const auto centerX = m_lockArea.left + (m_lockArea.width / 2);
    const auto centerY = m_lockArea.top + (m_lockArea.height / 2);
    SetCursorPos(centerX, centerY);
    m_mousePosition.x = static_cast<f32>(centerX);
    m_mousePosition.y = static_cast<f32>(centerY);
}