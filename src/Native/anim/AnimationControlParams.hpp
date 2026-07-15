#pragma once

namespace Native::anim
{
class AnimationControlParams
{
public:
	uint8_t unk00[0xBC - 0x00]; // 00
	uint32_t unkBC;			    // BC
	int8_t unkC0[0xE8 - 0xC0];  // C0
};
RED4EXT_ASSERT_SIZE(AnimationControlParams, 0xE8);
}
