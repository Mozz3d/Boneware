#pragma once

#include <Native/anim/MetaRig.hpp>

struct MetaRigScriptRef
{
	MetaRigScriptRef() = default;
	MetaRigScriptRef(RED4ext::anim::MetaRig* aMetaRig)
		: ptr(aMetaRig)
	{
	}

	RED4ext::DynArray<RED4ext::CName> GetBoneNames() const
	{
		if (ptr) return ptr->boneNames;
		return {};
	}

	RED4ext::anim::MetaRig* ptr = nullptr;
};

RTTI_DEFINE_CLASS(MetaRigScriptRef, "MetaRigRef",
	RTTI_METHOD(GetBoneNames);
);