#pragma once

#include <Native/anim/MetaPose.hpp>

struct BoneOffsetEntry
{
	RED4ext::CName name;
	RED4ext::QsTransform transform;
};

RTTI_DEFINE_CLASS(BoneOffsetEntry, "BoneOffsetEntry", {});

struct MetaPoseScriptRef
{
	MetaPoseScriptRef() = default;

	RED4ext::DynArray<RED4ext::QsTransform> GetTransforms()
	{
		if (ptr) return ptr->m_transforms;
		return {};
	}

	RED4ext::DynArray<float> GetTracks()
	{
		if (ptr) return ptr->m_tracks;
		return {};
	}

	Native::anim::MetaPose* ptr = nullptr;
};

RTTI_DEFINE_CLASS(MetaPoseScriptRef, "MetaPoseScriptRef",
{
	RTTI_METHOD(GetTransforms);
	RTTI_METHOD(GetTracks);
});