#pragma once

#include <Native/anim/MetaPose.hpp>
#include <Native/anim/MetaRig.hpp>

struct BoneTransformEntry
{
	r4e::CName name;
	r4e::QsTransform transform;
};

RTTI_DEFINE_CLASS(BoneTransformEntry, {
	RTTI_PROPERTY(name);
	RTTI_PROPERTY(transform);
});

struct TrackValueEntry
{
	r4e::CName name;
	float value;
};

RTTI_DEFINE_CLASS(TrackValueEntry, {
	RTTI_PROPERTY(name);
	RTTI_PROPERTY(value);
});

struct ScriptMetaPose
{
	r4e::DynArray<BoneTransformEntry> m_overrideTransformsLS;
	r4e::DynArray<BoneTransformEntry> m_additiveTransformsLS;
	r4e::DynArray<TrackValueEntry> m_overrideTracks;
	
	void UpdateTransformsLS(const r4e::DynArray<r4e::QsTransform>& aTransformsLS)
	{
		m_transformsLS = aTransformsLS;
	}

	void UpdateTransformsMS(const r4e::DynArray<r4e::QsTransform>& aTransformsMS)
	{
		m_transformsMS = aTransformsMS;
	}

	void UpdateTracks(const r4e::DynArray<float>& aTracks)
	{
		m_tracks = aTracks;
	}

	void UpdateNumBones(uint32_t aNumBones)
	{
		m_numBones = aNumBones;
	}

	void ApplyOverrideTransformsLS(ntv::anim::MetaPose& aMetaPose, const r4e::anim::MetaRig& aMetaRig)
	{
		for (const auto& entry : m_overrideTransformsLS)
		{
			int32_t boneIdx = Lib::ArrUtils::IndexOf(aMetaRig.boneNames, entry.name);
			if (boneIdx < 0 || boneIdx >= aMetaPose.m_transforms.Size()) continue;

			aMetaPose.m_transforms[boneIdx] = entry.transform;
		}
	}

	void ApplyAdditiveTransformsLS(ntv::anim::MetaPose& aMetaPose, const r4e::anim::MetaRig& aMetaRig)
	{
		for (const auto& entry : m_additiveTransformsLS)
		{
			int32_t boneIdx = Lib::ArrUtils::IndexOf(aMetaRig.boneNames, entry.name);
			if (boneIdx < 0 || boneIdx >= aMetaPose.m_transforms.Size()) continue;

			r4e::QsTransform& poseTransform = aMetaPose.m_transforms[boneIdx];
			poseTransform.Translation += entry.transform.Translation;
			poseTransform.Rotation *= entry.transform.Rotation;
			poseTransform.Scale *= entry.transform.Scale;
		}
	}

	void ApplyOverrideTracks(ntv::anim::MetaPose& aMetaPose, const r4e::anim::MetaRig& aMetaRig)
	{
		for (const auto& entry : m_overrideTracks)
		{
			int32_t trackIdx = Lib::ArrUtils::IndexOf(aMetaRig.trackNames, entry.name);
			if (trackIdx < 0 || trackIdx >= aMetaPose.m_tracks.Size()) continue;

			aMetaPose.m_tracks[trackIdx] = entry.value;
		}
	}

	r4e::DynArray<r4e::QsTransform> m_transformsLS;
	r4e::DynArray<r4e::QsTransform> m_transformsMS;
	r4e::DynArray<float> m_tracks;
	uint32_t m_numBones;
};

RTTI_DEFINE_CLASS(ScriptMetaPose, "MetaPose",
{
	RTTI_PROPERTY(m_numBones,	  "numBones");
	RTTI_PROPERTY(m_transformsLS, "transformsLS");
	RTTI_PROPERTY(m_transformsMS, "transformsMS");
	RTTI_PROPERTY(m_tracks,		  "tracks");

	RTTI_PROPERTY(m_overrideTransformsLS, "overrideTransformsLS");
	RTTI_PROPERTY(m_additiveTransformsLS, "additiveTransformsLS");
	RTTI_PROPERTY(m_overrideTracks,		  "overrideTracks");
});
