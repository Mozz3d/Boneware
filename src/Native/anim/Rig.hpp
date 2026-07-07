#pragma

#include <RED4ext/Scripting/Natives/animRig.hpp>

NATIVE_INFO(RED4ext::anim::Rig)
{
	NATIVE_MEMBER_FUNC(
	r4e::Span<const r4e::QsTransform> ,GetAPoseLS,() const, 1932007550);

	NATIVE_MEMBER_FUNC(
	uint32_t ,RemapDistanceCategoryToSkeletalLOD,(uint32_t) const, 826348417);
};
