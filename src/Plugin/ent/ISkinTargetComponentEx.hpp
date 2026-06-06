#pragma once

#include <Native/ent/ISkinTargetComponent.hpp>

struct ISkinTargetComponentEx : RED4ext::ent::ISkinTargetComponent
{
	void OnTransformUpdated(RED4ext::Box& aOutBounds)
	{
		aOutBounds = NATIVE_CALL(worldTransform,TransformBox(NATIVE_GET(this,m_activeSkinBounds)));

		RED4ext::Vector3 visualScale{ 1.f, 1.f, 1.f };
		if (auto* scriptProp = GetType()->GetProperty("visualScale"))
		{
			visualScale = *scriptProp->GetValuePtr<RED4ext::Vector3>(this);
		}

		ApplySkinningInfo info {
			{worldTransform, visualScale},
			aOutBounds,
			&NATIVE_GET(this,m_skinningBuffer),
			&NATIVE_GET(this,m_trackBuffer),
			NATIVE_GET(this,m_skinningBuffer) ? NATIVE_GET(this,m_skinningBuffer)->GetMatrixCount() : 0
		};
		NATIVE_CALL(this,OnApplySkinningAndTransform(&info));
	}
};

NATIVE_EXPAND(RED4ext::ent::ISkinTargetComponent, ISkinTargetComponentEx)
{
	NATIVE_REPLACE_MEMBER_FN(OnTransformUpdated);
};

RTTI_EXPAND_CLASS(RED4ext::ent::ISkinTargetComponent,
	type->defaults.InsertOrAssign(
		"visualScale",
		new Red::Variant(Red::ResolveType<Red::Vector3>(), new Red::Vector3(1.f, 1.f, 1.f))
	);
);
