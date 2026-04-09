#pragma once

#include <RED4ext/Scripting/Natives/animAnimatedObject.hpp>

#include <Native/anim/MetaRig.hpp>
#include <Native/anim/MetaPose.hpp>
#include <Native/anim/AnimatedObjectPart.hpp>

namespace Native::anim::AnimatedObject
{
using m_metaRigReference = OffsetField<RED4ext::anim::AnimatedObject, Native::anim::MetaRigReference, 0x00>;
using m_metaPose = OffsetField<RED4ext::anim::AnimatedObject, RED4ext::UniquePtr<Native::anim::MetaPose>, 0x18>;
}