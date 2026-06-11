#pragma once

#include <Native/anim/MetaRig.hpp>

struct MetaRigScriptRef
{
	MetaRigScriptRef() = default;

	RED4ext::DynArray<RED4ext::QsTransform> GetBoneTransforms() const
	{
		if (ptr) return ptr->boneTransforms;
		return {};
	}

	RED4ext::QsTransform GetBoneTransform(uint32_t aBoneIndex) const
	{
		if (ptr && aBoneIndex < ptr->boneTransforms.Size())
		{
			return ptr->boneTransforms[aBoneIndex];
		}
		return {};
	}

	RED4ext::DynArray<RED4ext::CName> GetBoneNames() const
	{
		if (ptr) return ptr->boneNames;
		return {};
	}

	RED4ext::CName GetBoneName(int32_t aBoneIndex) const
	{
		if (ptr && aBoneIndex < ptr->boneNames.Size())
		{
			return ptr->boneNames[aBoneIndex];
		}
		return {};
	}

	int32_t GetBoneIndex(const RED4ext::CName aBoneName) const
	{
		if (ptr) return Lib::ArrayUtils::GetValueIndex(ptr->boneNames, aBoneName);
		return -1;
	}

	RED4ext::DynArray<float> GetTrackValues() const
	{
		if (ptr) return ptr->referenceTracks;
		return {};
	}

	float GetTrackValue(uint32_t aTrackIndex) const
	{
		if (ptr && aTrackIndex < ptr->referenceTracks.Size())
		{
			return ptr->referenceTracks[aTrackIndex];
		}
		return 0;
	}

	RED4ext::DynArray<RED4ext::CName> GetTrackNames() const
	{
		if (ptr) return ptr->trackNames;
		return {};
	}

	RED4ext::CName GetTrackName(int32_t aTrackIndex) const
	{
		if (ptr && aTrackIndex < ptr->trackNames.Size())
		{
			return ptr->trackNames[aTrackIndex];
		}
		return {};
	}

	int32_t GetTrackIndex(const RED4ext::CName aTrackName) const
	{
		if (ptr) return Lib::ArrayUtils::GetValueIndex(ptr->trackNames, aTrackName);
		return -1;
	}

	RED4ext::anim::MetaRig* ptr = nullptr;
};

RTTI_DEFINE_CLASS(MetaRigScriptRef, "MetaRigRef",
	RTTI_METHOD(GetBoneTransforms);
	RTTI_METHOD(GetBoneTransform);
	RTTI_METHOD(GetBoneNames);
	RTTI_METHOD(GetBoneName);
	RTTI_METHOD(GetBoneIndex);
	RTTI_METHOD(GetTrackValues);
	RTTI_METHOD(GetTrackValue);
	RTTI_METHOD(GetTrackNames);
	RTTI_METHOD(GetTrackName);
	RTTI_METHOD(GetTrackIndex);
);