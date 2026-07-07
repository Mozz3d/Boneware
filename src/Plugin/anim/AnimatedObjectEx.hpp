#pragma once

#include <Native/WorldTransform.hpp>

#include <Native/anim/AnimatedObject.hpp>
#include <Native/simd/QsTransform.hpp>
#include <Native/simd/QuadHelper.hpp>
#include <Plugin/anim/MetaPose.hpp>
#include <Plugin/anim/MetaRig.hpp>

struct AnimatedObjectEx : RED4ext::anim::AnimatedObject
{
    bool IsHierarchyDirty()
	{
		auto* part = NTV_GET(this,m_rootPart);
		while( part )
		{
			if ( part->m_isDirty )
			{
				return true;
			}
			part = part->m_child;
		}
		return false;
	}

	void Update(ntv::anim::AnimatedObjectUpdateContext& aUpdateCtx)
    {
        if ( IsHierarchyDirty() )
        {
			NTV_CALL(
			this,RebuildHierarchy(*aUpdateCtx.m_metaRigBank));

            aUpdateCtx.m_rebuiltHierarchy = true;

            if (aUpdateCtx.m_metaRigHeadIndex >= -1)
            {
				aUpdateCtx.m_metaRigHeadIndex = NTV_CALL(NTV_GET(this,m_metaRigRef).m_metaRig,FindBoneByName(0x351c13d86108cce3 /* "Head" */));
            }
        }

		const r4e::anim::MetaRig& _metaRig = *NTV_GET(this,m_metaRigRef).m_metaRig;

		NTV_CALL(
		this,UpdateDistanceCategory(aUpdateCtx.m_distanceTimeDelta));

		ntv::anim::MetaPose& metaPose = *NTV_GET(this,m_metaPose);
		uint32_t lodDistanceCategory = NTV_GET(this,m_distanceCategory);
		metaPose.m_numBones = NTV_GET(_metaRig,m_distanceCategoryNumBones)[lodDistanceCategory];
		metaPose.m_extraTransforms.Clear();
		metaPose.m_extraTracks.Clear();

		r4e::QsTransform	transformIdentity{ { 0.f, 0.f, 0.f, 0.f }, {}, { 1.f, 1.f, 1.f, 1.f } };
		r4e::QsTransform	partToParent;
		r4e::QsTransform	partToRoot;
		r4e::WorldTransform partToWorld;
		NTV_GET(this,unkEC) = 4;

		r4e::QsTransform& someUnkTransform = NTV_GET(this,m_unkTransform30);
		someUnkTransform = transformIdentity;

		ntv::anim::AnimatedObjectPart* rootPart = NTV_GET(this,m_rootPart);
		ntv::anim::AnimatedObjectPart* part = rootPart;
		uint32_t partIndex = 0;
		while ( part )
		{
			auto rigPoseLS = NTV_CALL(*part->m_rig,GetAPoseLS());
			NTV_CALL(
			metaPose,ResetPartTransforms(rigPoseLS, partIndex, _metaRig));

			part = part->m_child;
			partIndex++;
		}

		part = rootPart;
		partIndex = 0;
		while ( part )
		{
			bool isFacial = part->IsFacial();
			bool shouldSample = !aUpdateCtx.unkED || partIndex == 0 || isFacial;

			bool shouldUpdateFacial = !isFacial || 
									  (NTV_GET(this,unkE0) & 0x20) || 
									  !aUpdateCtx.unkEA || 
									  (NTV_GET(this,unk68) & 1);

			if ( shouldSample && !aUpdateCtx.m_forceUpdate && (isFacial || part->IsDeformation() || part->IsDangle()) )
			{
				uint32_t lod = NTV_CALL(
					*part->m_rig,RemapDistanceCategoryToSkeletalLOD(lodDistanceCategory));

				shouldSample = NTV_CALL(
					part,ShouldSample(lod));
			}

			if (shouldSample)
			{
				ntv::anim::AnimatedObjectPart* parentPart = part->m_parent;
				if ( parentPart
				  && parentPart->metaRigRootBoneIndex != -1
				  && part->metaRigRootBoneIndex != -1 
				)
				{
					r4e::QsTransform partMS = NTV_CALL(
						metaPose,GetBoneMSTransform(_metaRig, part->metaRigRootBoneIndex));

					r4e::QsTransform parentMS = NTV_CALL(
						metaPose,GetBoneMSTransform(_metaRig, parentPart->metaRigRootBoneIndex));

					NTV_CALL(
					partToParent,SetMulInverseMulUnsafe(parentMS, partMS));

					NTV_CALL(
					partToRoot,SetMulUnsafe(parentPart->localToRoot, partToParent));
					
					auto noramlizedRot = NTV_CALL(
						simd::QuadHelper::Normalize4(*reinterpret_cast<__m128*>(&partToParent.Rotation)));

					r4e::Transform transform = {
						partToParent.Translation,
						*reinterpret_cast<r4e::Quaternion*>(&noramlizedRot)
					};
					transform.position.W = 0.f;

					partToWorld = NTV_CALL(
						parentPart->localToWorld,TransformXForm(transform));
				}
				else
				{
					partToParent = transformIdentity;
					partToRoot   = transformIdentity;
					partToWorld  = aUpdateCtx.m_localToWorld;
				}

				if ( shouldUpdateFacial || aUpdateCtx.m_forceUpdate )
				{
					alignas(16) uint8_t unkStruct[0x310]{};

					if ( partIndex != 0 && part->m_updateSkipped )
					{
						NTV_CALL(
						part,CopyInputsFrom(*rootPart));
						part->m_updateSkipped = false;
					}

					void* sharedData = part->unkSharedPtr2590.GetPtr();
					bool shouldCleanStreaming = sharedData && *OffsetPtr<uint32_t,0xBC>(sharedData) != 0;

					if ( NTV_CALL(part,UpdateInputs(*part)) )
					{
						aUpdateCtx.unkD4 = false;
					}

					if ( shouldCleanStreaming || NTV_GET(this,m_hasDirtyStreamingContexts) )
					{
						NTV_CALL(
						part->m_dataContext,CleanStreamingContexts(
							r4e::Span(NTV_GET(this,m_streamingContexts).Data(), NTV_GET(this,m_streamingContexts).Size()),
							r4e::Span(NTV_GET(this,m_dirtyStreamingContexts).Data(), NTV_GET(this,m_dirtyStreamingContexts).Size())
						));
					}

					r4e::QsTransform someTransform = transformIdentity;

					ntv::anim::AnimatedObjectPartUpdateContext partUpdateCtx{};
					partUpdateCtx.unk00 = &someTransform;
					partUpdateCtx.unk08 = aUpdateCtx.unk20;
					partUpdateCtx.partToParent = &partToParent;
					partUpdateCtx.partToRoot = &partToRoot;
					partUpdateCtx.partToWorld = &partToWorld;
					partUpdateCtx.metaRig = &_metaRig;
					partUpdateCtx.unk30 = &NTV_GET(_metaRig,unkStructArray)[partIndex];
					partUpdateCtx.metaPose = &metaPose;
					partUpdateCtx.unkStructPtr40 = unkStruct;
					partUpdateCtx.globalTimeMs = aUpdateCtx.unk38;
					partUpdateCtx.unk50 = aUpdateCtx.unk40;
					partUpdateCtx.unk54 = aUpdateCtx.m_distanceTimeDelta;
					partUpdateCtx.globalTimeS = aUpdateCtx.unk48;
					partUpdateCtx.unk60 = aUpdateCtx.unk70;
					partUpdateCtx.unk68 = aUpdateCtx.unk28;
					partUpdateCtx.unk70 = aUpdateCtx.unk88;
					partUpdateCtx.unk78 = aUpdateCtx.unk90;
					partUpdateCtx.unk80 = aUpdateCtx.unk98;
					partUpdateCtx.animatedObject = aUpdateCtx.m_animatedObject;
					partUpdateCtx.unk90 = aUpdateCtx.unk78;
					partUpdateCtx.unk98 = &NTV_GET(this,unk70);
					partUpdateCtx.unkA0 = aUpdateCtx.unkB0;
					partUpdateCtx.unkA8 = aUpdateCtx.unkB8;
					partUpdateCtx.shouldSampleGraph = aUpdateCtx.m_shouldSampleGraph;
					partUpdateCtx.entity = aUpdateCtx.m_entity;
					partUpdateCtx.distanceCategory = NTV_GET(this,m_distanceCategory);
					partUpdateCtx.unkC4 = NTV_GET(this,unkA0);
					partUpdateCtx.unkC8 = NTV_GET(this,unkE8);
					partUpdateCtx.unkCC = aUpdateCtx.unkEE;
					partUpdateCtx.unkD0 = aUpdateCtx.unkC0;
					partUpdateCtx.unkD8 = aUpdateCtx.unkC8;
					partUpdateCtx.unkE0 = 0;
					partUpdateCtx.unkE8 = &aUpdateCtx.unkD0;
					partUpdateCtx.unkF0 = &aUpdateCtx.unkD4;
					partUpdateCtx.unkF8 = aUpdateCtx.unkD5;
					partUpdateCtx.unk100 = &NTV_GET(this,unkEC);
					partUpdateCtx.unk108 = &aUpdateCtx.unkD8;
					partUpdateCtx.unk110 = &aUpdateCtx.unkE0;
					partUpdateCtx.unk118 = &aUpdateCtx.unkE4;
					partUpdateCtx.unk120 = &aUpdateCtx.unkEC;

					if ( shouldUpdateFacial )
					{
						NTV_CALL(
						part,Update(partUpdateCtx));
					}

					NTV_CALL(
					someUnkTransform,SetMulUnsafe(someUnkTransform, someTransform));
				}
				else
				{
					part->m_updateSkipped = true;
				}
			}
			else
			{
				part->m_updateSkipped = true;
				part->unk25A0 = 2;
			}

			part = part->m_child;
			partIndex++;
		}

		if ( aUpdateCtx.m_shouldSampleGraph )
		{
			NTV_CALL(
			metaPose,CalcMS(_metaRig));
		}

		if ( NTV_GET(this,m_hasDirtyStreamingContexts) )
		{
			NTV_GET(this,m_dirtyStreamingContexts).Clear();
			NTV_GET(this,m_hasDirtyStreamingContexts) = false;
		}
    }
};

