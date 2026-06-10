#pragma once

#include <Native/anim/MetaRig.hpp>
#include <Native/ent/AnimatedComponent.hpp>

namespace Lib
{
	RED4ext::anim::MetaRig* GetMetaRig(const RED4ext::ent::AnimatedComponent* aAnimComp)
	{
		return NATIVE_GET(NATIVE_GET(aAnimComp,m_animObj),m_metaRigRef).m_metaRig;
	}
}