#pragma once
#include <DX3D/Core/Common.h>
#include <d3d11.h>
#include <bit>

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

		inline DXGI_FORMAT GetDXGIFormatFromMask(D3D_REGISTER_COMPONENT_TYPE type, UINT mask)
		{	//mask just like class, if a bit is used the other are not checked
			auto componentCount = std::popcount(mask); 
			if (componentCount < 1) return DXGI_FORMAT_UNKNOWN; 

			constexpr DXGI_FORMAT formatTable[1][4] =
			{
				{
					DXGI_FORMAT_R32_FLOAT,
					DXGI_FORMAT_R32G32_FLOAT,
					DXGI_FORMAT_R32G32B32_FLOAT,
					DXGI_FORMAT_R32G32B32A32_FLOAT
				 }
			};

			auto typeIndex = 0u; 
			switch (type)
			{
			case D3D_REGISTER_COMPONENT_FLOAT32: typeIndex = 0u; break;
			deafault:  return DXGI_FORMAT_UNKNOWN;

			}
			return formatTable[typeIndex][componentCount - 1]; 
		}
	}
}