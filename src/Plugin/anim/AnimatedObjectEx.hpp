#pragma once

#include <Native/WorldTransform.hpp>

#include <Native/anim/AnimatedObject.hpp>
#include <Native/simd/QsTransform.hpp>
#include <Native/simd/QuadHelper.hpp>
#include <Plugin/anim/MetaPose.hpp>
#include <Plugin/anim/MetaRig.hpp>

#include <Lib/RigUtils.hpp>

struct AnimatedObjectEx : RED4ext::anim::AnimatedObject
{
    bool IsHierarchyDirty()
	{
		auto* part = NTV_GET(
					 this,m_rootPart);
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
		static constexpr r4e::CName c_shouldAnimUpdate	     = "shouldAnimUpdate";
		static constexpr r4e::CName c_metaRigRef		     = "metaRigRef";
		static constexpr r4e::CName c_metaPoseRef			 = "metaPoseRef";
		static constexpr r4e::CName c_poseOverrideTransforms = "poseOverrideTransforms";
		static constexpr r4e::CName c_poseAdditiveTransforms = "poseAdditiveTransforms";
		static constexpr r4e::CName c_poseTrackOverrides	 = "poseTrackOverrides";

		r4e::ent::Entity* entity = aUpdateCtx.m_entity;
		r4e::CClass* entityClass = entity->GetType();

		if (auto* scriptProp = entityClass->GetProperty(c_shouldAnimUpdate))
		{
			if (auto* shouldUpdate = scriptProp->GetValuePtr<bool>(entity))
			{
				if (*shouldUpdate == false) return;
			}
		}

		if ( IsHierarchyDirty() )
		{
			NTV_CALL(
			this,RebuildHierarchy(*aUpdateCtx.m_metaRigBank));

			aUpdateCtx.m_rebuiltHierarchy = true;

			if (aUpdateCtx.m_metaRigHeadIndex >= -1)
			{
				aUpdateCtx.m_metaRigHeadIndex = 
					Lib::ArrUtils::IndexOf(NTV_GET(
										   this,m_metaRigRef).m_metaRig->boneNames, r4e::CName{0x351c13d86108cce3}/*Head*/ );
			}
		}

		NTV_CALL(
		this,UpdateDistanceCategory(aUpdateCtx.m_distanceTimeDelta));

		const r4e::anim::MetaRig& _metaRig = *NTV_GET(
											  this,m_metaRigRef).m_metaRig;

		ntv::anim::MetaPose& metaPose = *NTV_GET(
										 this,m_metaPose);

		const uint32_t distanceCategory = NTV_GET(
										  this,m_distanceCategory);
		metaPose.m_numBones = NTV_GET(
							  _metaRig,m_distanceCategoryNumBones)[distanceCategory];

		metaPose.m_extraTransforms.Clear();
		metaPose.m_extraTracks.Clear();

		const r4e::QsTransform transformIdentity{ { 0.f, 0.f, 0.f, 0.f }, {}, { 1.f, 1.f, 1.f, 1.f } };
		r4e::QsTransform	   partToParent;
		r4e::QsTransform	   partToRoot;
		r4e::WorldTransform    partToWorld;
		NTV_GET(
		this,unkEC) = 4;

		r4e::QsTransform& someUnkTransform = NTV_GET(
											 this,m_unkTransform30);
		someUnkTransform = transformIdentity;

		ntv::anim::AnimatedObjectPart* rootPart = NTV_GET(
												  this,m_rootPart);
		ntv::anim::AnimatedObjectPart* part = rootPart;
		uint32_t partIndex = 0;
		while ( part )
		{
			metaPose.ResetTransforms(Lib::Rig::GetAPoseLS(*part->m_rig), partIndex, _metaRig);

			part = part->m_child;
			partIndex++;
		}

		alignas(16) uint8_t unkStruct[0x310];
		r4e::QsTransform	deltaTransform;

		ntv::anim::AnimatedObjectPartUpdateContext partUpdateCtx{};
		partUpdateCtx.deltaTransform = &deltaTransform;
		partUpdateCtx.unk08 = aUpdateCtx.unk20;
		partUpdateCtx.partToParent = &partToParent;
		partUpdateCtx.partToRoot = &partToRoot;
		partUpdateCtx.partToWorld = &partToWorld;
		partUpdateCtx.metaRig = &_metaRig;
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
		partUpdateCtx.entity = entity;
		partUpdateCtx.distanceCategory = distanceCategory;
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


		const bool forceUpdate		 = aUpdateCtx.m_forceUpdate;
		const bool onlyRootAndFacial = aUpdateCtx.unkED;
		const bool facialAllowed	 = (NTV_GET(
										this,unkE0) & 0x20)
										|| !aUpdateCtx.unkEA
										|| (NTV_GET(
											this,unk68) & 1);

		auto& streamingContexts			 = NTV_GET(
										   this,m_streamingContexts);

		auto& dirtyStreamingContexts	 = NTV_GET(
										   this,m_dirtyStreamingContexts);

		bool& hasDirtyStreamingContexts	 = NTV_GET(
										   this,m_hasDirtyStreamingContexts);

		part = rootPart;
		partIndex = 0;
		while ( part )
		{
			const bool isFacial = part->IsFacial();
			bool shouldSample   = !onlyRootAndFacial || partIndex == 0 || isFacial;

			if ( shouldSample && !forceUpdate && (isFacial || part->IsDeformation() || part->IsDangle()) )
			{
				shouldSample = part->ShouldSample(
					Lib::Rig::RemapDistanceCategoryToSkeletalLOD(*part->m_rig, distanceCategory) );
			}

			if (shouldSample)
			{
				const bool shouldUpdateFacial = !isFacial || facialAllowed;

				if ( shouldUpdateFacial || forceUpdate )
				{
					if ( shouldUpdateFacial )
					{
						const ntv::anim::AnimatedObjectPart* parentPart = part->m_parent;
						if ( parentPart
						  && parentPart->metaRigRootBoneIndex != -1
						  && part->metaRigRootBoneIndex != -1 
						)
						{
							const r4e::QsTransform partMS = NTV_CALL(
														    metaPose,GetBoneMSTransform(_metaRig, part->metaRigRootBoneIndex));

							const r4e::QsTransform parentMS = NTV_CALL(
															  metaPose,GetBoneMSTransform(_metaRig, parentPart->metaRigRootBoneIndex));

							Lib::QsTransform::SetMulInverseMulUnsafe(partToParent, parentMS, partMS);
							Lib::QsTransform::SetMulUnsafe(partToRoot, parentPart->localToRoot, partToParent);

							auto normalizedRot = Lib::simd::Normalize4(*std::bit_cast<__m128*>(&partToParent.Rotation));
							r4e::Transform transform = {
								partToParent.Translation,
								*std::bit_cast<r4e::Quaternion*>(&normalizedRot)
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
					}

					if ( partIndex != 0 && part->m_updateSkipped )
					{
						NTV_CALL(
						part,CopyInputsFrom(*rootPart));

						part->m_updateSkipped = false;
					}

					const void* sharedData = part->unkSharedPtr2590.GetPtr();
					bool shouldCleanStreamingContexts = sharedData && *OffsetPtr<uint32_t,0xBC>(sharedData) != 0;

					if ( NTV_CALL(
						 part,UpdateInputs(*part)) )
					{
						aUpdateCtx.unkD4 = false;
					}

					if ( shouldCleanStreamingContexts || hasDirtyStreamingContexts )
					{
						NTV_CALL(
						part->m_dataContext,CleanStreamingContexts(
							r4e::Span(streamingContexts.Data(), streamingContexts.Size()),
							r4e::Span(dirtyStreamingContexts.Data(), dirtyStreamingContexts.Size())
						));
					}

					if ( shouldUpdateFacial )
					{
						memset(unkStruct, 0, sizeof(unkStruct));
						deltaTransform = transformIdentity;

						partUpdateCtx.unk30 = &NTV_GET(
											   _metaRig,unkStructArray)[partIndex];

						NTV_CALL(
						part,Update(partUpdateCtx));

						Lib::QsTransform::SetMulUnsafe(someUnkTransform, someUnkTransform, deltaTransform);
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
			if (auto* scriptProp = entityClass->GetProperty(c_metaRigRef))
			{
				if (auto* metaRigRef = scriptProp->GetValuePtr<MetaRigScriptRef>(entity))
				{
					metaRigRef->Update(&_metaRig);
				}
			}

			if (auto* scriptProp = entityClass->GetProperty(c_metaPoseRef))
			{
				if (auto* metaPoseRef = scriptProp->GetValuePtr<MetaPoseScriptRef>(entity))
				{
					metaPoseRef->Update(&metaPose);
				}
			}

			if (auto* scriptProp = entityClass->GetProperty(c_poseOverrideTransforms))
			{
				if (auto* entries = scriptProp->GetValuePtr<RED4ext::DynArray<BoneTransformEntry>>(entity))
				{
					for (const auto& entry : *entries)
					{
						int32_t boneIdx = Lib::ArrUtils::IndexOf(_metaRig.boneNames, entry.name);
						if (boneIdx < 0 || boneIdx >= metaPose.m_transforms.Size()) continue;

						metaPose.m_transforms[boneIdx] = entry.transform;
					}
				}
			}

			if (auto* scriptProp = entityClass->GetProperty(c_poseAdditiveTransforms))
			{
				if (auto* entries = scriptProp->GetValuePtr<RED4ext::DynArray<BoneTransformEntry>>(entity))
				{
					for (const auto& entry : *entries)
					{
						int32_t boneIdx = Lib::ArrUtils::IndexOf(_metaRig.boneNames, entry.name);
						if (boneIdx < 0 || boneIdx >= metaPose.m_transforms.Size()) continue;

						RED4ext::QsTransform& poseTransform = metaPose.m_transforms[boneIdx];
						poseTransform.Translation += entry.transform.Translation;
						poseTransform.Rotation	  *= entry.transform.Rotation;
						poseTransform.Scale		  *= entry.transform.Scale;
					}
				}
			}

			if (auto* scriptProp = entityClass->GetProperty(c_poseTrackOverrides))
			{
				if (auto* entries = scriptProp->GetValuePtr<RED4ext::DynArray<TrackValueEntry>>(entity))
				{
					for (const auto& entry : *entries)
					{
						int32_t trackIdx = Lib::ArrUtils::IndexOf(_metaRig.trackNames, entry.name);
						if (trackIdx < 0 || trackIdx >= metaPose.m_tracks.Size()) continue;

						metaPose.m_tracks[trackIdx] = entry.value;
					}
				}
			}

			NTV_CALL(
			metaPose,CalcMS(_metaRig));
		}

		if ( hasDirtyStreamingContexts )
		{
			dirtyStreamingContexts.Clear();
			hasDirtyStreamingContexts = false;
		}
	}
};

NATIVE_EXPAND(r4e::anim::AnimatedObject, AnimatedObjectEx)
{
	NATIVE_REPLACE_MEMBER_FUNC(Update);
};
