#pragma once

#include <Native/ent/ISkinTargetComponent.hpp>

struct ISkinTargetComponentEx : RED4ext::ent::ISkinTargetComponent
{
	void OnTransformUpdated(RED4ext::Box& aOutBounds)
	{
		static constexpr r4e::CName c_visualScale = "visualScale";

		aOutBounds = NTV_CALL(
					 worldTransform,TransformBox(NTV_GET(this,m_activeSkinBounds)));

		RED4ext::Vector3 visualScale{ 1.f, 1.f, 1.f };
		if (auto* scriptProp = GetType()->GetProperty(c_visualScale))
		{
			if (auto* value = scriptProp->GetValuePtr<RED4ext::Vector3>(this))
			{
				visualScale = *value;
			}
		}

		ApplySkinningInfo info {
			{worldTransform, visualScale},
			aOutBounds,
			&NTV_GET(this,m_skinningBuffer),
			&NTV_GET(this,m_trackBuffer),
			NTV_GET(this,m_skinningBuffer) ? NTV_GET(this,m_skinningBuffer)->GetMatrixCount() : 0
		};
		NTV_CALL(
		this,OnApplySkinningAndTransform(&info));
	}
};

NATIVE_EXPAND(RED4ext::ent::ISkinTargetComponent, ISkinTargetComponentEx)
{
	NATIVE_REPLACE_MEMBER_FUNC(OnTransformUpdated);
};

RTTI_EXPAND_CLASS(RED4ext::ent::ISkinTargetComponent,
	type->defaults.InsertOrAssign(
		"visualScale",
		new Red::Variant(Red::ResolveType<Red::Vector3>(), new Red::Vector3(1.f, 1.f, 1.f))
	);
);
