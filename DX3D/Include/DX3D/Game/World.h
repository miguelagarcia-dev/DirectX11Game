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
        T* createGameObject() requires IsRegistered<GameObject, T>
        {
            UniquePtr<GameObject> e = std::make_unique<T>(GameObjectDesc{
                {m_logger},
                *this
                });
            return static_cast<T*>(createGameObjectInternal(e));
        }

        template <typename T> requires IsRegistered<Component, T>
        T* const* getComponents(ui32& numComponents) const noexcept
        {
            return reinterpret_cast<T* const*>(
                getComponentsInternal(T::GetTypeId(), &numComponents));
        }


        void update(f32 deltaTime);
    private:
        GameObject* createGameObjectInternal(UniquePtr<GameObject>& object);
        void addComponentInternal(Component& component);
        void addDirtyTransformInternal(TransformComponent& component);
        Component* const* getComponentsInternal(size_t typeId, ui32* numComponents) const noexcept;

    private:
        enum class EventType { Create = 0 };
        struct GameObjectEvent
        {
            GameObject* object{};
            size_t pendingObjectIndex{};
            EventType eventType{};
        };

    private:
        std::unordered_map<size_t, std::vector<UniquePtr<GameObject>>> m_objects{};
        std::unordered_map<size_t, std::vector<Component*>> m_components{};

        std::vector<TransformComponent*> m_dirtyTransforms{};

        std::vector<UniquePtr<GameObject>> m_pendingObjects;
        std::vector<UniquePtr<GameObject>> m_pendingObjectsSwapBuffer;

        std::vector<GameObjectEvent> m_events{};
        std::vector<GameObjectEvent> m_eventsSwapBuffer{};

        friend class GameObject;
        friend class TransformComponent;
    };
}