#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

//this will contain the configuration settings and objects for how the gpu will proccess and treat graphics 
//how shaders are used 
//how pixel are blended 
//how vertices are interperted 
//how testing is applied

namespace dx3d  
{ 
	class GraphicsPipelineState final : public GraphicsResource
	{
	public: 
		GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const GraphicsResourceDesc& gDesc);
	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs{};
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps{};
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout{};
		friend class DeviceContext;
	};
 
}