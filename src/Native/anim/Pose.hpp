#pragma once

#include <RED4ext/Scripting/Natives/Generated/QsTransform.hpp>

namespace Native
{
namespace anim
{
struct Pose
{
    uint32_t numTransforms;      // 00
    uint32_t numTracks;          // 04
    uint32_t numExtraTransforms; // 08
    uint32_t numExtraTracks;     // 0C
    uint8_t unk10[0x24 - 0x10];  // 10
    uint32_t numAllTransforms;   // 24
    uint32_t numAllTracks;       // 28
    uint8_t unk2C[0x30 - 0x2C];  // 2C
    RED4ext::QsTransform* transforms; // 30
    float* tracks;               // 38
    uint8_t unk40[0x50 - 0x40];  // 40
};
RED4EXT_ASSERT_SIZE(Pose, 0x50);
} // namespace anim
} // namespace Native
