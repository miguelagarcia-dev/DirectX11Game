#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/VertexShaderSignature.h>

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc) //this is the initializer list 
{
	//check if the data is correct 

	
	if (desc.ps.getType() != ShaderType::PixelShader)
		DX3DLogThrowInvalidArg("The 'ps' memebr is not a vaild pixel shader binary");

	auto vs = desc.vs.getShaderBinaryData(); 
	auto ps = desc.ps.getData();
	auto vsInputElements = desc.vs.getInputElementsData();

	//input layer defines how the vertex buffers data are interperted by the vertex shadder 
	// cpu side vertex data -> gpu side shader input 
	//float3 positon : POSITION0;
	//float4 color : COLOR0;
	//changed from hard coded to more modualr 
	// constexpr D3D11_INPUT_ELEMENT_DESC elements[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	//	// offset = float3(4byte,4byte,4bytes)         ^ so color comes after is 12 bytes off
	//};

	DX3DGraphicsLogThrowOnFail(
		m_device.CreateInputLayout(
			static_cast<const D3D11_INPUT_ELEMENT_DESC*>(vsInputElements.data),
			static_cast<ui32>(vsInputElements.dataSize),
			vs.data,
			vs.dataSize,
			&m_layout),
		"CreateInputLayout failed.");

	DX3DGraphicsLogThrowOnFail(
		m_device.CreateVertexShader(vs.data, vs.dataSize, nullptr, &m_vs),
		"CreateVertexShader failed.");

	DX3DGraphicsLogThrowOnFail(
		m_device.CreatePixelShader(ps.data, ps.dataSize, nullptr, &m_ps),
		"CreatePixelShader failed.");

}
