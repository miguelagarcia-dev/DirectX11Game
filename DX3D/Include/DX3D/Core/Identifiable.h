#pragma once
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
#include <type_traits>
//enbaling a macro to use hascode a math algo to genreate unquie id's for game objects 

#define dx3d_typeid(Class)           \
public:                              \
using type_id_tag = Class;           \
static size_t GetTypeId()            \
{                                    \
    static const auto id = typeid(Class).hash_code(); \
    return id;                       \
}                                    \
size_t getTypeId() const noexcept override \
{                                    \
    return GetTypeId();              \
}

namespace dx3d
{
    class Identifiable : public Base
    {
    public:
        explicit Identifiable(const BaseDesc& desc) :
            Base(desc)
        {
        }
        virtual size_t getTypeId() const noexcept = 0;
    };

    template <typename T>
    concept HasTypeId = std::is_same_v<typename T::type_id_tag, T>;

    template <typename Base, typename Derived>
    concept IsRegistered = std::is_base_of_v<Base, Derived>&& HasTypeId<Derived>;
}