#pragma once

namespace RED4ext
{
template<typename T>
class UniquePtr;

template<typename T>
struct is_unique_ptr : std::false_type {};

template<typename T>
struct is_unique_ptr<UniquePtr<T>> : std::true_type {};

template<typename U>
constexpr bool is_unique_ptr_v = is_unique_ptr<U>::value;
}

// type resolution hell
template<typename T, size_t OFFSET>
class OffsetPtr
{
public:
    using Type = T;

    static constexpr size_t Offset = OFFSET;

    static constexpr bool isIndirect = 
        (std::is_pointer_v<T> && !std::is_void_v<std::remove_pointer_t<T>>) ||
        RED4ext::is_unique_ptr_v<T>;

    constexpr OffsetPtr(const void* aBase)
        : m_address(std::bit_cast<uintptr_t>(aBase) + Offset)
    {
    }

    constexpr T* GetPtr() const
    {
        return std::bit_cast<T*>(m_address);
    }

    constexpr decltype(auto) GetValuePtr() const
    {
        if constexpr (isIndirect) return *GetPtr();
        else return GetPtr();
    }

    template<typename U = decltype(GetValuePtr())>
    constexpr operator U*() const
    {
        return GetValuePtr();
    }

    [[nodiscard]] constexpr decltype(auto) operator->() const noexcept
    {
        if constexpr (isIndirect) 
        {
            if constexpr (std::is_pointer_v<T>) 
            {
                return *GetPtr();
            }
            else 
            {
                return GetPtr()->operator->();
            }
        }
        else 
        {
            return GetPtr();
        }
    }

    constexpr decltype(auto) operator*() const noexcept
    {
        return *GetValuePtr();
    }

private:
    const uintptr_t m_address;
};


template<typename BASE, typename T, size_t OFFSET>
class OffsetField : public OffsetPtr<T, OFFSET>
{
public:
    using BaseType = BASE;

    constexpr explicit OffsetField(const BaseType* aInstance) noexcept
        : OffsetPtr<T, OFFSET>(aInstance)
    {
    }
};