#pragma once

#include <Native/anim/AnimatedObjectPart.hpp>
#include <Plugin/anim/MetaPose.hpp>
#include <Plugin/anim/MetaRig.hpp>

struct AnimatedObjectPartEx : Native::anim::AnimatedObjectPart
{
	void UpdateMetaPose_Detour(
		Native::anim::AnimatedObjectPartUpdateContext& aContext, 
		Native::anim::Pose& aPose, 
		uint32_t aDistanceCategory)
	{
		if (auto* scriptProp = component->GetType()->GetProperty("metaRigRef"))
		{
			if (auto* metaRigRef = scriptProp->GetValuePtr<MetaRigScriptRef>(component))
			{
				metaRigRef->ptr = aContext.metaRig;
			}
		}

		if (auto* scriptProp = component->GetType()->GetProperty("metaPoseRef"))
		{
			if (auto* metaPoseRef = scriptProp->GetValuePtr<MetaPoseScriptRef>(component))
			{
				metaPoseRef->ptr = aContext.metaPose;
			}
		}

		if (auto* scriptProp = component->GetType()->GetProperty("additiveTransforms"))
		{
			if (auto* entries = scriptProp->GetValuePtr<RED4ext::DynArray<AdditiveTransformEntry>>(component))
			{
				RED4ext::DynArray<RED4ext::CName>& metaBoneNames = aContext.metaRig->boneNames;
				for (const auto& entry : *entries)
				{
					auto it = metaBoneNames.Find(entry.name);
					if (it == metaBoneNames.End()) continue;
					uint32_t index = static_cast<uint32_t>(std::distance(metaBoneNames.Begin(), it));
					if (index >= aPose.numTransforms) continue;

					RED4ext::QsTransform& poseTransform = aPose.transforms[index];
					poseTransform.Translation += entry.transform.Translation;
					poseTransform.Rotation *= entry.transform.Rotation;
					poseTransform.Scale *= entry.transform.Scale;
				}
			}
		}
		NATIVE_CALL_ORIGINAL(this,UpdateMetaPose(aContext, aPose, aDistanceCategory));
	}
};

NATIVE_EXPAND(Native::anim::AnimatedObjectPart, AnimatedObjectPartEx)
{
	NATIVE_DETOUR_MEMBER_FN(UpdateMetaPose, UpdateMetaPose_Detour);
};