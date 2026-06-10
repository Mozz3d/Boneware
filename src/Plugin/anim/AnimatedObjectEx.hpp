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

		if (auto* scriptProp = entityClass->GetProperty("poseAdditiveTransforms"))
		{
			if (auto* entries = scriptProp->GetValuePtr<RED4ext::DynArray<BoneTransformEntry>>(entity))
			{
				RED4ext::DynArray<RED4ext::CName>& metaBoneNames = metaRig->boneNames;
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
	NATIVE_MID_DETOUR_FN(Update, 0x46E, UpdateEntityScriptedProperties);
};