#pragma once

#include <Core/MacroUtils.hpp>
#include <Core/HookingUtils.hpp>
#include <Core/Plugin.hpp>

template<typename T>
struct NativeInfoBase {
    using OwnerType = T;
};

template<typename T>
struct NativeInfo;

template<typename T>
struct NativeInfo : std::conditional_t<
    std::derived_from<T, NativeInfoBase<T>>,
    T,
    NativeInfoBase<T>
>
{
};

template<typename TEx, typename TNative>
struct NativeExpansionBase {
    using ExType = TEx;
    using NativeType = TNative;
};

template<typename TExt, typename TNative>
struct NativeExpansion;

namespace Native {
    using OwnerType = void;
}

namespace Detail
{
    template<typename T>
    constexpr auto* AsTypePtr(T&& aData) {
        if constexpr (std::is_pointer_v<std::remove_cvref_t<T>>)
            return aData;
        else
            return std::addressof(aData);
    }

    template<typename T>
        requires std::derived_from<T, NativeInfoBase<T>>
    NativeInfo<T> NativeInfoFrom(T*);

    template<typename T>
        requires std::derived_from<T, NativeInfoBase<T>>
    NativeInfo<T> NativeInfoFrom(const T*);

    // Determine whether ABI will use return storage for this type.
    template<typename T>
    concept WillSRet = !std::is_void_v<T> 
        && !std::is_floating_point_v<T> 
        && (  !std::has_single_bit(sizeof(T)) 
           || sizeof(T) > 8 
           || !std::is_trivially_copyable_v<T>
        )
        && !( std::is_same_v<std::remove_cv_t<T>, __m128>
           || std::is_same_v<std::remove_cv_t<T>, __m128i>
           || std::is_same_v<std::remove_cv_t<T>, __m128d>
           || std::is_same_v<std::remove_cv_t<T>, __m256>
           || std::is_same_v<std::remove_cv_t<T>, __m256i>
           || std::is_same_v<std::remove_cv_t<T>, __m256d>
        );
}

template<typename TOwner, typename TRet, typename... TArgs>
struct NativeFuncBase
{
    static constexpr bool HasSRet = Detail::WillSRet<TRet>;

    using RetType = TRet;

    using ArgsTuple = std::tuple<TArgs...>;
    template<size_t I>
    using ArgType = std::tuple_element<I, ArgsTuple>::type;

    // MSVC's pointer to member is a non-standard fat pointer that -given circumstances-
    // are error prone and difficult to manipulate. So instead we just fake it.
    // This however means we need to account for sret manually because the compiler may
    // fuck up argument registers otherwise.
    using PtrType =
        std::conditional_t<std::is_void_v<TOwner>,
            std::conditional_t<HasSRet,
                void(*)(TRet*, TArgs...),
                TRet(*)(TArgs...)>,
            std::conditional_t<HasSRet,
                void(*)(TOwner*, TRet*, TArgs...),
                TRet(*)(TOwner*, TArgs...)>
        >;
};

template<typename TImpl, typename TOwner, typename TFunc>
struct NativeFunc;

template<typename TImpl, typename TOwner, typename TRet, typename... TArgs>
struct NativeFunc<TImpl, TOwner, TRet(TArgs...)> : NativeFuncBase<void, TRet, TArgs...>
{
    using Base = NativeFuncBase<void, TRet, TArgs...>;
    using Base::HasSRet;
    using OwnerType = TOwner;
    using typename Base::RetType;
    using typename Base::ArgsTuple;
    using typename Base::PtrType;
    template<size_t I>
    using ArgType = typename Base::template ArgType<I>;

protected:
    template<typename... UArgs>
    inline static RetType Invoke(const PtrType func, UArgs&&... aArgs)
    {
        if constexpr (HasSRet) {
            // FIXME
            // this is bad because it assumes RetType is default constructible (it may not be)
            // it also assumes RetType is trivially destructible, pray there's no situation where 
            // cleanup is critical, lest this leak
            RetType __return_storage__;
            func(&__return_storage__, std::forward<UArgs>(aArgs)...);
            return __return_storage__;
        }
        else
            return func(std::forward<UArgs>(aArgs)...);
    }
public:
    template<typename... UArgs>
    NativeFunc(UArgs&&... aArgs) : boundArgs(std::forward<UArgs>(aArgs)...) {}

