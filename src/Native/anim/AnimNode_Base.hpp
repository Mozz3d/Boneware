#pragma once

#include <RED4ext/Scripting/Natives/Generated/anim/AnimNode_Base.hpp>

#include <Native/anim/AnimInstanceBufferCompiler.hpp>

NATIVE_INFO(RED4ext::anim::AnimNode_Base)
{
	NATIVE_VIRTUAL_FN(void, OnBuildDataLayout,(Native::anim::AnimInstanceBufferCompiler&), 0xe0);
};