#pragma once
#include <DX3D/Core/Core.h>

namespace dx3d
{

	class Vec4
	{

	public:
		Vec4() = default;
		Vec4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}; 

		static Vec4 cross(Vec4& v1, Vec4& v2, Vec4& v3) noexcept
		{
			return {
				 v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z * v3.y),
				-(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z)),
				 v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y),
				-(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y))
			};
		}

	public:
		f32 x{}, y{}, z{}, w{}; 

	};


}