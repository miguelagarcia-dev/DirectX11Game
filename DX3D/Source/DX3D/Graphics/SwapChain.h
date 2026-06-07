#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d
{
	class SwapChain final: public GraphicsResource 
	{

	public:
		SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc); 

	private: 
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain{};
	};

} 