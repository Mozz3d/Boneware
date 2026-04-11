#include "OffsetPtr.hpp"

template<typename TOwner>
struct NativeUtils;

template<typename TOwner, typename TFunc>
struct AsMethod;

template<typename TOwner, typename TRet, typename... TArgs>
struct AsMethod<TOwner, TRet(TArgs...)> {
    using Type = TRet(*)(TOwner*, TArgs...);
};

template<typename TOwner, typename TRet, typename... TArgs>
struct AsMethod<TOwner, TRet(TArgs...) const> {
    using Type = TRet(*)(const TOwner*, TArgs...);
};

#define NATIVE_UTILS_BEGIN(_owner) \
    template<> struct NativeUtils<_owner> { \
    using OwnerType = _owner;

#define NATIVE_UTILS_FIELD(_type, _name, _offset) \
    using offset_##_name##_t = OffsetField<OwnerType, _type, _offset>;

#define NATIVE_UTILS_METHOD(_type, _name, _hash) \
    static inline const RED4ext::UniversalRelocFunc<AsMethod<OwnerType, _type>::Type> _name{_hash};

#define NATIVE_UTILS_END() };

#define NATIVE_UTILS_ALIAS(_derived, _base) \
    struct _derived; \
    template<> struct NativeUtils<_derived> : NativeUtils<_base> {};

#define NATIVE_FIELD(_instance, _name) \
    NativeUtils<std::remove_pointer_t<decltype(_instance)>>::offset_##_name##_t(_instance)

#define NATIVE_METHOD_CALL(_instance, _name, ...) \
    NativeUtils<std::remove_pointer_t<decltype(_instance)>>::_name(_instance, ##__VA_ARGS__)
