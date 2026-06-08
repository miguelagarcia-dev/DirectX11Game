#pragma once
#include <DX3D/Graphics/GraphicsResource.h> 
#include <DX3D/Math/Vec4.h>

namespace dx3d
{

	class DeviceContext final: public GraphicsResource
	{

	public:
		explicit DeviceContext(const GraphicsResourceDesc& gDesc); //remeber that marking as explicit means not expecting more paramters  
		void clearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color);
		void setGraphicsPipelineState(const GraphicsPipelineState& pipeline);

	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context{};

		friend class GraphicsDevice; 
	};




}