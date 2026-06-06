#pragma once

#include <RED4ext/Scripting/Natives/animMetaRig.hpp>
#include <RED4ext/Memory/Allocators.hpp>

NATIVE_INFO(RED4ext::anim::MetaRig)
{
	NATIVE_MEMBER_FN(int16_t, FindBoneByName,(RED4ext::CName aName), 1842286434);
};

namespace Native::anim
{
struct MetaRigBank
{
	struct MetaRigBankEntry
	{
		using AllocatorType = RED4ext::Memory::AnimMetaRigsAllocator;

		int32_t m_hash;
		uint32_t m_refCount;
		RED4ext::UniquePtr<RED4ext::anim::MetaRig> m_metaRig;
		bool unk10;
		bool m_isInitialized;
		RED4ext::SharedSpinLock m_lock;
	};

	RED4ext::DynArray<RED4ext::UniquePtr<MetaRigBankEntry>> m_entries;
	RED4ext::SharedSpinLock m_entriesLock;
	std::atomic<uint32_t> m_clearCounter;
};

struct MetaRigReference
{
	//using Release_t = void(*)(MetaRigReference*);
	//static const RED4ext::UniversalRelocFunc<Release_t> Release{ 525864448 };

	int32_t m_hash;
	RED4ext::anim::MetaRig* m_metaRig;
	MetaRigBank* m_metaRigBank;
};
} // namespace Native::anim