    template<typename... UArgs>
    inline static RetType Call(UArgs&&... aArgs)
    {
        return Invoke(TImpl::Get(), std::forward<UArgs>(aArgs)...);
    }

    inline RetType BoundCall(OwnerType* _ = nullptr)&&
    {
        return std::apply([](auto&&... aArgs) {
            return Call(std::forward<decltype(aArgs)>(aArgs)...);
            }, std::move(boundArgs));
    }

    ArgsTuple boundArgs;
};

template<typename TOwner, typename TRet, typename... TArgs>
struct NativeMemberFuncBase : NativeFuncBase<TOwner, TRet, TArgs...>
{
    using Base = NativeFuncBase<TOwner, TRet, TArgs...>;
    using Base::HasSRet;
    using OwnerType = TOwner;
    using typename Base::RetType;
    using typename Base::ArgsTuple;
    using typename Base::PtrType;
    template<size_t I>
    using ArgType = typename Base::template ArgType<I>;
protected:
    template<typename... UArgs>
    inline static RetType Invoke(const PtrType func, OwnerType* aInstance, UArgs&&... aArgs)
    {
        if constexpr (HasSRet) {
            RetType __return_storage__;
            func(aInstance, &__return_storage__, std::forward<UArgs>(aArgs)...);
            return __return_storage__;
        }
        else
            return func(aInstance, std::forward<UArgs>(aArgs)...);
    }
};

template<typename TImpl, typename TOwner, typename TFunc>
struct NativeMemberFunc;

template<typename TImpl, typename TOwner, typename TRet, typename... TArgs>
struct NativeMemberFunc<TImpl, TOwner, TRet(TArgs...)> : NativeMemberFuncBase<TOwner, TRet, TArgs...>
{
    using Base = NativeMemberFuncBase<TOwner, TRet, TArgs...>;
    using Base::HasSRet;
    using typename Base::OwnerType;
    using typename Base::RetType;
    using typename Base::ArgsTuple;
    using typename Base::PtrType;
    template<size_t I>
    using ArgType = typename Base::template ArgType<I>;
protected:
    using Base::Invoke;
public:
    template<typename... UArgs>
    requires std::is_constructible_v<ArgsTuple, UArgs...>
    NativeMemberFunc(UArgs&&... aArgs) : boundArgs(std::forward<UArgs>(aArgs)...) {}

    template<typename... UArgs>
    inline static RetType Call(OwnerType* aInstance, UArgs&&... aArgs)
    {
        return Invoke(TImpl::Get(aInstance), aInstance, std::forward<UArgs>(aArgs)...);
    }

    inline RetType BoundCall(OwnerType* aInstance)&&
    {
        return std::apply([aInstance](auto&&... aArgs) {
            return Call(aInstance, std::forward<decltype(aArgs)>(aArgs)...);
            }, std::move(boundArgs));
    }

    ArgsTuple boundArgs;
};

// const member function
template<typename TImpl, typename TOwner, typename TRet, typename... TArgs>
struct NativeMemberFunc<TImpl, TOwner, TRet(TArgs...) const> : NativeMemberFuncBase<const TOwner, TRet, TArgs...>
{
    using Base = NativeMemberFuncBase<const TOwner, TRet, TArgs...>;
    using Base::HasSRet;
    using typename Base::OwnerType;
    using typename Base::RetType;
    using typename Base::ArgsTuple;
    using typename Base::PtrType;
    template<size_t I>
    using ArgType = typename Base::template ArgType<I>;
protected:
    using Base::Invoke;
public:
    template<typename... UArgs>
    requires std::is_constructible_v<ArgsTuple, UArgs...>
    NativeMemberFunc(UArgs&&... aArgs) : boundArgs(std::forward<UArgs>(aArgs)...) {}

