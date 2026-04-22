#pragma once

#include <RED4ext/Memory/UniquePtr.hpp>

template<typename T, size_t OFFSET>
class OffsetPtr
{
public:
    using Type = T;

    static constexpr size_t Offset = OFFSET;

    constexpr OffsetPtr(const void* aBase)
        : m_address(std::bit_cast<uintptr_t>(aBase) + Offset)
    {
    }

    constexpr T* GetPtr() const
    {
        return std::bit_cast<T*>(m_address);
    }

    constexpr T& GetRef() const
    {
        return *GetPtr();
    }

    constexpr T& operator*() const
    { 
        return GetRef(); 
    }

private:
    const uintptr_t m_address;
};
