#pragma once

#include <RED4ext/Scripting/Natives/entEntity.hpp>
#include <ent/ISkinTargetComponent.hpp>

#include <Plugin/anim/MetaRig.hpp>
#include <Lib/AnimCompLib.hpp>

struct EntityEx : RED4ext::ent::Entity
{
	MetaRigScriptRef GetMetaRig()
	{
		if (auto* rootAnimComp = Red::Cast<RED4ext::ent::AnimatedComponent>(transformComponent))
		{
			return NATIVE_GET(NATIVE_GET(rootAnimComp,m_animObj),m_metaRigRef).m_metaRig;
		}
	}
};

RTTI_EXPAND_CLASS(RED4ext::ent::Entity, EntityEx,
	RTTI_METHOD(GetMetaRig);
);