    template<typename... UArgs>
    inline static RetType Call(OwnerType* aInstance, UArgs&&... aArgs)
    {
        return Invoke(TImpl::Get(aInstance), aInstance, std::forward<UArgs>(aArgs)...);
    }

    inline RetType BoundCall(OwnerType* aInstance)&&
    {
        return std::apply([aInstance](auto&&... aArgs) {
            return Call(aInstance, std::forward<decltype(aArgs)>(aArgs)...);
            }, std::move(boundArgs));
    }

    ArgsTuple boundArgs;
};


#define NATIVE_INFO(_owner, ...) \
    namespace Detail \
    { \
        NativeInfo<_owner> NativeInfoFrom(_owner*); \
        NativeInfo<_owner> NativeInfoFrom(const _owner*); \
    } \
    template<> struct NativeInfo<_owner> \
        : __VA_OPT__(NativeInfo<__VA_ARGS__>,) NativeInfoBase<_owner>             

#define NTV_INFO(_owner, ...) NATIVE_INFO(_owner, __VA_ARGS__)

#define NATIVE_NAMESPACE(_namespace) \
    namespace Native::_namespace { using OwnerType = void; } \
    namespace Native::_namespace

// maybe shouldnt use this
#define NATIVE_TYPE(_type_def) _type_def : NativeInfoBase<_type_def>

#define NATIVE_FUNC(_ret, _name, _params, _hash) \
    static_assert(std::is_void_v<OwnerType>, \
    "NATIVE_FN is for globals. Use NATIVE_STATIC_FN for classes instead"); \
    struct _name : NativeFunc<_name, void, _ret _params> { \
        using NativeFunc::NativeFunc; \
        static constexpr const char* Name = #_name; \
        static constexpr uint32_t Hash = _hash; \
        inline static const uintptr_t Address{ RED4ext::UniversalRelocBase::Resolve(Hash) }; \
        inline static bool HasHook = false; \
        inline static PtrType Original = nullptr; \
        static const PtrType Get() { return std::bit_cast<const PtrType>(Address); } \
        template<typename... UArgs> \
        inline static RetType CallOriginal(UArgs&&... aArgs) { \
            return Invoke(Original, std::forward<UArgs>(aArgs)...); \
        } \
        inline RetType BoundCallOriginal() && { \
            return std::apply([](auto&&... aArgs) { \
                return CallOriginal(std::forward<decltype(aArgs)>(aArgs)...); \
            }, std::move(boundArgs)); \
        } \
    } 

#define NTV_FUNC(_ret, _name, _params, _hash) NATIVE_FUNC(_ret, _name, _params, _hash)

#define NATIVE_GLOBAL_FUNC(_ret, _name, _params, _hash) \
    namespace Native { struct _name; } \
    struct Native::_name : NativeFunc<_name, void, _ret _params> { \
        using NativeFunc::NativeFunc; \
        static constexpr const char* Name = #_name; \
        static constexpr uint32_t Hash = _hash; \
        inline static const uintptr_t Address{ RED4ext::UniversalRelocBase::Resolve(Hash) }; \
        inline static bool HasHook = false; \
        inline static PtrType Original = nullptr; \
        static const PtrType Get() { return std::bit_cast<const PtrType>(Address); } \
        template<typename... UArgs> \
        inline static RetType CallOriginal(UArgs&&... aArgs) { \
            return Invoke(Original, std::forward<UArgs>(aArgs)...); \
        } \
        inline RetType BoundCallOriginal()&& { \
            return std::apply([](auto&&... aArgs) { \
                return CallOriginal(std::forward<decltype(aArgs)>(aArgs)...); \
            }, std::move(boundArgs)); \
        } \
    }

