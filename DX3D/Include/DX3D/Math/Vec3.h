#pragma once
#include <DX3D/Core/Core.h>
namespace dx3d
{
	class Vec3 
	{
	public:
		Vec3() = default;
		Vec3(f32 x, f32 y, f32 z) :x(x), y(y), z(z) {}
	public:
		f32 x{}, y{}, z{};
	};

}