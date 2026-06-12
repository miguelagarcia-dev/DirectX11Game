#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Math/Rect.h>
#include <DX3D/Math/Mat4x4.h>

namespace dx3d
{
    class CameraComponent final : public Component
    {
        dx3d_typeid(CameraComponent)
    public:
        explicit CameraComponent(const ComponentDesc& data);

        Mat4x4 getViewMatrix() noexcept;
        Mat4x4 getProjectionMatrix() const noexcept;

        void setFarPlane(f32 farPlane) noexcept;
        f32 getFarPlane() const noexcept;

        void setNearPlane(f32 nearPlane) noexcept;
        f32 getNearPlane() const noexcept;

        void setFieldOfView(f32 fieldOfView) noexcept;  // radians, clamped to (0, PI)
        f32 getFieldOfView() const noexcept;

        void setViewportSize(const Rect& size) noexcept;
        Rect getViewportSize() const noexcept;

    private:
        void computeProjectionMatrix() noexcept;

    private:
        Mat4x4 m_projection{};

        f32 m_nearPlane = 0.01f;
        f32 m_farPlane = 100.0f;
        f32 m_fieldOfView = 1.3f;   // ~74 degrees
        Rect m_viewportSize{ 1,1 };

        bool m_dirty{ true };
    };
}