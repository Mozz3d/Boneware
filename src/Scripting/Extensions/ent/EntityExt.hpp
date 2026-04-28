#pragma once

#include <RED4ext/Scripting/Natives/entEntity.hpp>

struct EntityEx : RED4ext::ent::Entity
{
	RED4ext::DynArray<RED4ext::Handle<RED4ext::IComponent>> GetSkinTargetComponents()
	{
		RED4ext::DynArray<RED4ext::Handle<RED4ext::IComponent>> outComponents;
		for (auto& comp : components)
		{
			if (comp->GetType()->IsA(Red::GetType<RED4ext::ent::ISkinTargetComponent>()))
			{
				outComponents.PushBack(comp);
			}
		}
		return outComponents;
	}
};
RTTI_EXPAND_CLASS(RED4ext::ent::Entity, EntityEx,
	RTTI_METHOD(GetSkinTargetComponents);
);
