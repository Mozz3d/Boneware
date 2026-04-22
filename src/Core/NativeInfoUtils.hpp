#include "OffsetPtr.hpp"

template<typename T>
constexpr auto* AsAddress(T&& aData) {
    if constexpr (std::is_pointer_v<std::remove_cvref_t<T>>)
        return aData;
    else
        return std::addressof(aData);
}

template<typename T>
struct NativeInfo;

namespace Detail
{
// Determine whether ABI will use RVO for this type.
template<typename T>
concept WillRVO = !std::is_void_v<T> && (sizeof(T) > 8 || !std::is_trivially_copyable_v<T>) && !std::is_floating_point_v<T>;

template<typename TOwner, typename TFunc>
struct NativeMemberFunc;

template<typename TOwner, typename TRet, typename... TArgs>
struct NativeMemberFunc<TOwner, TRet(TArgs...)> {
    static constexpr bool HasRVO = WillRVO<TRet>;

    using ReturnType = TRet;

    using OwnerType = TOwner;

    using ArgsTuple = std::tuple<TArgs...>;

    template<size_t I> 
    using ArgType = std::tuple_element<I, ArgsTuple>::type;
    // MSVC's pointer to member is a non-standard fat pointer that -given circumstances-
    // are error prone and difficult to manipulate. So instead we just fake it.
    // This however means we need to account for RVO manually because the compiler may
    // fuck up argument registers otherwise.
    using PtrType = std::conditional_t<
        HasRVO, 
        void(*)(TOwner*, TRet*, TArgs...), 
        TRet(*)(TOwner*, TArgs...)
    >;
};

template<typename TOwner, typename TRet, typename... TArgs>
struct NativeMemberFunc<TOwner, TRet(TArgs...) const> : NativeMemberFunc<TOwner, TRet(TArgs...)> {
    using NativeMemberFunc<TOwner, TRet(TArgs...)>::HasRVO;

    using OwnerType = const TOwner;

    using PtrType = std::conditional_t<
        HasRVO,
        void(*)(const TOwner*, TRet*, TArgs...),
        TRet(*)(const TOwner*, TArgs...)
    >;
};
}

template<typename T>
using NativeInfoOf = NativeInfo<std::remove_pointer_t<std::remove_cvref_t<T>>>;

#define NATIVE_INFO_BEGIN(_owner, ...)                                           \
    template<> struct NativeInfo<_owner> __VA_OPT__(: NativeInfo<__VA_ARGS__>) { \
        using OwnerType = _owner;                     

#define NATIVE_MEMBER_FN(_type, _name, _hash) \
    struct _name : Detail::NativeMemberFunc<OwnerType, _type> { \
        static constexpr uint32_t Hash = _hash; \
        static constexpr const char* Name = #_name; \
        static inline const uintptr_t Addr{ RED4ext::UniversalRelocBase::Resolve(Hash) }; \
        template<typename... TArgs> \
        _name(TArgs&&... aArgs) : boundArgs(std::forward<TArgs>(aArgs)...) {} \
        template<typename... TArgs> \
        static ReturnType Call(OwnerType* aInstance, TArgs&&... aArgs) { \
            auto func = reinterpret_cast<PtrType>(Addr); \
            if constexpr (HasRVO) { \
                ReturnType result; \
                func(aInstance, &result, std::forward<TArgs>(aArgs)...); \
                return result; \
            } \
            else { \
                return func(aInstance, std::forward<TArgs>(aArgs)...); \
            } \
        } \
        ReturnType Invoke(OwnerType* aInstance) { \
            return std::apply([aInstance](auto&&... aArgs) { \
                return Call(aInstance, std::forward<decltype(aArgs)>(aArgs)...); \
            }, boundArgs); \
        } \
        ArgsTuple boundArgs; \
    };


#define NATIVE_VIRTUAL_FN(_type, _name, _offset) \
    struct _name : Detail::NativeMemberFunc<OwnerType, _type> { \
        static constexpr const char* Name = #_name; \
        template<typename... TArgs> \
        _name(TArgs&&... aArgs) : boundArgs(std::forward<TArgs>(aArgs)...) {} \
        template<typename... TArgs> \
        static ReturnType Call(OwnerType* aInstance, TArgs&&... aArgs) { \
            auto vftable = *reinterpret_cast<void***>(aInstance); \
            auto func = *OffsetPtr<PtrType, _offset>(vftable); \
            if constexpr (HasRVO) { \
                ReturnType result; \
                func(aInstance, &result, std::forward<TArgs>(aArgs)...); \
                return result; \
            } \
            else { \
                return func(aInstance, std::forward<TArgs>(aArgs)...); \
            } \
        } \
        ReturnType Invoke(OwnerType* aInstance) { \
            return std::apply([aInstance](auto&&... aArgs) { \
                return Call(aInstance, std::forward<decltype(aArgs)>(aArgs)...); \
            }, boundArgs); \
        } \
        ArgsTuple boundArgs; \
    };

#define NATIVE_FIELD(_type, _name, _offset)                              \
    static inline _type& Get_##_name(OwnerType* aInstance) {             \
        return *OffsetPtr<_type, _offset>(aInstance);                    \
    }                                                                    \
    static inline const _type& Get_##_name(const OwnerType* aInstance) { \
        return *OffsetPtr<const _type, _offset>(aInstance);              \
    }  

#define NATIVE_INFO_END() };

#define NATIVE_WRAP_ALIAS(_derived, _base)                         \
    struct _derived;                                               \
    template<> struct NativeInfo<_derived> : NativeInfo<_base> {};

#define NATIVE_GET(_instance, _field_name) \
    NativeInfoOf<decltype(_instance)>::Get_##_field_name(AsAddress(_instance))

#define NATIVE_CALL(_instance, _func_ctor)                    \
    [](auto&& func, auto* inst){ return func.Invoke(inst); }( \
        NativeInfoOf<decltype(_instance)>::_func_ctor,        \
        AsAddress(_instance)                                  \
    )
