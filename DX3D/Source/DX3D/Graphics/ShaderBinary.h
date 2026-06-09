#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d 
{
	class ShaderBinary final: public GraphicsResource
	{
	public: 
		ShaderBinary(const ShaderCompileDesc& desc, const GraphicsResourceDesc& gDesc); //the graphics resocues has all the knowlege this class will need to do its function.
		BinaryData getData() const noexcept;
		ShaderType getType() const noexcept;
	
	private: 
		Microsoft::WRL::ComPtr<ID3DBlob> m_blob{}; 
		ShaderType m_type{};

	};
}
