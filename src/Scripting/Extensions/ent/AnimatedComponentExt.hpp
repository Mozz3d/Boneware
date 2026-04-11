#pragma once

#include <Native/ent/AnimatedComponent.hpp>

NATIVE_UTILS_ALIAS(AnimatedComponentExt, RED4ext::ent::AnimatedComponent)

struct AnimatedComponentExt : RED4ext::ent::AnimatedComponent
{
    RED4ext::Handle<RED4ext::anim::Rig> GetRig()
    {
        return rig.Get();
    }

    void ForceReferencePose(bool aShouldForce)
    {
        NATIVE_FIELD(this,m_rootAnimObjPart)->forceReferencePose = aShouldForce;
    }

    RED4ext::DynArray<RED4ext::QsTransform> GetCurrentPoseTransforms()
    {
        RED4ext::anim::AnimatedObject* animObj = NATIVE_FIELD(this,m_animObj);
        return NATIVE_FIELD(animObj,m_metaPose)->m_transforms;
    }
};

RTTI_EXPAND_CLASS(RED4ext::ent::AnimatedComponent, AnimatedComponentExt,
{
    RTTI_METHOD(GetRig);
    RTTI_METHOD(ForceReferencePose);
    RTTI_METHOD(GetCurrentPoseTransforms);
});
