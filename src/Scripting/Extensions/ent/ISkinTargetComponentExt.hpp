#pragma once

#include <Native/ent/ISkinTargetComponent.hpp>
#include <RED4ext/Scripting/Natives/Vector3.hpp>

RTTI_EXPAND_CLASS(RED4ext::ent::ISkinTargetComponent,
	type->defaults.InsertOrAssign(
		"visualScale",
		new Red::Variant(Red::ResolveType<Red::Vector3>(), new Red::Vector3(1.f, 1.f, 1.f))
	);
);
