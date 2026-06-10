#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>

namespace dx3d
{
	// we need to use final here because we don't want to allow inheritance from this class,
	// as it is the main class of the engine and should not be extended or modified by users,
	// it should be used as is, and if users want to extend or modify the engine, they should 
	// create their own classes that use the engine as a component, rather than inheriting from it.

	class GraphicsEngine final : public Base 
	{ 
	public:

		//constructor and destructor
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override; // override the destructor to ensure that it is called when the object is destroyed
		

		GraphicsDevice& getGraphicsDevice() noexcept;

		void render(SwapChain& swapChain, f32 deltaTime);

	private: //this struct must be a prefect match in the hlsl shader code
		struct Vertex 
		{
			Vec3 positon; 
			Vec4 color;
		};

	private:
		std::shared_ptr<GraphicsDevice> m_graphicsDevice{}; //turned into a shared pointer 
		RefPtr<DeviceContext> m_deviceContext{};
		RefPtr<GraphicsPipelineState> m_pipeline{};
		RefPtr<VertexBuffer> m_vb{};

	private:
		struct alignas(16) ConstantData
		{
			f32 scale{};
		};
	private:
		RefPtr<ConstantBuffer> m_cb{};
		f32 m_sum{};
		f32 m_scale{};
	};
}
	