#define NATIVE_STATIC_FUNC(_ret, _name, _params, _hash) \
    struct _name : NativeFunc<_name, OwnerType, _ret _params> { \
        using NativeFunc::NativeFunc; \
        static constexpr const char* Name = #_name; \
        static constexpr uint32_t Hash = _hash; \
        inline static const uintptr_t Address{ RED4ext::UniversalRelocBase::Resolve(Hash) }; \
        inline static bool HasHook = false; \
        inline static PtrType Original = nullptr; \
        static const PtrType Get() { return std::bit_cast<const PtrType>(Address); } \
        template<typename... UArgs> \
        inline static RetType CallOriginal(UArgs&&... aArgs) { \
            return Invoke(Original, std::forward<UArgs>(aArgs)...); \
        } \
        inline RetType BoundCallOriginal() && { \
            return std::apply([](auto&&... aArgs) { \
                return CallOriginal(std::forward<decltype(aArgs)>(aArgs)...); \
            }, std::move(boundArgs)); \
        } \
    }

#define NATIVE_MEMBER_FUNC(_ret, _name, _params, _hash) \
    struct _name : NativeMemberFunc<_name, OwnerType, _ret _params> { \
        using NativeMemberFunc::NativeMemberFunc; \
        static constexpr const char* Name = #_name; \
        static constexpr uint32_t Hash = _hash; \
        inline static const uintptr_t Address{ RED4ext::UniversalRelocBase::Resolve(Hash) }; \
        inline static bool HasHook = false; \
        inline static PtrType Original = nullptr; \
        static const PtrType Get(OwnerType*) { return std::bit_cast<const PtrType>(Address); } \
        template<typename... UArgs> \
        inline static RetType CallOriginal(OwnerType* aInstance, UArgs&&... aArgs) { \
            return Invoke(Original, aInstance, std::forward<UArgs>(aArgs)...); \
        } \
        inline RetType BoundCallOriginal(OwnerType* aInstance) && { \
            return std::apply([aInstance](auto&&... aArgs) { \
                return CallOriginal(aInstance, std::forward<decltype(aArgs)>(aArgs)...); \
            }, std::move(boundArgs)); \
        } \
    }

#define NTV_MBR_FUNC(_ret, _name, _params, _hash) NATIVE_MEMBER_FUNC(_ret, _name, _params, _hash)

#define NATIVE_VIRTUAL_FUNC(_ret, _name, _params, _offset) \
    struct _name : NativeMemberFunc<_name, OwnerType, _ret _params> { \
        using NativeMemberFunc::NativeMemberFunc; \
        static constexpr const char* Name = #_name; \
        static constexpr uint32_t Offset = _offset; \
        static const PtrType Get(OwnerType* aInstance) { \
            void* vftable = *std::bit_cast<void***>(aInstance); \
            return *OffsetPtr<const PtrType, Offset>(vftable); \
        } \
    }

#define NTV_VRT_FUNC(_ret, _name, _params, _offset) NATIVE_VIRTUAL_FUNC(_ret, _name, _params, _offset)

#define NATIVE_DATA_MEMBER(_type, _name, _offset) \
    struct _name { \
        using Type = _type; \
        static constexpr const char* Name = #_name; \
        static constexpr uint32_t Offset = _offset; \
        static Type& Get(OwnerType* aInstance) { \
            return *OffsetPtr<Type, Offset>(aInstance); \
        } \
        static const Type& Get(const OwnerType* aInstance) { \
            return *OffsetPtr<const Type, Offset>(aInstance); \
        } \
    }

#define NTV_DATA_MBR(_type, _name, _offset) NATIVE_DATA_MEMBER(_type, _name, _offset)

#define NATIVE_INFO_ALIAS(_derived, _base)                        \
    struct _derived;                                              \
    template<> struct NativeInfo<_derived> : NativeInfo<_base> {}

