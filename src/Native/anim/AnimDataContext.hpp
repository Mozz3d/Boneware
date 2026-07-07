#pragma once

#include <Native/anim/AnimStreamingContextEntry.hpp>

namespace Native::anim
{
	struct AnimDataContext
	{
		struct AdditionalPart
		{
			uint8_t unk00[0x10 - 0x00];
		};

		void* unk00;
		r4e::DynArray<AdditionalPart> additonalParts;
	};
}

NATIVE_INFO(ntv::anim::AnimDataContext)
{
	NATIVE_MEMBER_FUNC(
	void ,CleanStreamingContexts,(
		r4e::Span<ntv::anim::AnimStreamingContextEntry>, 
		r4e::Span<ntv::anim::AnimStreamingContextEntry>
	) const, 1992829852);
};
