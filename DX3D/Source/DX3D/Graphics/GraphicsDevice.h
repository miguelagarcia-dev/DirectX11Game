#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
#include <d3d11.h>
#include <wrl.h>


namespace dx3d
{
	class GraphicsDevice final: public Base, public std::enable_shared_from_this<GraphicsDevice> 
	{
	
	public: 
		explicit GraphicsDevice(const GraphicsDeviceDesc& desc);
		virtual ~GraphicsDevice() override;

		// any time we add a new subsystem we make a shared pointer here , and make a class in core 
		//these are method signatures 
		SwapChainPtr createSwapChain(const SwapChainDesc& desc); 
		DeviceContextPtr createDeviceContext(); 
		ShaderBinaryPtr compileShader(const ShaderCompileDesc& desc); 
		GraphicsPipelineStatePtr createGraphicsPipelineState(const GraphicsPipelineStateDesc& desc);

		void executeCommandList(DeviceContext& context);
	private: 
		GraphicsResourceDesc getGraphicsResourceDesc() const noexcept; 
	private: 
		//device pointer for virtual gpu, 
		//this uses refernece content, meaning theres a counter for how many things are pointer to
		// when its 0 it self dels
		// this is the main interface for creating resources and managing the graphics pipeline, it represents the virtual GPU and is used to create and manage resources such as buffers, textures, shaders, and states.
		
		Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext{};
		Microsoft::WRL::ComPtr<IDXGIDevice> m_dxgiDevice{};
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_dxgiAdapter{};
		Microsoft::WRL::ComPtr<IDXGIFactory> m_dxgiFactory{};

	};

}
	


