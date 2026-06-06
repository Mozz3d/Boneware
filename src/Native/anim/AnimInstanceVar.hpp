#pragma once

namespace Native::anim
{
// the overcomplicated way CDPR handles accesing info in the AnimInstanceBuffer
struct AnimInstanceVar
{
	virtual RED4ext::Memory::IAllocator* GetAllocator() = 0;
	uint32_t m_offset;
};

template<typename T>
struct TAnimInstanceVar : AnimInstanceVar
{
	uint32_t GetVarSize() const { return sizeof(T); }
	uint32_t GetVarAlign() const { return alignof(T); }
};

template<typename T>
struct TAnimInstanceSharedVar : AnimInstanceVar
{
};

// an instance variable representing an array of instance variables
template<typename T>
struct TAnimInstanceArrayVar : AnimInstanceVar
{
	uint32_t GetVarSize() const { return m_size * sizeof(T) + sizeof(m_size); }
	uint32_t GetVarAlign() const { return alignof(T); }

	uint32_t Size() { return m_size; }
	void Resize(uint32_t aSize) { m_size = aSize; }

	uint32_t m_size;
};

template<typename T>
struct TAnimInstanceInput : AnimInstanceVar
{
};
}
