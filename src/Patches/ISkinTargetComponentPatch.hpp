#pragma once

#include <Native/ent/ISkinTargetComponent.hpp>
#include <Native/WorldTransform.hpp>

inline void ISkinTargetComponent_OnTransformUpdated(RED4ext::ent::ISkinTargetComponent* aThis, RED4ext::Box& aOutBounds)
{
	RED4ext::WorldTransform& worldTransform = aThis->worldTransform;
	aOutBounds = NATIVE_CALL(worldTransform,TransformBox(NATIVE_GET(aThis,m_activeSkinBounds)));

	RED4ext::Vector3 visualScale{ 1.f, 1.f, 1.f };
	if (auto* scripProp = aThis->GetType()->GetProperty("visualScale"))
	{
		visualScale = *scripProp->GetValuePtr<RED4ext::Vector3>(aThis);
	}

	ApplySkinningInfo info {
		{worldTransform, visualScale},
		aOutBounds,
		&NATIVE_GET(aThis,m_skinningBuffer),
		&NATIVE_GET(aThis,m_trackBuffer),
		NATIVE_GET(aThis,m_skinningBuffer) ? NATIVE_GET(aThis,m_skinningBuffer)->GetMatrixCount() : 0
	};
	NATIVE_CALL(aThis,OnApplySkinningAndTransform(&info));
}
