#pragma once

#include <Native/anim/AnimatedObject.hpp>
#include <Plugin/anim/MetaPose.hpp>
#include <Plugin/anim/MetaRig.hpp>

struct AnimatedObjectEx : RED4ext::anim::AnimatedObject
{
	static void ApplyScriptedAdditivetransforms(NativeMidFuncContext& ctx)
	{
		auto* animatedObj = ctx.RBX<RED4ext::anim::AnimatedObject*>();
		auto* updateCtx   = ctx.RSI<Native::anim::AnimatedObjectUpdateContext*>();
		auto* metaPose	  = ctx.R13<Native::anim::MetaPose*>();

		auto* entity = updateCtx->entity;

		if (auto* scriptProp = entity->GetType()->GetProperty("metaRigRef"))
		{
			if (auto* metaRigRef = scriptProp->GetValuePtr<MetaRigScriptRef>(entity))
			{
				metaRigRef->ptr = NATIVE_GET(animatedObj,m_metaRigRef).m_metaRig;
			}
		}

		if (auto* scriptProp = entity->GetType()->GetProperty("metaPoseRef"))
		{
			if (auto* metaPoseRef = scriptProp->GetValuePtr<MetaPoseScriptRef>(entity))
			{
				metaPoseRef->ptr = NATIVE_GET(animatedObj,m_metaPose);
			}
		}

		if (auto* scriptProp = entity->GetType()->GetProperty("additiveTransforms"))
		{
			if (auto* entries = scriptProp->GetValuePtr<RED4ext::DynArray<AdditiveTransformEntry>>(entity))
			{
				RED4ext::DynArray<RED4ext::CName>& metaBoneNames = NATIVE_GET(animatedObj,m_metaRigRef).m_metaRig->boneNames;
				RED4ext::DynArray<RED4ext::QsTransform>& poseTransforms = metaPose->m_transforms;
				for (const auto& entry : *entries)
				{
					auto it = metaBoneNames.Find(entry.name);
					if (it == metaBoneNames.End()) continue;
					uint32_t index = static_cast<uint32_t>(std::distance(metaBoneNames.Begin(), it));
					if (index >= metaPose->m_numBones) continue;

					RED4ext::QsTransform& poseTransform = poseTransforms[index];
					poseTransform.Translation += entry.transform.Translation;
					poseTransform.Rotation	  *= entry.transform.Rotation;
					poseTransform.Scale		  *= entry.transform.Scale;
				}
			}
		}
	}
};

NATIVE_EXPAND(RED4ext::anim::AnimatedObject, AnimatedObjectEx)
{
	NATIVE_MID_DETOUR_FN(Update, 0x46E, ApplyScriptedAdditivetransforms);
};