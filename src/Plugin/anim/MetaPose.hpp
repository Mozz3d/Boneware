#pragma once

#include <Native/anim/MetaPose.hpp>

struct BoneTransformEntry
{
	RED4ext::CName name;
	RED4ext::QsTransform transform;
};

RTTI_DEFINE_CLASS(BoneTransformEntry, {
	RTTI_PROPERTY(name);
	RTTI_PROPERTY(transform);
});

struct TrackValueEntry
{
	RED4ext::CName name;
	float value;
};

RTTI_DEFINE_CLASS(TrackValueEntry, {
	RTTI_PROPERTY(name);
	RTTI_PROPERTY(value);
});

struct MetaPoseScriptRef
{
	MetaPoseScriptRef() = default;

	r4e::DynArray<r4e::QsTransform> GetTransforms() const
	{
		if (ptr) return ptr->m_transforms;
		return {};
	}

	r4e::QsTransform GetTransform(uint32_t aBoneIdx) const
	{
		if (ptr && aBoneIdx < ptr->m_transforms.Size())
		{
			return ptr->m_transforms[aBoneIdx];
		}
		return {};
	}

	r4e::DynArray<float> GetTracks() const
	{
		if (ptr) return ptr->m_tracks;
		return {};
	}

	float GetTrack(uint32_t aTrackIndex) const
	{
		if (ptr && aTrackIndex < ptr->m_tracks.Size())
		{
			return ptr->m_tracks[aTrackIndex];
		}
		return {};
	}

	void Update(const ntv::anim::MetaPose* aPtr)
	{
		ptr = const_cast<ntv::anim::MetaPose*>(aPtr);
	}

	ntv::anim::MetaPose* ptr = nullptr;
};

RTTI_DEFINE_CLASS(MetaPoseScriptRef, "MetaPoseRef",
{
	RTTI_METHOD(GetTransforms);
	RTTI_METHOD(GetTransform);
	RTTI_METHOD(GetTracks);
	RTTI_METHOD(GetTrack);
});