#pragma once

#include <Native/anim/AnimInstanceVar.hpp>
#include <Native/anim/AnimInstanceBufferLayout.hpp>
#include <RED4ext/Scripting/Natives/Generated/anim/AnimDatabaseCollectionEntry.hpp>

namespace Native::anim
{
struct AnimInstanceBufferCompiler
{
	struct InputInfo
	{
		AnimInstanceVar* m_var;
		uint8_t unk08[0x28 - 0x09];
	};

	struct VarInfo
	{
		AnimInstanceVar* m_var;
		uint32_t m_size;
		uint32_t m_alignment;
	};

	struct SharedVarInfo
	{
		AnimInstanceVar* m_var;
		uint8_t unk08[0x20 - 0x08];
	};

	RED4ext::DynArray<InputInfo> m_inputsInfo;
	RED4ext::DynArray<VarInfo> m_varsInfo;
	RED4ext::DynArray<SharedVarInfo> m_sharedVarsInfo;
	RED4ext::DynArray<InputInfo> m_inputsInfo1; // idk why theres two
	RED4ext::DynArray<VarInfo> m_varsInfo1;
	RED4ext::DynArray<SharedVarInfo> m_sharedVarsInfo1;
	RED4ext::Map<RED4ext::CName, RED4ext::DynArray<AnimEventCallback>> m_eventCallbacksMap;
	RED4ext::DynArray<uint64_t> unk88;
	RED4ext::DynArray<uint64_t> unk98;
	RED4ext::DynArray<uint64_t> unka8;
	RED4ext::DynArray<uint64_t> unkb8;
	RED4ext::DynArray<uint64_t> unkc8;
	RED4ext::DynArray<uint64_t> unkd8;
	RED4ext::DynArray<uint64_t> unke8;
	uint32_t unkf8;
	RED4ext::DynArray<uint64_t> unk100;
	RED4ext::DynArray<uint64_t> unk110;
	RED4ext::DynArray<uint64_t> unk120;
	bool m_hashMixerSlot;
	uint8_t unk131;
	uint8_t unk132;
	uint32_t unk134;
	RED4ext::DynArray<RED4ext::anim::AnimDatabaseCollectionEntry> m_animDatabases;
};
RED4EXT_ASSERT_SIZE(AnimInstanceBufferCompiler, 0x148);
}
