#include <DX3D/Game/World.h>
#include <DX3D/Game/GameObject.h>

dx3d::World::World(const WorldDesc& desc) : Base(desc.base)
{
}

void dx3d::World::update(f32 deltaTime)
{
    if (m_events.size())
    {
        std::swap(m_events, m_eventsSwapBuffer);
        std::swap(m_pendingObjects, m_pendingObjectsSwapBuffer);

        for (auto& e : m_eventsSwapBuffer)
        {
            auto objTypeId = e.object->getTypeId();
            auto pendingObjIndex = e.object->getWorldIndex();

            if (e.eventType == EventType::Create)
            {
                auto& obj = m_pendingObjectsSwapBuffer[pendingObjIndex];
                auto ptr = obj.get();
                auto index = m_objects[objTypeId].size();
                ptr->setWorldIndex(index);
                m_objects[objTypeId].push_back(std::move(obj));
                ptr->onCreate();
            }
        }

        m_pendingObjectsSwapBuffer.clear();
        m_eventsSwapBuffer.clear();
    }

    for (auto&& [typeId, objects] : m_objects)
        for (auto& object : objects)
            object->onUpdate(deltaTime);
}

dx3d::GameObject* dx3d::World::createGameObjectInternal(UniquePtr<GameObject>& object)
{
    if (!object) return {};
    auto ptr = object.get();
    auto index = m_pendingObjects.size();
    ptr->setWorldIndex(index);
    m_pendingObjects.push_back(std::move(object));
    m_events.push_back({ ptr, EventType::Create });
    return ptr;
}