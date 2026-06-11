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

	RED4ext::DynArray<RED4ext::QsTransform> GetTransforms() const
	{
		if (ptr) return ptr->m_transforms;
		return {};
	}

	RED4ext::QsTransform GetTransform(uint32_t aBoneIdx) const
	{
		if (ptr) return ptr->m_transforms[aBoneIdx];
		return {};
	}

	RED4ext::DynArray<float> GetTracks() const
	{
		if (ptr) return ptr->m_tracks;
		return {};
	}

	float GetTrack(uint32_t aTrackIndex) const
	{
		if (ptr) return ptr->m_tracks[aTrackIndex];
		return {};
	}


	Native::anim::MetaPose* ptr = nullptr;
};

RTTI_DEFINE_CLASS(MetaPoseScriptRef, "MetaPoseRef",
{
	RTTI_METHOD(GetTransforms);
	RTTI_METHOD(GetTransform);
	RTTI_METHOD(GetTracks);
	RTTI_METHOD(GetTrack);
});