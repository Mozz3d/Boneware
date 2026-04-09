#pragma once

#include <Native/ent/AnimatedComponent.hpp>

struct AnimatedComponentEx : RED4ext::ent::AnimatedComponent
{
    RED4ext::Handle<RED4ext::anim::Rig> GetRig()
    {
        return rig.Get();
    }

    void ForceReferencePose(bool aShouldForce)
    {
        Native::ent::AnimatedComponent::m_rootAnimObjPart(this)->forceReferencePose = aShouldForce;
    }

    RED4ext::DynArray<RED4ext::QsTransform> GetCurrentPoseTransforms()
    {
        auto animObj = Native::ent::AnimatedComponent::m_animObj(this);
        return Native::anim::AnimatedObject::m_metaPose(animObj)->m_transforms;
    }
};

RTTI_EXPAND_CLASS(RED4ext::ent::AnimatedComponent, AnimatedComponentEx,
{
    RTTI_METHOD(GetRig);
    RTTI_METHOD(ForceReferencePose);
    RTTI_METHOD(GetCurrentPoseTransforms);
});