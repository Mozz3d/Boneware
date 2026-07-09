#pragma once

#include <algorithm>

namespace Lib::Rig
{
	inline r4e::Span<const r4e::QsTransform> GetAPoseLS(const r4e::anim::Rig& aRig)
	{
		const uint32_t numBones = aRig.boneNames.Size();
		return aRig.aPoseLS.Size() == numBones ?
			r4e::Span(aRig.aPoseLS.Data(), aRig.aPoseLS.Size()) :
			r4e::Span(const_cast<const r4e::QsTransform*>(aRig.referencePoseLS), numBones);
	};

	inline uint32_t RemapDistanceCategoryToSkeletalLOD(const r4e::anim::Rig& aRig, uint32_t aDistanceCategory)
	{
		const uint32_t maxLod = aRig.levelOfDetailStartIndices.Size();

		if ( aRig.distanceCategoryToLodMap.Size() == 0 )
			return std::min(aDistanceCategory, maxLod);

		const uint32_t index = std::min(aDistanceCategory, aRig.distanceCategoryToLodMap.Size() - 1);
		const uint32_t lod = aRig.distanceCategoryToLodMap.Data()[index];
		return std::min(lod, maxLod);
	}
}
