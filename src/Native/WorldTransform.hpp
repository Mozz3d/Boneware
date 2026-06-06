#pragma once

#include <RED4ext/Scripting/Natives/Generated/WorldTransform.hpp>
#include <RED4ext/Scripting/Natives/Box.hpp>

NATIVE_INFO(RED4ext::WorldTransform)
{
	NATIVE_MEMBER_FN(RED4ext::Box, TransformBox,(RED4ext::Box&), 1761285048);
};
