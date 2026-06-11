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

	public:
		Vec3& operator+=(const Vec3& rhs)
		{
			x += rhs.x; y += rhs.y; z += rhs.z;
			return *this;
		}

		Vec3& operator*=(float scalar)
		{
			x *= scalar; y *= scalar; z *= scalar;
			return *this;
		}

		static Vec3 normalize(const Vec3& v)
		{
			float lenSq = v.x * v.x + v.y * v.y + v.z * v.z;
			if (lenSq == 0.0f) return Vec3{ 0.0f, 0.0f, 0.0f };
			float invLen = 1.0f / std::sqrt(lenSq);
			return Vec3{ v.x * invLen, v.y * invLen, v.z * invLen };
		}
	};

	inline Vec3 operator+(Vec3 lhs, const Vec3& rhs) { lhs += rhs; return lhs; }
	inline Vec3 operator*(Vec3 v, float scalar) { v *= scalar; return v; }
	inline Vec3 operator*(float scalar, Vec3 v) { v *= scalar; return v; }
}