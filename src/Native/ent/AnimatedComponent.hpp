#pragma once

#include <RED4ext/Scripting/Natives/Generated/ent/AnimatedComponent.hpp>
#include <Native/anim/AnimatedObject.hpp>

NATIVE_UTILS_BEGIN(RED4ext::ent::AnimatedComponent)
	NATIVE_UTILS_FIELD(RED4ext::world::AnimationSystem*, m_animSys, 0x168)
	NATIVE_UTILS_FIELD(RED4ext::anim::AnimatedObject*, m_animObj, 0x178)
	NATIVE_UTILS_FIELD(RED4ext::UniquePtr<Native::anim::AnimatedObjectPart>, m_rootAnimObjPart, 0x270)
NATIVE_UTILS_END()
