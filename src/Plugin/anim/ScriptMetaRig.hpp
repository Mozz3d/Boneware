#pragma once

#include <Native/anim/MetaRig.hpp>

struct ScriptMetaRig
{

	void Update(const r4e::anim::MetaRig& aMetaRig)
	{
		m_transforms = aMetaRig.boneTransforms;
		m_parentIndices = aMetaRig.parentIndeces;
		m_boneNames = aMetaRig.boneNames;
		m_tracks = aMetaRig.referenceTracks;
		m_trackNames = aMetaRig.trackNames;
	}

	r4e::DynArray<r4e::QsTransform> m_transforms;
	r4e::DynArray<int16_t> m_parentIndices;
	r4e::DynArray<r4e::CName> m_boneNames;
	r4e::DynArray<float> m_tracks;
	r4e::DynArray<r4e::CName> m_trackNames;
};

RTTI_DEFINE_CLASS(ScriptMetaRig, "MetaRig",
{
	RTTI_PROPERTY(m_transforms,	   "transforms");
	RTTI_PROPERTY(m_parentIndices, "parentIndices");
	RTTI_PROPERTY(m_boneNames,	   "boneNames");
	RTTI_PROPERTY(m_tracks,		   "tracks");
	RTTI_PROPERTY(m_trackNames,	   "trackNames");
});
