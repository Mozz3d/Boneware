#pragma once

#include <Native/anim/AnimatedObject.hpp>
#include <Plugin/anim/MetaPose.hpp>
#include <Plugin/anim/MetaRig.hpp>

struct AnimatedObjectEx : RED4ext::anim::AnimatedObject
{
	static void UpdateEntityScriptedProperties(NativeMidFuncContext& ctx)
	{
		auto* animatedObj = ctx.RBX<RED4ext::anim::AnimatedObject*>();
		auto* updateCtx   = ctx.RSI<Native::anim::AnimatedObjectUpdateContext*>();
		auto* metaPose	  = ctx.R13<Native::anim::MetaPose*>();
		RED4ext::anim::MetaRig* metaRig	= NATIVE_GET(animatedObj,m_metaRigRef).m_metaRig;

		RED4ext::ent::Entity* entity = updateCtx->entity;
		RED4ext::CClass* entityClass = entity->GetType();

		if (auto* scriptProp = entityClass->GetProperty("metaRigRef"))
		{
			if (auto* metaRigRef = scriptProp->GetValuePtr<MetaRigScriptRef>(entity))
			{
				metaRigRef->ptr = metaRig;
			}
		}

		if (auto* scriptProp = entityClass->GetProperty("metaPoseRef"))
		{
			if (auto* metaPoseRef = scriptProp->GetValuePtr<MetaPoseScriptRef>(entity))
			{
				metaPoseRef->ptr = metaPose;
			}
		}

		if (auto* scriptProp = entityClass->GetProperty("poseOverrideTransforms"))
		{
			if (auto* entries = scriptProp->GetValuePtr<RED4ext::DynArray<BoneTransformEntry>>(entity))
			{
				for (const auto& entry : *entries)
				{
					int32_t boneIdx = Lib::ArrayUtils::GetValueIndex(metaRig->boneNames, entry.name);
					if (boneIdx < 0 || boneIdx >= metaPose->m_numBones) continue;

					metaPose->m_transforms[boneIdx] = entry.transform;
				}
			}
		}

		if (auto* scriptProp = entityClass->GetProperty("poseAdditiveTransforms"))
		{
			if (auto* entries = scriptProp->GetValuePtr<RED4ext::DynArray<BoneTransformEntry>>(entity))
			{
				for (const auto& entry : *entries)
				{
					int32_t boneIdx = Lib::ArrayUtils::GetValueIndex(metaRig->boneNames, entry.name);
					if (boneIdx < 0 || boneIdx >= metaPose->m_numBones) continue;

					RED4ext::QsTransform& poseTransform = metaPose->m_transforms[boneIdx];
					poseTransform.Translation += entry.transform.Translation;
					poseTransform.Rotation	  *= entry.transform.Rotation;
					poseTransform.Scale		  *= entry.transform.Scale;
				}
			}
		}

		if (auto* scriptProp = entityClass->GetProperty("poseTrackOverrides"))
		{
			if (auto* entries = scriptProp->GetValuePtr<RED4ext::DynArray<TrackValueEntry>>(entity))
			{
				for (const auto& entry : *entries)
				{
					int32_t trackIdx = Lib::ArrayUtils::GetValueIndex(metaRig->trackNames, entry.name);
					if (trackIdx < 0 || trackIdx >= metaPose->m_numBones) continue;

					metaPose->m_tracks[trackIdx] = entry.value;
				}
			}
		}
	}
};

NATIVE_EXPAND(RED4ext::anim::AnimatedObject, AnimatedObjectEx)
{
	NATIVE_MID_DETOUR_FN(Update, 0x46E, UpdateEntityScriptedProperties);
};