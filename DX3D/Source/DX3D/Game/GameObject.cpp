#include <DX3D/Game/GameObject.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Component/TransformComponent.h>
#include <DX3D/Game/World.h>

dx3d::GameObject::GameObject(const GameObjectDesc& desc)
    : Identifiable(desc.base), m_world(desc.world)
{
    m_transform = createOrGetComponent<TransformComponent>();  // cache it
}

dx3d::TransformComponent& dx3d::GameObject::getTransform() noexcept
{
    return *m_transform;
}

dx3d::Component* dx3d::GameObject::createComponentInternal(UniquePtr<Component>& component)
{
    if (!component) return {};
    auto typeId = component->getTypeId();
    auto ptr = component.get();
    if (m_components.find(typeId) != m_components.end()) return {};
    m_components.emplace(typeId, std::move(component));
    m_world.addComponentInternal(*ptr);
    return ptr;
}

dx3d::Component* dx3d::GameObject::getComponentInternal(size_t id)
{
    auto it = m_components.find(id);
    if (it == m_components.end()) return {};
    return it->second.get();
}