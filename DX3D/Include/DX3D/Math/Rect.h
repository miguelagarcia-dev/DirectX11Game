#pragma once
#include <DX3D/Core/Core.h>

namespace dx3d
{
	class Rect
	{

	public: 
		Rect() = default;
		Rect(i32 width, i32 height) : left(0), top(0), width(width), height(height) {}
		Rect(i32 left, i32 top, i32 width, i32 height): left(left), top(left), width(width), height(height) {}
		
		bool operator==(const Rect& other) const noexcept
		{
			return left == other.left &&
				top == other.top &&
				width == other.width &&
				height == other.height;
		}

		bool operator!=(const Rect& other) const noexcept
		{
			return !(*this == other);
		}

	public:
		i32 left{}, top{}, width{}, height{}; //intializingfined 32 bit intergers for the sides of the rectangle

	};

}