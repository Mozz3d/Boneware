#pragma once

#include <Native/ent/IComponent.hpp>
#include <Native/anim/AnimatedObject.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/AnimatedComponent.hpp>

NATIVE_INFO(RED4ext::ent::AnimatedComponent)
{
	NATIVE_MEMBER_FN(void, OnInitialize,(Native::ent::ComponentInitializeContext&), 1712659627);
	NATIVE_MEMBER_FN(void, OnAttach,(Native::ent::ComponentAttachContext&), 2005539121);
	NATIVE_FIELD(RED4ext::world::AnimationSystem*, m_animSys, 0x168);
	NATIVE_FIELD(RED4ext::anim::AnimatedObject*,   m_animObj, 0x178);
	NATIVE_FIELD(RED4ext::WeakHandle<RED4ext::ent::AnimatedComponent>, m_parentAnimComp,  0x240);
	NATIVE_FIELD(RED4ext::WeakHandle<RED4ext::ent::AnimatedComponent>, m_rootAnimComp,	  0x250);
	NATIVE_FIELD(RED4ext::UniquePtr<Native::anim::AnimatedObjectPart>, m_rootAnimObjPart, 0x270);
};
