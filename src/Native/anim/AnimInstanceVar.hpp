#pragma once

namespace Native::anim
{
// the overcomplicated way CDPR handles accesing info in the AnimInstanceBuffer
struct AnimInstanceVar
{
	uint8_t unk00[0x8 - 0x00];
	uint32_t m_offset;
};

template<typename T>
struct TAnimInstanceInput : AnimInstanceVar
{
};

template<typename T>
struct TAnimInstanceVar : AnimInstanceVar
{
};

template<typename T>
struct TAnimInstanceSharedVar : AnimInstanceVar
{
};

// an variable representing an array of variables
template<typename T>
struct TAnimInstanceArrayVar : AnimInstanceVar
{
	uint32_t m_capacity;
};
}
