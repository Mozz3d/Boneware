#pragma once

#include <Native/ent/IComponent.hpp>
#include <Native/anim/AnimatedObject.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/AnimatedComponent.hpp>

NATIVE_INFO(RED4ext::ent::AnimatedComponent)
{
	NATIVE_MEMBER_FUNC(
	void ,OnInitialize,(ntv::ent::ComponentInitializeContext&), 1712659627);

	NATIVE_MEMBER_FUNC(
	void ,OnAttach,(ntv::ent::ComponentAttachContext&),         2005539121);

	NATIVE_DATA_MEMBER(
	r4e::world::AnimationSystem* ,m_animSys, 0x168);

	NATIVE_DATA_MEMBER(
	r4e::anim::AnimatedObject*   ,m_animObj, 0x178);

	NATIVE_DATA_MEMBER(
	r4e::WeakHandle<r4e::ent::AnimatedComponent>  ,m_parentAnimComp,  0x240);

	NATIVE_DATA_MEMBER(
	r4e::WeakHandle<r4e::ent::AnimatedComponent>  ,m_rootAnimComp,	  0x250);

	NATIVE_DATA_MEMBER(
	r4e::UniquePtr<ntv::anim::AnimatedObjectPart> ,m_rootAnimObjPart, 0x270);
};
