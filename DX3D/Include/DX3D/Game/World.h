#pragma once
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Identifiable.h>
#include <unordered_map>
#include <vector>

namespace dx3d
{
    class World final : public Base
    {
    public:
        explicit World(const WorldDesc& desc);

        template <typename T>
        T* createGameObject()
        {
            static_assert(std::is_base_of<GameObject, T>::value,
                "T must inherit from dx3d::GameObject.");
            static_assert(HasTypeId<T>,
                "T needs a unique TypeId. Make sure you added dx3d_typeid.");
            UniquePtr<GameObject> e = std::make_unique<T>(GameObjectDesc{
                {m_logger},
                *this
                });
            return static_cast<T*>(createGameObjectInternal(e));
        }

        void update(f32 deltaTime);

    private:
        GameObject* createGameObjectInternal(UniquePtr<GameObject>& object);

    private:
        enum class EventType { Create = 0 };
        struct GameObjectEvent
        {
            GameObject* object{};
            EventType eventType{};
        };

    private:
        std::unordered_map<size_t, std::vector<UniquePtr<GameObject>>> m_objects;
        std::vector<UniquePtr<GameObject>> m_pendingObjects;
        std::vector<UniquePtr<GameObject>> m_pendingObjectsSwapBuffer;
        std::vector<GameObjectEvent> m_events{};
        std::vector<GameObjectEvent> m_eventsSwapBuffer{};
    };
}