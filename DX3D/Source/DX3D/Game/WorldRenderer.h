#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <DX3D/Math/Mat4x4.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <d3d11.h>
#include <wrl.h>

namespace dx3d
{
	class WorldRenderer final : public Base
	{
	public:
		explicit WorldRenderer(const WorldRendererDesc& desc);
		virtual ~WorldRenderer() override;

		void render(const World& world, SwapChain& swapChain, f32 deltaTime);

	private:
		struct alignas(16) ConstantData
		{
			Mat4x4 world{};
			Mat4x4 view{};
			Mat4x4 proj{};
		};
	private:
		GraphicsDevice& m_graphicsDevice;
		RefPtr<DeviceContext> m_deviceContext{};
		RefPtr<GraphicsPipelineState> m_pipeline{};
		RefPtr<ConstantBuffer> m_cb{};
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler{};
	};
}