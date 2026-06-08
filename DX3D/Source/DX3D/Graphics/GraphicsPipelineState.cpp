#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/ShaderBinary.h>

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc) //this is the initializer list 
{
	//check if the data is correct 

	if (desc.vs.getType() != ShaderType::VertexShader)
		DX3DLogThrowInvalidArg("The 'vs' memebr is not a vaild vertex shader binary"); 
	if (desc.ps.getType() != ShaderType::PixelShader)
		DX3DLogThrowInvalidArg("The 'ps' memebr is not a vaild pixel shader binary");

	auto vs = desc.vs.getData(); 
	auto ps = desc.ps.getData();


	DX3DGraphicsLogThrowOnFail(m_device.CreateVertexShader(vs.data, vs.dataSize, nullptr, &m_vs),
		"CreateVertexShader failed.");

	DX3DGraphicsLogThrowOnFail(m_device.CreatePixelShader(ps.data, ps.dataSize, nullptr, &m_ps),
		"CreatePixelShader failed.");

}
