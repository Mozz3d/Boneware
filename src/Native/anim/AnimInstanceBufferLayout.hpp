#pragma once

#include <Native/anim/AnimInstanceBuffer.hpp>

namespace Native::anim
{
struct AnimNodeServiceEventContext
{
};

using AnimEventCallback = RED4ext::Callback<
	void(RED4ext::Handle<RED4ext::ISerializable> const&, AnimNodeServiceEventContext&, AnimInstanceBuffer&)
>;

class AnimInstanceBufferLayout
{
	struct RuntimeInputInfo
	{
		uint8_t unk00[0x20 - 0x00];
	};

	uint32_t unk00;
	uint32_t unk04;
	uint32_t unk08;
	r4e::DynArray<RuntimeInputInfo> m_runtimeInputs;
	r4e::HashMap<std::pair<r4e::CName, r4e::CName>, uint16_t> m_inputsIndexMap;
	r4e::Map<r4e::CName, r4e::DynArray<AnimEventCallback>> m_eventCallbacksMap;
	uint32_t unk78;
};
RED4EXT_ASSERT_SIZE(AnimInstanceBufferLayout, 0x80);
}
