#pragma once

#include <Core/MacroUtils.hpp>
#include <Core/HookingUtils.hpp>
#include <Core/Plugin.hpp>

template<typename T>
struct NativeInfo;

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
    using RawType = std::remove_pointer_t<std::remove_cvref_t<T>>;

    template<typename T>
    struct NativeInfoBase {
        using OwnerType = T;
    };

    template<typename TEx, typename TNative>
    struct NativeExpansionBase {
        using ExType = TEx;
        using NativeType = TNative;
    };

    template<typename T>
    requires std::derived_from<T, NativeInfoBase<T>>
    NativeInfo<T> NativeInfoFrom(T*);

    template<typename T>
    requires std::derived_from<T, NativeInfoBase<T>>
    NativeInfo<T> NativeInfoFrom(const T*);

    // Determine whether ABI will use RVO for this type.
    template<typename T>
    concept WillRVO = !std::is_void_v<T> && (sizeof(T) > 8 || !std::is_trivially_copyable_v<T>) && !std::is_floating_point_v<T>;

    template<typename TOwner, typename TRet, typename... TArgs>
    struct NativeMemberFuncBase
    {
        static constexpr bool HasRVO = WillRVO<TRet>;

        using RetType = TRet;

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

    protected:
        template<typename... UArgs>
        inline static RetType Invoke(PtrType func, OwnerType* aInstance, UArgs&&... aArgs)
        {
            if constexpr (HasRVO) {
                // FIXME
                // this is bad because it assume RetType is default constructible (it may not be)
                RetType __return_storage__;
                func(aInstance, &__return_storage__, std::forward<UArgs>(aArgs)...);
                return std::move(__return_storage__);
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
        using typename Base::RetType;
        using typename Base::OwnerType;
        using typename Base::PtrType;
        using typename Base::ArgsTuple;
    protected:
        using Base::Invoke;
    public:
        template<typename... UArgs>
        NativeMemberFunc(UArgs&&... aArgs) : boundArgs(std::forward<UArgs>(aArgs)...) {}

        template<typename... UArgs>
        inline static RetType Call(OwnerType* aInstance, UArgs&&... aArgs)
        {
            return Invoke(TImpl::Get(aInstance), aInstance, std::forward<UArgs>(aArgs)...);
        }

        inline RetType BoundCall(OwnerType* aInstance) &&
        {
            return std::apply([aInstance](auto&&... aArgs) {
                return Call(aInstance, std::forward<decltype(aArgs)>(aArgs)...);
                }, std::move(boundArgs));
        }

        ArgsTuple boundArgs;
    };

    template<typename TImpl, typename TOwner, typename TRet, typename... TArgs>
    struct NativeMemberFunc<TImpl, TOwner, TRet(TArgs...) const> : NativeMemberFuncBase<const TOwner, TRet, TArgs...> 
    {
        using Base = NativeMemberFuncBase<const TOwner, TRet, TArgs...>;
        using typename Base::RetType;
        using typename Base::OwnerType;
        using typename Base::PtrType;
        using typename Base::ArgsTuple;
    protected:
        using Base::Invoke;
    public:
        template<typename... UArgs>
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
}

template<typename T>
struct NativeInfo : std::conditional_t<
    std::derived_from<T, Detail::NativeInfoBase<T>>,
    T,
    Detail::NativeInfoBase<T>
> {
};

template<typename TExt, typename TNative>
struct NativeExpansion;


#define NATIVE_INFO(_owner, ...) \
    namespace Detail \
    { \
        NativeInfo<_owner> NativeInfoFrom(_owner*); \
        NativeInfo<_owner> NativeInfoFrom(const _owner*); \
    } \
    template<> struct NativeInfo<_owner> \
        : __VA_OPT__(NativeInfo<__VA_ARGS__>,) Detail::NativeInfoBase<_owner>             

// maybe shouldnt use this
#define NATIVE_TYPE(_type_def) _type_def : Detail::NativeInfoBase<_type_def>

#define NATIVE_MEMBER_FN(_ret, _name, _params, _hash) \
    struct _name : Detail::NativeMemberFunc<_name, OwnerType, _ret _params> { \
        using NativeMemberFunc::NativeMemberFunc; \
        static constexpr const char* Name = #_name; \
        static constexpr uint32_t Hash = _hash; \
        inline static const uintptr_t Address{ RED4ext::UniversalRelocBase::Resolve(Hash) }; \
        inline static bool HasHook = false; \
        inline static PtrType Original = nullptr; \
        static PtrType Get(OwnerType*) { return reinterpret_cast<PtrType>(Address); } \
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

#define NATIVE_VIRTUAL_FN(_ret, _name, _params, _offset) \
    struct _name : Detail::NativeMemberFunc<_name, OwnerType, _ret _params> { \
        using NativeMemberFunc::NativeMemberFunc; \
        static constexpr const char* Name = #_name; \
        static constexpr uint32_t Offset = _offset; \
        static PtrType Get(OwnerType* aInstance) { \
            void* vftable = *reinterpret_cast<void***>(aInstance); \
            return *OffsetPtr<PtrType, Offset>(vftable); \
        } \
    }

#define NATIVE_FIELD(_type, _name, _offset) \
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

#define NATIVE_INFO_ALIAS(_derived, _base)                        \
    struct _derived;                                              \
    template<> struct NativeInfo<_derived> : NativeInfo<_base> {}

#define NATIVE_EXPAND(_native_type, _extension) \
    template<> struct NativeInfo<_extension> : NativeInfo<_native_type> {}; \
    template<> struct NativeExpansion<_extension, _native_type> \
        : Detail::NativeExpansionBase<_extension, _native_type>

#define NATIVE_DETOUR_MEMBER_FN(_name, _detour) \
    inline static const bool _name##_hook_registered = []() { \
        using FuncInfo = NativeInfo<NativeType>::_name; \
        if (FuncInfo::HasHook) { \
            std::cerr << std::format("Duplicate hooks registered for {}\n", #_name); \
            std::abort(); \
        } \
        FuncInfo::HasHook = Plugin::RegisterHook( \
            FuncInfo::Address, \
            pmf_cast<void*>(&ExType::_detour), \
            reinterpret_cast<void**>(&FuncInfo::Original) \
        ); \
        return FuncInfo::HasHook; \
    }()

#define NATIVE_REPLACE_MEMBER_FN(_name) \
    inline static const bool _name##_hook_registered = []() { \
        using FuncInfo = NativeInfo<NativeType>::_name; \
        if (FuncInfo::HasHook) { \
            std::cerr << std::format("Duplicate hooks registered for {}\n", #_name); \
            std::abort(); \
        } \
        FuncInfo::HasHook = Plugin::RegisterHook(FuncInfo::Address, pmf_cast<void*>(&ExType::_name)); \
        return FuncInfo::HasHook; \
    }()

using NativeMidFuncContext = MidHooking::MidContext;
#define NATIVE_MID_DETOUR_FN(_name, _offset, _detour) \
    inline static const bool _detour##_mid_hook_registered = []() { \
        static_assert( \
            std::is_same_v<decltype(&ExType::_detour), void(*)(NativeMidFuncContext&)>, \
            "Mid detour '" #_detour "' must be: static void " #_detour "(NativeMidFuncContext&)" \
        ); \
        using FuncInfo = NativeInfo<NativeType>::_name; \
        return ::MidHooking::InstallMidDetour( \
            FuncInfo::Address + (_offset), \
            reinterpret_cast<void*>(&ExType::_detour)); \
    }()




#define NATIVE_GET(_instance, _field_name) \
    decltype(::Detail::NativeInfoFrom(::Detail::AsTypePtr(_instance)))::_field_name::Get(::Detail::AsTypePtr(_instance))

// ctor used for pretty semantics e.g. NATIVE_CALL( instance,Method(args) )
#define NATIVE_CALL(_instance, _func_ctor) \
    decltype(::Detail::NativeInfoFrom(::Detail::AsTypePtr(_instance)))::_func_ctor.BoundCall(::Detail::AsTypePtr(_instance))

// for use with detours
#define NATIVE_CALL_ORIGINAL(_instance, _func_ctor) \
    decltype(::Detail::NativeInfoFrom(::Detail::AsTypePtr(_instance)))::_func_ctor.BoundCallOriginal(::Detail::AsTypePtr(_instance))
