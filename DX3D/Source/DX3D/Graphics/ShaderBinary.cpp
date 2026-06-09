#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsUtils.h>
#include <d3dcompiler.h>

dx3d::ShaderBinary::ShaderBinary(const ShaderCompileDesc& desc, const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc), m_type(desc.shaderType)
{
	//row pointers need vaildating attrubuites for non-null 
	
	if (!desc.shaderSourceName) DX3DLogThrowInvalidArg(" No shader soruce name provided.");
	if (!desc.shaderSourceCode) DX3DLogThrowInvalidArg(" No shader soruce code provided.");
	if (!desc.shaderSourceCodeSize) DX3DLogThrowInvalidArg(" No shader size provided.");
	if (!desc.shaderEntryPoint) DX3DLogThrowInvalidArg(" No shader entry point provided.");

	UINT compileFlags{};

#ifdef _DEBUG
	compileFlags |= D3DCOMPILE_DEBUG; // this enables some more debugging info 
#endif

	//function used to compil HLSL
	//passing some aurgments  that we need to define in our project to use. ->common.h defining attrubites we need for compling 
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob{}; 
	DX3DGraphicsCheckShaderCompile(
	D3DCompile(
		desc.shaderSourceCode,
		desc.shaderSourceCodeSize,
		desc.shaderSourceName,
		nullptr,
		nullptr,
		desc.shaderEntryPoint, //shader entry points are usally called vs.main ps.main 
		dx3d::GraphicsUtils::GetShaderModelTarget(desc.shaderType),
		compileFlags,
		0,
		&m_blob,
		&errorBlob 
	), 
		errorBlob.Get())

	//we cant use the same error handeling to throw on fail since theres build in errors so we'll make a custom macro for it in GraphicsLogUtils.h

}

dx3d::BinaryData dx3d::ShaderBinary::getData() const noexcept
{
	return //called brace initializetion 
	{
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize()
	};
}

dx3d::ShaderType dx3d::ShaderBinary::getType() const noexcept
{
	return m_type;
}
