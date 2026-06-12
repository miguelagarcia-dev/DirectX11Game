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

dx3d::Vec3 dx3d::TransformComponent::getPosition() const noexcept { return m_position; }

void dx3d::TransformComponent::setRotation(const Vec3& rotation)
{
    m_rotation = rotation;
    markAsDirty();
}

dx3d::Vec3 dx3d::TransformComponent::getRotation() const noexcept { return m_rotation; }

void dx3d::TransformComponent::setScale(const Vec3& scale)
{
    m_scale = scale;
    markAsDirty();
}

dx3d::Vec3 dx3d::TransformComponent::getScale() const noexcept { return m_scale; }

dx3d::Vec3 dx3d::TransformComponent::forward()
{
    auto f = getRigidWorldMatrix().row(2);
    return dx3d::Vec3::normalize({ f.x, f.y, f.z });
}

dx3d::Vec3 dx3d::TransformComponent::right()
{
    auto r = getRigidWorldMatrix().row(0);
    return dx3d::Vec3::normalize({ r.x, r.y, r.z });
}

dx3d::Vec3 dx3d::TransformComponent::up()
{
    auto u = getRigidWorldMatrix().row(1);
    return dx3d::Vec3::normalize({ u.x, u.y, u.z });
}

dx3d::Mat4x4 dx3d::TransformComponent::getAffineWorldMatrix() noexcept
{
    updateWorldMatrix();
    return m_affineWorldMatrix;
}

dx3d::Mat4x4 dx3d::TransformComponent::getRigidWorldMatrix() noexcept
{
    updateWorldMatrix();
    return m_rigidWorldMatrix;
}

void dx3d::TransformComponent::updateWorldMatrix() noexcept
{
    if (!m_dirty) return;
    m_dirty = false;

    m_rigidWorldMatrix =
        Mat4x4::rotateX(m_rotation.x) *
        Mat4x4::rotateY(m_rotation.y) *
        Mat4x4::rotateZ(m_rotation.z) *
        Mat4x4::translate(m_position);

    m_affineWorldMatrix =
        Mat4x4::scale(m_scale) *
        m_rigidWorldMatrix;
}

void dx3d::TransformComponent::markAsDirty()
{
    if (m_dirty) return;
    m_dirty = true;
    m_world.addDirtyTransformInternal(*this);
}