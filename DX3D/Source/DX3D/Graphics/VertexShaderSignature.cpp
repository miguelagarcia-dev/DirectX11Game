#include <DX3D/Graphics/VertexShaderSignature.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsUtils.h>
#include <d3dcompiler.h>
#include <ranges>

//purpose of the class is to handle vertex input data 
dx3d::VertexShaderSignature::VertexShaderSignature(const VertexShaderSignatureDesc& desc, const GraphicsResourceDesc gDesc) :
	GraphicsResource(gDesc), m_vsBinary(desc.vsBinary)
{
	if (!desc.vsBinary) DX3DLogThrowInvalidArg("No shader binary provided.");
	if (desc.vsBinary->getType() != ShaderType::VertexShader)
		DX3DLogThrowInvalidArg("The 'vsbinary' memebr is not a vaild vertex shader binary");

	auto vsData = m_vsBinary->getData();

	//allows us to inspect shader componenets  
	DX3DGraphicsLogThrowOnFail(D3DReflect(
		vsData.data,
		vsData.dataSize,
		IID_PPV_ARGS(&m_shaderReflection)),
		"D3DReflected failed."); 
	
	D3D11_SHADER_DESC shaderDesc{};
	DX3DGraphicsLogThrowOnFail(m_shaderReflection->GetDesc(&shaderDesc),
		"ID3D11ShaderReflection::GetDesc failed.");

	m_numElements = shaderDesc.InputParameters; 

	D3D11_SIGNATURE_PARAMETER_DESC params[D3D11_STANDARD_VERTEX_ELEMENT_COUNT]{};
	for (auto i: std::views::iota(0u, m_numElements))
	{ 
		DX3DGraphicsLogThrowOnFail(m_shaderReflection->GetInputParameterDesc(i, &params[i]),
			"ID3D11ShaderReflection::GetInputParameterDesc failed.");
	}

	//constexpr D3D11_INPUT_ELEMENT_DESC elements[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	//};

	for (auto i : std::views::iota(0u, m_numElements))
	{
		auto param = params[i];
		m_elements[i] = {
			param.SemanticName,
			param.SemanticIndex,
			GraphicsUtils::GetDXGIFormatFromMask(param.ComponentType, param.Mask),
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		};

	};

}

dx3d::BinaryData dx3d::VertexShaderSignature::getShaderBinaryData() const noexcept
{
	return m_vsBinary->getData();
}

dx3d::BinaryData dx3d::VertexShaderSignature::getInputElementsData() const noexcept
{
	return
	{
		m_elements,
		m_numElements

	};
}

