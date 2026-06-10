#pragma once

#include <Native/ent/AnimatedComponent.hpp>
#include <Plugin/anim/MetaRig.hpp>
#include <Plugin/anim/MetaPose.hpp>

struct AnimatedComponentEx : RED4ext::ent::AnimatedComponent
{
    RED4ext::Handle<RED4ext::anim::Rig> GetRig()
    {
        return rig.Get();
    }

    void ForceReferencePose(bool aShouldForce)
    {
        NATIVE_GET(this,m_rootAnimObjPart)->forceReferencePose = aShouldForce;
    }
};

NATIVE_EXPAND(RED4ext::ent::AnimatedComponent, AnimatedComponentEx)
{
};

RTTI_EXPAND_CLASS(RED4ext::ent::AnimatedComponent, AnimatedComponentEx,
{
    RTTI_METHOD(GetRig);
    RTTI_METHOD(ForceReferencePose);
});
