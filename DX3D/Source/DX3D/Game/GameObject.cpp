#include <DX3D/Game/GameObject.h>

dx3d::GameObject::GameObject(const GameObjectDesc& desc)
    : Identifiable(desc.base), m_world(desc.world)
{
}

size_t dx3d::GameObject::getWorldIndex() const noexcept
{
    return m_worldIndex;
}

void dx3d::GameObject::setWorldIndex(size_t index) noexcept
{
    m_worldIndex = index;
}