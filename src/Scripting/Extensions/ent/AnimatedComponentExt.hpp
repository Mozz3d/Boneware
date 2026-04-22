#pragma once

#include <Native/ent/AnimatedComponent.hpp>

NATIVE_WRAP_ALIAS(AnimatedComponentExt, RED4ext::ent::AnimatedComponent)

struct AnimatedComponentExt : RED4ext::ent::AnimatedComponent
{
    RED4ext::Handle<RED4ext::anim::Rig> GetRig()
    {
        return rig.Get();
    }

    void ForceReferencePose(bool aShouldForce)
    {
        NATIVE_GET(this,m_rootAnimObjPart)->forceReferencePose = aShouldForce;
    }

    RED4ext::DynArray<RED4ext::QsTransform> GetCurrentPoseTransforms()
    {
        return NATIVE_GET(NATIVE_GET(this,m_animObj),m_metaPose)->m_transforms;
    }

    RED4ext::DynArray<float> GetCurrentPoseTracks()
    {
        return NATIVE_GET(NATIVE_GET(this,m_animObj),m_metaPose)->m_tracks;
    }
};

RTTI_EXPAND_CLASS(RED4ext::ent::AnimatedComponent, AnimatedComponentExt,
{
    RTTI_METHOD(GetRig);
    RTTI_METHOD(ForceReferencePose);
    RTTI_METHOD(GetCurrentPoseTransforms);
    RTTI_METHOD(GetCurrentPoseTracks);
});
