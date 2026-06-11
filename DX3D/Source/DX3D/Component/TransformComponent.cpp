#include <DX3D/Component/TransformComponent.h>
#include <DX3D/Game/World.h>

dx3d::TransformComponent::TransformComponent(const ComponentDesc& data) : Component(data)
{
    markAsDirty();
}

void dx3d::TransformComponent::setPosition(const Vec3& position)
{
    m_position = position;
    markAsDirty();
}

dx3d::Vec3 dx3d::TransformComponent::getPosition() const noexcept
{
    return m_position;
}

void dx3d::TransformComponent::setRotation(const Vec3& rotation)
{
    m_rotation = rotation;
    markAsDirty();
}

dx3d::Vec3 dx3d::TransformComponent::getRotation() const noexcept
{
    return m_rotation;
}

void dx3d::TransformComponent::setScale(const Vec3& scale)
{
    m_scale = scale;
    markAsDirty();
}

dx3d::Vec3 dx3d::TransformComponent::getScale() const noexcept
{
    return m_scale;
}

dx3d::Mat4x4 dx3d::TransformComponent::getWorldMatrix() noexcept
{ // wrapper that ensures the matrix is up to date before returning it.
    updateWorldMatrix();
    return m_worldMat;
}

void dx3d::TransformComponent::updateWorldMatrix() noexcept
{
    if (!m_dirty) return;
    m_dirty = false;
    m_worldMat =
        Mat4x4::scale(m_scale) *
        Mat4x4::rotateX(m_rotation.x) *
        Mat4x4::rotateY(m_rotation.y) *
        Mat4x4::rotateZ(m_rotation.z) *
        Mat4x4::translate(m_position);
}


void dx3d::TransformComponent::markAsDirty()
{
    if (m_dirty) return;
    m_dirty = true;
    m_world.addDirtyTransformInternal(*this);
}