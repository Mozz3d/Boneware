#pragma once

#include <RED4ext/Scripting/Natives/Generated/WorldTransform.hpp>
#include <RED4ext/Scripting/Natives/Generated/Transform.hpp>
#include <RED4ext/Scripting/Natives/Box.hpp>

NATIVE_INFO(r4e::WorldTransform)
{
	NATIVE_MEMBER_FUNC(
	r4e::Box ,TransformBox,(r4e::Box&), 1761285048);

	NATIVE_MEMBER_FUNC(
	r4e::WorldTransform,TransformXForm,(r4e::Transform const&) const, 462755596);
};
