#pragma once

namespace Native::anim
{
class AnimInstanceBuffer
{
	void* m_varsBuffer;
	uint32_t m_bufferSize;
	uint8_t unk0c[0xc0 - 0x0c];
};
RED4EXT_ASSERT_SIZE(AnimInstanceBuffer, 0xC0);
}
