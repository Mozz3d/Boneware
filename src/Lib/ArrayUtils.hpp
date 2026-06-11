#pragma once

#include <Native/anim/MetaRig.hpp>

namespace Lib::ArrayUtils
{
	template<typename T>
	inline int32_t GetValueIndex(const RED4ext::DynArray<T>& aArray, const T aValue)
	{
		auto it = aArray.Find(aValue);
		if (it == aArray.End())
		{
			return -1;
		}
		uint32_t index = static_cast<uint32_t>(std::distance(aArray.Begin(), it));
		return index;
	}
}
