#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Math/MathUtils.h>
#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>
#include <cmath>
#include <cassert>

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

        static Mat4x4 rotateX(f32 x) noexcept
        {
            Mat4x4 res{};
            res.m_data[0][0] = 1;
            res.m_data[1][1] = std::cos(x);
            res.m_data[1][2] = std::sin(x);
            res.m_data[2][1] = -std::sin(x);
            res.m_data[2][2] = std::cos(x);
            res.m_data[3][3] = 1;
            return res;
        }

        static Mat4x4 rotateY(f32 y) noexcept
        {
            Mat4x4 res{};
            res.m_data[0][0] = std::cos(y);
            res.m_data[1][1] = 1;
            res.m_data[0][2] = -std::sin(y);
            res.m_data[2][0] = std::sin(y);
            res.m_data[2][2] = std::cos(y);
            res.m_data[3][3] = 1;
            return res;
        }
        static Mat4x4 orthoLH(f32 width, f32 height, f32 zNear, f32 zFar) noexcept
        {
            assert(width != 0.0f && "OrthoLH: width must not be zero");
            assert(height != 0.0f && "OrthoLH: height must not be zero");
            assert(zFar != zNear && "OrthoLH: zNear and zFar cannot be equal");

            Mat4x4 res{};
            res.m_data[0][0] = 2.0f / width;
            res.m_data[1][1] = 2.0f / height;
            res.m_data[2][2] = 1.0f / (zFar - zNear);
            res.m_data[3][2] = -(zNear / (zFar - zNear));
            res.m_data[3][3] = 1;
            return res;
        }

        static Mat4x4 perspectiveFovLH(f32 fov, f32 aspect, f32 zNear, f32 zFar) noexcept
        {
            assert(fov > 0.001f && "perspectiveFovLH: fov must be greater than 0 radians");
            assert(fov < MathUtils::PI - 0.001f && "perspectiveFovLH: fov must be less than PI radians");
            assert(aspect > 0.0f && "perspectiveFovLH: aspect ratio must be greater than 0");
            assert(zFar != zNear && "perspectiveFovLH: zNear and zFar cannot be equal");

            Mat4x4 res{};
            f32 yscale = 1.0f / tan(fov / 2.0f);
            f32 xscale = yscale / aspect;
            res.m_data[0][0] = xscale;
            res.m_data[1][1] = yscale;
            res.m_data[2][2] = zFar / (zFar - zNear);
            res.m_data[2][3] = 1.0f;
            res.m_data[3][2] = (-zNear * zFar) / (zFar - zNear);
            res.m_data[3][3] = 0.0f;
            return res;
        }

        static f32 determinant(const Mat4x4& rhs) noexcept
        {
            auto v1 = Vec4(rhs.m_data[0][0], rhs.m_data[1][0], rhs.m_data[2][0], rhs.m_data[3][0]);
            auto v2 = Vec4(rhs.m_data[0][1], rhs.m_data[1][1], rhs.m_data[2][1], rhs.m_data[3][1]);
            auto v3 = Vec4(rhs.m_data[0][2], rhs.m_data[1][2], rhs.m_data[2][2], rhs.m_data[3][2]);
            auto minor = Vec4::cross(v1, v2, v3);
            return -(rhs.m_data[0][3] * minor.x +
                rhs.m_data[1][3] * minor.y +
                rhs.m_data[2][3] * minor.z +
                rhs.m_data[3][3] * minor.w);
        }

        static Mat4x4 inverse(const Mat4x4& rhs) noexcept
        {
            Mat4x4 out{};
            Vec4 vec[3]{};
            auto det = Mat4x4::determinant(rhs);
            if (!det) return{};
            for (auto i = 0; i < 4; i++)
            {
                for (auto j = 0; j < 4; j++)
                {
                    if (j != i)
                    {
                        auto a = j;
                        if (j > i) a = a - 1;
                        vec[a].x = (rhs.m_data[j][0]);
                        vec[a].y = (rhs.m_data[j][1]);
                        vec[a].z = (rhs.m_data[j][2]);
                        vec[a].w = (rhs.m_data[j][3]);
                    }
                }
                auto v = Vec4::cross(vec[0], vec[1], vec[2]);
                out.m_data[0][i] = (f32)std::pow(-1.0f, i) * v.x / det;
                out.m_data[1][i] = (f32)std::pow(-1.0f, i) * v.y / det;
                out.m_data[2][i] = (f32)std::pow(-1.0f, i) * v.z / det;
                out.m_data[3][i] = (f32)std::pow(-1.0f, i) * v.w / det;
            }
            return out;
        }

        Vec4 row(ui32 index) const
        {
            assert(index < 4 && "Matrix row index out of range");
            return { m_data[index][0], m_data[index][1], m_data[index][2], m_data[index][3] };
        }

        Vec4 column(ui32 index) const
        {
            assert(index < 4 && "Matrix column index out of range");
            return { m_data[0][index], m_data[1][index], m_data[2][index], m_data[3][index] };
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