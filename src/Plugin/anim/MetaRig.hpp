#pragma once

#include <Native/anim/MetaRig.hpp>

struct MetaRigScriptRef
{
	MetaRigScriptRef() = default;

	r4e::DynArray<r4e::QsTransform> GetBoneTransforms() const
	{
		if (ptr) return ptr->boneTransforms;
		return {};
	}

	r4e::QsTransform GetBoneTransform(uint32_t aBoneIndex) const
	{
		if (ptr && aBoneIndex < ptr->boneTransforms.Size())
		{
			return ptr->boneTransforms[aBoneIndex];
		}
		return {};
	}

	r4e::DynArray<int16_t> GetBoneParentIndices() const
	{
		if (ptr) return ptr->parentIndeces;
		return {};
	}

	r4e::DynArray<r4e::CName> GetBoneNames() const
	{
		if (ptr) return ptr->boneNames;
		return {};
	}

	r4e::CName GetBoneName(int32_t aBoneIndex) const
	{
		if (ptr && aBoneIndex < ptr->boneNames.Size())
		{
			return ptr->boneNames[aBoneIndex];
		}
		return {};
	}

	int32_t GetBoneIndex(const r4e::CName aBoneName) const
	{
		if (ptr) return Lib::ArrUtils::IndexOf(ptr->boneNames, aBoneName);
		return -1;
	}

	r4e::DynArray<float> GetTrackValues() const
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

	r4e::DynArray<r4e::CName> GetTrackNames() const
	{
		if (ptr) return ptr->trackNames;
		return {};
	}

	r4e::CName GetTrackName(int32_t aTrackIndex) const
	{
		if (ptr && aTrackIndex < ptr->trackNames.Size())
		{
			return ptr->trackNames[aTrackIndex];
		}
		return {};
	}

	int32_t GetTrackIndex(const r4e::CName aTrackName) const
	{
		if (ptr) return Lib::ArrUtils::IndexOf(ptr->trackNames, aTrackName);
		return -1;
	}

	void Update(const r4e::anim::MetaRig* aPtr)
	{
		ptr = const_cast<r4e::anim::MetaRig*>(aPtr);
	}

	r4e::anim::MetaRig* ptr = nullptr;
};

RTTI_DEFINE_CLASS(MetaRigScriptRef, "MetaRigRef",
	RTTI_METHOD(GetBoneTransforms);
	RTTI_METHOD(GetBoneTransform);
	RTTI_METHOD(GetBoneParentIndices);
	RTTI_METHOD(GetBoneNames);
	RTTI_METHOD(GetBoneName);
	RTTI_METHOD(GetBoneIndex);
	RTTI_METHOD(GetTrackValues);
	RTTI_METHOD(GetTrackValue);
	RTTI_METHOD(GetTrackNames);
	RTTI_METHOD(GetTrackName);
	RTTI_METHOD(GetTrackIndex);
);