NATIVE_EXPAND(r4e::anim::AnimatedObject, AnimatedObjectEx)
{
	NATIVE_REPLACE_MEMBER_FUNC(Update);
};

/*
void Update(ntv::anim::AnimatedObjectUpdateContext& aUpdateCtx)
    {
		RED4ext::ent::Entity* entity = aUpdateCtx.m_entity;
		RED4ext::CClass* entityClass = entity->GetType();

		if (auto* scriptProp = entityClass->GetProperty("shouldAnimUpdate"))
		{
			if (auto* shouldUpdate = scriptProp->GetValuePtr<bool>(entity))
			{
				if (*shouldUpdate == false) return;
			}
		}

		auto& metaRig = *NTV_GET(this,m_metaRigRef).m_metaRig;

        if ( IsHierarchyDirty() )
        {
			NTV_CALL(
			this,RebuildHierarchy(aUpdateCtx.m_metaRigBank));
            aUpdateCtx.m_rebuiltHierarchy = true;

            if (aUpdateCtx.m_metaRigHeadIndex >= -1)
            {
				aUpdateCtx.m_metaRigHeadIndex = NTV_CALL(metaRig,FindBoneByName("Head"));
            }
        }
		NTV_CALL(
		this,UpdateDistanceCategory(aUpdateCtx.m_distanceTimeDelta));

		ntv::anim::MetaPose& metaPose = *NTV_GET(this,m_metaPose);
		uint32_t lodDistanceCategory = NTV_GET(this,m_distanceCategory);
		metaPose.m_numBones = NTV_GET(metaRig,m_distanceCategoryNumBones)[lodDistanceCategory];
		metaPose.m_extraTransforms.Clear();
		metaPose.m_extraTracks.Clear();

		r4e::QsTransform	transformIdentity{ { 0.f, 0.f, 0.f, 0.f }, {}, { 1.f, 1.f, 1.f, 1.f } };
		r4e::QsTransform	partToParent;
		r4e::QsTransform	partToRoot;
		r4e::WorldTransform partToWorld;
		NTV_GET(this,unkEC) = 4;

		r4e::QsTransform& someUnkTransform = NTV_GET(this,m_unkTransform30);
		someUnkTransform = transformIdentity;

		ntv::anim::AnimatedObjectPart* rootPart = NTV_GET(this,m_rootPart);
		ntv::anim::AnimatedObjectPart* part = rootPart;
		uint32_t partIndex = 0;
		while ( part )
		{
			auto rigPoseLS = NTV_CALL(*part->m_rig,GetAPoseLS());
			NTV_CALL(
			metaPose,ResetPartTransforms(rigPoseLS, partIndex, metaRig));

			part = part->m_child;
			partIndex++;
		}

		// Part update context is built once; fields sourced from mutable state are
		// refreshed per-part below, everything else is loop-invariant.
		alignas(16) uint8_t unkStruct[0x310];
		r4e::QsTransform someTransform;

		ntv::anim::AnimatedObjectPartUpdateContext partUpdateCtx{};
		partUpdateCtx.unk00 = &someTransform;
		partUpdateCtx.unk08 = aUpdateCtx.unk20;
		partUpdateCtx.partToParent = &partToParent;
		partUpdateCtx.partToRoot = &partToRoot;
		partUpdateCtx.partToWorld = &partToWorld;
		partUpdateCtx.metaRig = &metaRig;
		partUpdateCtx.metaPose = &metaPose;
		partUpdateCtx.unkStructPtr40 = unkStruct;
		partUpdateCtx.globalTimeMs = aUpdateCtx.unk38;
		partUpdateCtx.unk50 = aUpdateCtx.unk40;
		partUpdateCtx.unk54 = aUpdateCtx.m_distanceTimeDelta;
		partUpdateCtx.globalTimeS = aUpdateCtx.unk48;
		partUpdateCtx.unk60 = aUpdateCtx.unk70;
		partUpdateCtx.unk68 = aUpdateCtx.unk28;
		partUpdateCtx.unk70 = aUpdateCtx.unk88;
		partUpdateCtx.unk78 = aUpdateCtx.unk90;
		partUpdateCtx.unk80 = aUpdateCtx.unk98;
		partUpdateCtx.animatedObject = aUpdateCtx.m_animatedObject;
		partUpdateCtx.unk90 = aUpdateCtx.unk78;
		partUpdateCtx.unk98 = &NTV_GET(this,unk70);
		partUpdateCtx.unkA0 = aUpdateCtx.unkB0;
		partUpdateCtx.unkA8 = aUpdateCtx.unkB8;
		partUpdateCtx.shouldSampleGraph = aUpdateCtx.m_shouldSampleGraph;
		partUpdateCtx.entity = aUpdateCtx.m_entity;
		partUpdateCtx.unkCC = aUpdateCtx.unkEE;
		partUpdateCtx.unkD0 = aUpdateCtx.unkC0;
		partUpdateCtx.unkD8 = aUpdateCtx.unkC8;
		partUpdateCtx.unkE0 = 0;
		partUpdateCtx.unkE8 = &aUpdateCtx.unkD0;
		partUpdateCtx.unkF0 = &aUpdateCtx.unkD4;
		partUpdateCtx.unk100 = &NTV_GET(this,unkEC);
		partUpdateCtx.unk108 = &aUpdateCtx.unkD8;
		partUpdateCtx.unk110 = &aUpdateCtx.unkE0;
		partUpdateCtx.unk118 = &aUpdateCtx.unkE4;
		partUpdateCtx.unk120 = &aUpdateCtx.unkEC;

		part = rootPart;
		partIndex = 0;
		while ( part )
		{
			bool isFacial = part->IsFacial();
			bool shouldSample = !aUpdateCtx.unkED || partIndex == 0 || isFacial;

			if ( shouldSample && !aUpdateCtx.m_forceUpdate && (isFacial || part->IsDeformation() || part->IsDangle()) )
			{
				uint32_t lod = NTV_CALL(
					*part->m_rig,RemapDistanceCategoryToSkeletalLOD(lodDistanceCategory));

				shouldSample = NTV_CALL(
					part,ShouldSample(lod));
			}

			if (shouldSample)
			{
				bool shouldUpdateFacial = !isFacial || 
										  (NTV_GET(this,unkE0) & 0x20) || 
										  !aUpdateCtx.unkEA || 
										  (NTV_GET(this,unk68) & 1);

				if ( shouldUpdateFacial || aUpdateCtx.m_forceUpdate )
				{
					if ( partIndex != 0 && part->m_updateSkipped )
					{
						NTV_CALL(
						part,CopyInputsFrom(rootPart));
						part->m_updateSkipped = false;
					}

					void* sharedData = part->unkSharedPtr2590.GetPtr();
					bool shouldCleanStreaming = sharedData && *OffsetPtr<uint32_t,0xBC>(sharedData) != 0;

					if ( NTV_CALL(part,UpdateInputs(part)) )
					{
						aUpdateCtx.unkD4 = false;
					}

					if ( shouldCleanStreaming || NTV_GET(this,m_hasDirtyStreamingContexts) )
					{
						NTV_CALL(
						part->m_dataContext,CleanStreamingContexts(
							NTV_GET(this,m_streamingContexts), 
							NTV_GET(this,m_dirtyStreamingContexts)
						));
					}

					// The part-to-parent transform chain and the part update itself only
					// matter when the part is actually updated, so all of it lives behind
					// shouldUpdateFacial; the original computed it unconditionally.
					if ( shouldUpdateFacial )
					{
						ntv::anim::AnimatedObjectPart* parentPart = part->m_parent;
						if ( parentPart
						  && parentPart->metaRigRootBoneIndex != -1
						  && part->metaRigRootBoneIndex != -1 
						)
						{
							r4e::QsTransform partMS = NTV_CALL(
								metaPose,GetBoneMSTransform(metaRig, part->metaRigRootBoneIndex));

							r4e::QsTransform parentMS = NTV_CALL(
								metaPose,GetBoneMSTransform(metaRig, parentPart->metaRigRootBoneIndex));

							NTV_CALL(
							partToParent,SetMulInverseMulUnsafe(parentMS, partMS));

							NTV_CALL(
							partToRoot,SetMulUnsafe(parentPart->localToRoot, partToParent));
							
							r4e::Transform transform = {
								partToParent.Translation,
								*reinterpret_cast<r4e::Quaternion*>(&NTV_CALL(
									simd::QuadHelper::Normalize4(partToParent.Rotation))
								)
							};

							partToWorld = NTV_CALL(
								parentPart->localToWorld,TransformXForm(transform));
						}
						else
						{
							partToParent = transformIdentity;
							partToRoot   = transformIdentity;
							partToWorld  = aUpdateCtx.m_localToWorld;
						}

						memset(unkStruct, 0, sizeof(unkStruct));
						someTransform = transformIdentity;

						// Refresh the fields whose sources the part update (or input update)
						// could have mutated since the context was built.
						partUpdateCtx.unk30 = &NTV_GET(metaRig,unkStructArray)[partIndex];
						partUpdateCtx.distanceCategory = NTV_GET(this,m_distanceCategory);
						partUpdateCtx.unkC4 = NTV_GET(this,unkA0);
						partUpdateCtx.unkC8 = NTV_GET(this,unkE8);
						partUpdateCtx.unkF8 = aUpdateCtx.unkD5;

						NTV_CALL(
						part,Update(partUpdateCtx));

						NTV_CALL(
						someUnkTransform,SetMulUnsafe(someUnkTransform, someTransform));
					}
				}
				else
				{
					part->m_updateSkipped = true;
				}
			}
			else
			{
				part->m_updateSkipped = true;
				part->unk25A0 = 2;
			}

			part = part->m_child;
			partIndex++;
		}

		if ( aUpdateCtx.m_shouldSampleGraph )
		{
			// Scripted pose properties; inlined replacement for the old 0x46E mid-hook,
			// which landed here: applied only when the graph is sampled, right before
			// CalcMS folds the overrides into model space.
			if (auto* scriptProp = entityClass->GetProperty("metaRigRef"))
			{
				if (auto* metaRigRef = scriptProp->GetValuePtr<MetaRigScriptRef>(entity))
				{
					metaRigRef->ptr = &metaRig;
				}
			}

			if (auto* scriptProp = entityClass->GetProperty("metaPoseRef"))
			{
				if (auto* metaPoseRef = scriptProp->GetValuePtr<MetaPoseScriptRef>(entity))
				{
					metaPoseRef->ptr = &metaPose;
				}
			}

			if (auto* scriptProp = entityClass->GetProperty("poseOverrideTransforms"))
			{
				if (auto* entries = scriptProp->GetValuePtr<RED4ext::DynArray<BoneTransformEntry>>(entity))
				{
					for (const auto& entry : *entries)
					{
						int32_t boneIdx = Lib::ArrayUtils::GetValueIndex(metaRig.boneNames, entry.name);
						if (boneIdx < 0 || boneIdx >= metaPose.m_transforms.Size()) continue;

						metaPose.m_transforms[boneIdx] = entry.transform;
					}
				}
			}

			if (auto* scriptProp = entityClass->GetProperty("poseAdditiveTransforms"))
			{
				if (auto* entries = scriptProp->GetValuePtr<RED4ext::DynArray<BoneTransformEntry>>(entity))
				{
					for (const auto& entry : *entries)
					{
						int32_t boneIdx = Lib::ArrayUtils::GetValueIndex(metaRig.boneNames, entry.name);
						if (boneIdx < 0 || boneIdx >= metaPose.m_transforms.Size()) continue;

						RED4ext::QsTransform& poseTransform = metaPose.m_transforms[boneIdx];
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
						int32_t trackIdx = Lib::ArrayUtils::GetValueIndex(metaRig.trackNames, entry.name);
						if (trackIdx < 0 || trackIdx >= metaPose.m_tracks.Size()) continue;

						metaPose.m_tracks[trackIdx] = entry.value;
					}
				}
			}

			NTV_CALL(
			metaPose,CalcMS(metaRig));
		}

		if ( NTV_GET(this,m_hasDirtyStreamingContexts) )
		{
			NTV_GET(this,m_dirtyStreamingContexts).Clear();
			NTV_GET(this,m_hasDirtyStreamingContexts) = false;
		}
    }*/