#define NATIVE_EXPAND(_native_type, _extension) \
    template<> struct NativeInfo<_extension> : NativeInfo<_native_type> {}; \
    template<> struct NativeExpansion<_extension, _native_type> \
        : NativeExpansionBase<_extension, _native_type>

#define NATIVE_DETOUR_MEMBER_FUNC(_fn_name, _detour) \
    inline static const bool _fn_name##_hook_registered = []() { \
        using FuncInfo = NativeInfo<NativeType>::_fn_name; \
        if (FuncInfo::HasHook) { \
            std::cerr << std::format("Duplicate hooks registered for {}\n", #_fn_name); \
            std::abort(); \
        } \
        FuncInfo::HasHook = Plugin::RegisterHook( \
            FuncInfo::Address, \
            pmf_cast<void*>(&ExType::_detour), \
            std::bit_cast<void**>(&FuncInfo::Original) \
        ); \
        return FuncInfo::HasHook; \
    }()

#define NATIVE_REPLACE_MEMBER_FUNC(_fn_name) \
    inline static const bool _fn_name##_hook_registered = []() { \
        using FuncInfo = NativeInfo<NativeType>::_fn_name; \
        if (FuncInfo::HasHook) { \
            std::cerr << std::format("Duplicate hooks registered for {}\n", #_fn_name); \
            std::abort(); \
        } \
        FuncInfo::HasHook = Plugin::RegisterHook(FuncInfo::Address, pmf_cast<void*>(&ExType::_fn_name)); \
        return FuncInfo::HasHook; \
    }()

using NativeMidFuncContext = MidHooking::MidContext;
#define NATIVE_MID_DETOUR_FUNC(_fn_name, _offset, _detour) \
    inline static const bool _detour##_mid_hook_registered = []() { \
        static_assert( \
            std::is_same_v<decltype(&ExType::_detour), void(*)(NativeMidFuncContext&)>, \
            "Mid detour '" #_detour "' must be: static void " #_detour "(NativeMidFuncContext&)" \
        ); \
        using FuncInfo = NativeInfo<NativeType>::_fn_name; \
        return ::MidHooking::InstallMidDetour( \
            FuncInfo::Address + (_offset), \
            pmf_cast<void*>(&ExType::_detour)); \
    }()


#define NATIVE_GET(_instance, _field_name) \
    decltype(::Detail::NativeInfoFrom(::Detail::AsTypePtr(_instance)))::_field_name::Get(::Detail::AsTypePtr(_instance))

#define NTV_GET(_instance, _field_name) NATIVE_GET(_instance, _field_name)


// ctor used for pretty syntax e.g. NATIVE_CALL( instance,Method(args) )
#define NATIVE_FREE_CALL(_qualified_func_ctor) \
    ::Native::_qualified_func_ctor.BoundCall()

#define NATIVE_MEMBER_CALL(_instance, _func_ctor) \
    decltype(::Detail::NativeInfoFrom(::Detail::AsTypePtr(_instance)))::_func_ctor.BoundCall(::Detail::AsTypePtr(_instance))

#define NATIVE_STATIC_CALL(_owner, _func_ctor) \
    ::NativeInfo<_owner>::_func_ctor.BoundCall()

#define NATIVE_CALL_SELECT(_1, _2, _macro, ...) _macro

#define NATIVE_CALL(...) \
    NATIVE_CALL_SELECT(__VA_ARGS__, NATIVE_MEMBER_CALL, NATIVE_FREE_CALL)(__VA_ARGS__)

#define NTV_CALL(...) NATIVE_CALL(__VA_ARGS__)

// for use with detours
#define NATIVE_CALL_ORIGINAL(_instance, _func_ctor) \
    decltype(::Detail::NativeInfoFrom(::Detail::AsTypePtr(_instance)))::_func_ctor.BoundCallOriginal(::Detail::AsTypePtr(_instance))

#define NTV_CALL_OG(_instance, _func_ctor) NATIVE_CALL_ORIGINAL(_instance, _func_ctor)

namespace ntv = Native;
