#pragma once
#include <DX3D/Core/Common.h>

namespace dx3d
{

	namespace GraphicsUtils //this is a utility function that has no memebr data or state so stateless classes can be avoided 
	{

		inline const char* GetShaderModelTarget(ShaderType type) //inline is in namespace it can be included in multipule units, this can be used for templates as well
		{
			switch (type)
			{
			case ShaderType::VertexShader: return "vs_5_0";
			case ShaderType::PixelShader: return "ps_5_0";
			default: return ""; 
			}
		}
	};

}