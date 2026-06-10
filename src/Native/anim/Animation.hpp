#pragma once

#include <RED4ext/Scripting/Natives/Generated/anim/Animation.hpp>
#include <Native/anim/Pose.hpp>

NATIVE_INFO(RED4ext::anim::Animation)
{
	NATIVE_MEMBER_FN(void, Sample,(float, Native::anim::Pose&) const, 1623265017);
};
