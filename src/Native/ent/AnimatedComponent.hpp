#pragma once

#include <RED4ext/Scripting/Natives/Generated/ent/AnimatedComponent.hpp>
#include <Native/anim/AnimatedObject.hpp>

namespace Native::ent::AnimatedComponent
{
using m_animSys = OffsetField<RED4ext::ent::AnimatedComponent, RED4ext::world::AnimationSystem*, 0x168>;
using m_animObj = OffsetField<RED4ext::ent::AnimatedComponent, RED4ext::anim::AnimatedObject*, 0x178>;
using m_rootAnimObjPart = OffsetField<RED4ext::ent::AnimatedComponent, RED4ext::UniquePtr<anim::AnimatedObjectPart>, 0x270>;
}
