#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <DX3D/Math/Mat4x4.h>

namespace dx3d
{
	class WorldRenderer final : public Base
	{
	public:
		explicit WorldRenderer(const WorldRendererDesc& desc);
		virtual ~WorldRenderer() override; // override the destructor to ensure that it is called when the object is destroyed

		void render(const World& world, SwapChain& swapChain, f32 deltaTime);
	private:
		struct Vertex ////this struct must be a prefect match in the hlsl shader code
		{
			Vec3 position;
			Vec4 color;
		};
		struct alignas(16) ConstantData
		{
			Mat4x4 world{};
			Mat4x4 proj{};
		};
	private:
		GraphicsDevice& m_graphicsDevice; // //turned into a shared pointer 
		RefPtr<DeviceContext> m_deviceContext{};
		RefPtr<GraphicsPipelineState> m_pipeline{};
		RefPtr<VertexBuffer> m_vb{};
		RefPtr<ConstantBuffer> m_cb{};
		RefPtr<IndexBuffer> m_ib{};
	};
}