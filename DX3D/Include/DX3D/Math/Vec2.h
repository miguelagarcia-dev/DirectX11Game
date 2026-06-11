#pragma once
#include <DX3D/Core/Core.h>

namespace dx3d
{
    class Vec2
    {
    public:
        Vec2() = default;
        Vec2(f32 x, f32 y) : x(x), y(y) {}
    public:
        f32 x{}, y{};
    };
}