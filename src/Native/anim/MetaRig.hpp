#pragma once

#include <RED4ext/Scripting/Natives/animMetaRig.hpp>
#include <RED4ext/Memory/Allocators.hpp>

NATIVE_INFO(r4e::anim::MetaRig)
{
	NATIVE_MEMBER_FUNC(
	int16_t ,FindBoneByName,(r4e::CName aName) const, 1842286434);

	NATIVE_DATA_MEMBER(
	r4e::DynArray<uint16_t> ,m_distanceCategoryNumBones, 0x30);

	struct UnkStruct 
	{
		uint8_t unk00[0x80 - 0x00];
	};

	NATIVE_DATA_MEMBER(
	r4e::DynArray<UnkStruct> ,unkStructArray, 0x68);
};

namespace Native::anim
{
struct MetaRigBank
{
	struct MetaRigBankEntry
	{
		using AllocatorType = r4e::Memory::AnimMetaRigsAllocator;

		int32_t m_hash;
		uint32_t m_refCount;
		r4e::UniquePtr<r4e::anim::MetaRig> m_metaRig;
		bool unk10;
		bool m_isInitialized;
		r4e::SharedSpinLock m_lock;
	};

	r4e::DynArray<r4e::UniquePtr<MetaRigBankEntry>> m_entries;
	r4e::SharedSpinLock m_entriesLock;
	std::atomic<uint32_t> m_clearCounter;
};

struct MetaRigReference
{
	int32_t m_hash;
	r4e::anim::MetaRig* m_metaRig;
	MetaRigBank* m_metaRigBank;
};
} // namespace Native::anim
