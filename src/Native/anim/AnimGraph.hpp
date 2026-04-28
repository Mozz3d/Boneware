#pragma once

#include <RED4ext/Scripting/Natives/Generated/anim/AnimGraph.hpp>
#include <Native/anim/AnimInstanceBuffer.hpp>

NATIVE_INFO(RED4ext::anim::AnimGraph)
{
	NATIVE_MEMBER_FN(void(Native::anim::AnimInstanceBuffer&, bool), ResetFeatures, 248715065)
};
