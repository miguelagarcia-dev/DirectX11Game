#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Math/Vec3.h>
#include <cmath>

namespace dx3d
{
    class Mat4x4
    {
    public:
        Mat4x4() = default;

        static Mat4x4 identity() noexcept
        {
            Mat4x4 res{};
            res.m_data[0][0] = 1;
            res.m_data[1][1] = 1;
            res.m_data[2][2] = 1;
            res.m_data[3][3] = 1;
            return res;
        }

        static Mat4x4 translate(const Vec3& translation) noexcept
        {
            auto res = Mat4x4::identity();
            res.m_data[3][0] = translation.x;
            res.m_data[3][1] = translation.y;
            res.m_data[3][2] = translation.z;
            return res;
        }

        static Mat4x4 scale(const Vec3& scale) noexcept
        {
            Mat4x4 res{};
            res.m_data[0][0] = scale.x;
            res.m_data[1][1] = scale.y;
            res.m_data[2][2] = scale.z;
            res.m_data[3][3] = 1;
            return res;
        }

        static Mat4x4 rotateZ(f32 z) noexcept
        {
            Mat4x4 res{};
            res.m_data[0][0] = std::cos(z);
            res.m_data[0][1] = std::sin(z);
            res.m_data[1][0] = -std::sin(z);
            res.m_data[1][1] = std::cos(z);
            res.m_data[2][2] = 1;
            res.m_data[3][3] = 1;
            return res;
        }

        Mat4x4 operator *(const Mat4x4& rhs) const noexcept
        {
            Mat4x4 res{};
            for (auto row = 0u; row < 4u; ++row)
            {
                for (auto k = 0u; k < 4u; ++k)
                {
                    auto temp = m_data[row][k];
                    for (auto col = 0u; col < 4u; ++col)
                    {
                        res.m_data[row][col] += temp * rhs.m_data[k][col];
                    }
                }
            }
            return res;
        }

    private:
        f32 m_data[4][4]{};
    };
}