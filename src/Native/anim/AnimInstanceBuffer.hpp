#pragma once

namespace Native::anim
{
struct PoseCache
{
	struct PoseDescriptor
	{
		uint8_t unk00[0x40 - 0x00];
	};

	uint8_t unk00[0x40 - 0x00];
	RED4ext::DynArray<PoseDescriptor> m_poseDescriptors;
	uint64_t unk50;
};
RED4EXT_ASSERT_SIZE(PoseCache, 0x58);

struct EventsCache
{
	uint8_t unk00[0x50 - 0x00];
};
RED4EXT_ASSERT_SIZE(EventsCache, 0x50);

class AnimInstanceBuffer
{
	void* m_varsBuffer;
	uint32_t m_size;
	uint32_t unk0C;
	uint8_t unk10;
	PoseCache m_poseCache;
	EventsCache m_eventsCache;
};
RED4EXT_ASSERT_SIZE(AnimInstanceBuffer, 0xC0);
}
