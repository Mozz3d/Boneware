#pragma once

#include <RED4ext/Scripting/Natives/animAnimatedObject.hpp>

#include <Native/anim/MetaRig.hpp>
#include <Native/anim/MetaPose.hpp>
#include <Native/anim/AnimatedObjectPart.hpp>

NATIVE_UTILS_BEGIN(RED4ext::anim::AnimatedObject)
	NATIVE_UTILS_FIELD(Native::anim::MetaRigReference, m_metaRigRef, 0x00)
	NATIVE_UTILS_FIELD(RED4ext::UniquePtr<Native::anim::MetaPose>, m_metaPose, 0x18)
NATIVE_UTILS_END()
