#include <DX3D/Component/CameraComponent.h>
#include <DX3D/Component/TransformComponent.h>
#include <DX3D/Game/GameObject.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <algorithm>

dx3d::CameraComponent::CameraComponent(const ComponentDesc& data) : Component(data)
{
    computeProjectionMatrix();
}

dx3d::Mat4x4 dx3d::CameraComponent::getViewMatrix() noexcept
{
    return Mat4x4::inverse(m_object.getTransform().getRigidWorldMatrix());
}

dx3d::Mat4x4 dx3d::CameraComponent::getProjectionMatrix() const noexcept
{
    return m_projection;
}

void dx3d::CameraComponent::setFarPlane(f32 farPlane) noexcept
{
    if (farPlane <= m_nearPlane) return;
    m_farPlane = farPlane;
    computeProjectionMatrix();
}

dx3d::f32 dx3d::CameraComponent::getFarPlane() const noexcept
{
    return m_farPlane;
}

void dx3d::CameraComponent::setNearPlane(f32 nearPlane) noexcept
{
    if (nearPlane <= 0.001f) return;
    m_nearPlane = nearPlane;
    computeProjectionMatrix();
}

dx3d::f32 dx3d::CameraComponent::getNearPlane() const noexcept
{
    return m_nearPlane;
}

void dx3d::CameraComponent::setFieldOfView(f32 fieldOfView) noexcept
{
    if (fieldOfView <= 0.001f || fieldOfView >= MathUtils::PI) return;
    m_fieldOfView = fieldOfView;
    computeProjectionMatrix();
}

dx3d::f32 dx3d::CameraComponent::getFieldOfView() const noexcept
{
    return m_fieldOfView;
}

void dx3d::CameraComponent::setViewportSize(const Rect& area) noexcept
{
    if (m_viewportSize == area) return;
    if (m_viewportSize.width == 0 || m_viewportSize.height == 0) return;
    m_viewportSize = area;
    computeProjectionMatrix();
}

dx3d::Rect dx3d::CameraComponent::getViewportSize() const noexcept
{
    return m_viewportSize;
}

void dx3d::CameraComponent::computeProjectionMatrix() noexcept
{
    m_projection = Mat4x4::perspectiveFovLH(m_fieldOfView,
        (f32)m_viewportSize.width / (f32)m_viewportSize.height,
        m_nearPlane, m_farPlane);
}