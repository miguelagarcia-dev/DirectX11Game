#pragma once
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Identifiable.h>

namespace dx3d
{
    class GameObject : public Identifiable
    {
        dx3d_typeid(GameObject)
    public:
        explicit GameObject(const GameObjectDesc& desc);

    protected:
        virtual void onCreate() {}
        virtual void onUpdate(f32 deltaTime) {}

    private:
        size_t getWorldIndex() const noexcept;
        void setWorldIndex(size_t index) noexcept;
    private:
        World& m_world;
        size_t m_worldIndex{};

        friend class World;
    };
}