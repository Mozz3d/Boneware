#pragma once

#include <RED4ext/Scripting/Natives/animAnimatedObject.hpp>

#include <Native/anim/MetaRig.hpp>
#include <Native/anim/MetaPose.hpp>
#include <Native/anim/AnimatedObjectPart.hpp>

#include <RED4ext/Scripting/Natives/entEntity.hpp>

namespace Native::anim
{
struct AnimatedObjectUpdateContext
{
	uint8_t unk00[0xa8 - 0x00];
	RED4ext::ent::Entity* entity;
};
}

NATIVE_INFO(RED4ext::anim::AnimatedObject)
{
	NATIVE_MEMBER_FN(void, Update,(Native::anim::AnimatedObjectUpdateContext&), 2251364700);
	NATIVE_FIELD(Native::anim::MetaRigReference, m_metaRigRef, 0x00);
	NATIVE_FIELD(RED4ext::UniquePtr<Native::anim::MetaPose>, m_metaPose, 0x18);
};
