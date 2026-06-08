#pragma once
#include<DX3D/Core/Logger.h>

namespace dx3d
{
#define DX3DGraphicsLogThrowOnFail(hr,message)\
	{\
	auto res = (hr);\
	if (FAILED(res))\
		DX3DLogErrorAndThrow(message);\
	}

}