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
	uint32_t unk00;
	uint32_t unk04;
	uint32_t unk08;
	uint8_t unk0C[0x20 - 0x08];
	RED4ext::HashMap<std::pair<RED4ext::CName, RED4ext::CName>, uint16_t> m_inputsIndexMap;
	RED4ext::Map<RED4ext::CName, RED4ext::DynArray<AnimEventCallback>> m_eventCallbacksMap;
};
RED4EXT_ASSERT_SIZE(AnimInstanceBufferLayout, 0x80);
}
