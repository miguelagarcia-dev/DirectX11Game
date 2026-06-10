#pragma once
#include <d3d11.h>

namespace dx3d
{
	namespace GraphicsLogUtils
	{
		inline void CheckShaderCompile(Logger& logger, HRESULT hr, ID3DBlob* errorBlob)
		{
			auto errorMsg = errorBlob ? static_cast<const char*>(errorBlob->GetBufferPointer()) : nullptr; //if error blob yes get it, if not null 

			if (FAILED(hr))
				DX3DLogThrow(logger, std::runtime_error, Logger::LogLevel::Error,
					"Shader compilation failed.\nDetails:\n{}", errorMsg ? errorMsg : "");
			if (errorMsg)
				DX3DLog(logger, Logger::LogLevel::Warning,
					"Shader compiled with warnings.\nDetails:\n{}", errorMsg);

		}
	}
}

#define DX3DGraphicsLogThrowOnFail(hr, message, ...)\
	{\
	auto res = (hr);\
	if (FAILED(res))\
		DX3DLogThrowError(message, __VA_ARGS__);\
	}
//calling this function easier
#define DX3DGraphicsCheckShaderCompile(hr, errorBlob)\
{\
auto res = (hr);\
dx3d::GraphicsLogUtils::CheckShaderCompile(getLogger(), res, errorBlob);\
}
