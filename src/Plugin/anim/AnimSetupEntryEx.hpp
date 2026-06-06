#pragma once

#include <RED4ext/Scripting/Natives/Generated/anim/AnimSetupEntry.hpp>
#include <RED4ext/Scripting/Natives/Generated/anim/AnimSet.hpp>

struct AnimSetupEntryEx : RED4ext::anim::AnimSetupEntry
{
	RED4ext::Handle<RED4ext::anim::AnimSet> GetAnimSet()
	{
		return animSet.Resolve().Fetch();
	}
};

RTTI_EXPAND_CLASS(RED4ext::anim::AnimSetupEntry, AnimSetupEntryEx,
	RTTI_METHOD(GetAnimSet);
);
