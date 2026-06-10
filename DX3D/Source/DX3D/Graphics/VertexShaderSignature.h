#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <d3dcompiler.h>

namespace dx3d
{ 
	class VertexShaderSignature final: public GraphicsResource
	{
	public: 
		VertexShaderSignature(const VertexShaderSignatureDesc& desc,  const GraphicsResourceDesc gDesc);
		BinaryData getShaderBinaryData() const noexcept;
		BinaryData getInputElementsData() const noexcept;
	private:
		RefPtr<ShaderBinary> m_vsBinary{};
		Microsoft::WRL::ComPtr<ID3D11ShaderReflection> m_shaderReflection{};
		D3D11_INPUT_ELEMENT_DESC m_elements[D3D11_STANDARD_VERTEX_ELEMENT_COUNT]{}; 
		ui32 m_numElements{};

	};
}