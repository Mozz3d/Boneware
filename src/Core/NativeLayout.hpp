#include "OffsetPtr.hpp"

template<typename T>
struct NativeLayout;

#define NATIVE_LAYOUT_BEGIN(aOwnerType) \
    template<> struct NativeLayout<aOwnerType> { \
    using OwnerType = aOwnerType;

#define NATIVE_LAYOUT_FIELD(aType, aName, aOffset) \
    using OFFSET_FIELD_##aName = OffsetField<OwnerType, aType, aOffset>;

#define NATIVE_LAYOUT_END() };

#define NATIVE_LAYOUT_ALIAS(aDerivedType, aBaseType) \
    template<> struct NativeLayout<aDerivedType> : NativeLayout<aBaseType> {};

#define NATIVE_FIELD(aInstance, aName) \
    NativeLayout<std::remove_pointer_t<decltype(aInstance)>>::OFFSET_FIELD_##aName(aInstance)
