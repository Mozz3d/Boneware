#pragma once

namespace Lib::Rig
{
	inline r4e::Span<const r4e::QsTransform> GetAPoseLS(const r4e::anim::Rig& aRig)
	{
		const uint32_t numBones = aRig.boneNames.Size();
		return aRig.aPoseLS.Size() == numBones ?
			r4e::Span(aRig.aPoseLS.Data(), aRig.aPoseLS.Size()) :
			r4e::Span(const_cast<const r4e::QsTransform*>(aRig.referencePoseLS), numBones);
	};
}
