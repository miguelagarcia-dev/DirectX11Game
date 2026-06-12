#pragma once
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Identifiable.h>
#include <DX3D/Game/Component.h>
#include <DX3D/Component/MeshComponent.h>

#include <unordered_map>

namespace dx3d
{
	class GameObject : public Identifiable
	{
		dx3d_typeid(GameObject)
	public:
		explicit GameObject(const GameObjectDesc& desc);
		World& getWorld() noexcept;
		InputSystem& getInputSystem() noexcept;

		template <typename T>
		T* createOrGetComponent() requires IsRegistered<Component, T>
		{
			auto c = getComponent<T>();
			if (c) return c;
			UniquePtr<Component> cp = std::make_unique<T>(ComponentDesc{
								{m_logger},
								*this,
								m_world
				});
			return static_cast<T*>(createComponentInternal(cp));
		}

		template <typename T>
		T* getComponent() requires IsRegistered<Component, T>
		{
			return static_cast<T*>(getComponentInternal(T::GetTypeId()));
		}

		template <typename T>
		T* createOrGetComponent(std::shared_ptr<GraphicsDevice> graphicsDevice)
			requires IsRegistered<Component, T>
		{
			auto c = getComponent<T>();
			if (c) return c;
			UniquePtr<Component> cp = std::make_unique<T>(MeshComponentDesc{
				{ {m_logger}, *this, m_world },
				graphicsDevice
				});
			return static_cast<T*>(createComponentInternal(cp));
		}

		TransformComponent& getTransform() noexcept;
	protected:
		virtual void onCreate() {}
		virtual void onUpdate(f32 deltaTime) {}
	private:
		Component* createComponentInternal(UniquePtr<Component>& component);
		Component* getComponentInternal(size_t id);
	private:
		std::unordered_map<size_t, UniquePtr<Component>> m_components{};
		TransformComponent* m_transform{};
		GameContext m_gameContext;
		World& m_world;
		friend class World;
	};
}