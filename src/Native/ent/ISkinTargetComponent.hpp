#pragma once

#include <RED4ext/Scripting/Natives/Generated/ent/ISkinTargetComponent.hpp>

#include <RED4ext/Scripting/Natives/Box.hpp>
#include <Native/IRenderSkinningData.hpp>

struct RenderTransform
{
	RED4ext::WorldTransform worldTransform{};
	RED4ext::Vector3 scale;
};

struct ApplySkinningInfo
{
	RenderTransform m_transform;
	RED4ext::Box m_bounds;
	RED4ext::TRenderPtr<IRenderSkinningData>* m_skinningBuffer;
	RED4ext::TRenderPtr<>* m_trackBuffer;
	uint32_t m_numBones;
};


NATIVE_INFO_BEGIN(RED4ext::ent::ISkinTargetComponent)
	NATIVE_VIRTUAL_FN(bool(ApplySkinningInfo*), OnApplySkinningAndTransform, 0x298)
	NATIVE_MEMBER_FN(void(RED4ext::Box&), OnTransformUpdated, 3853850250)
	NATIVE_FIELD(RED4ext::Box, m_restSkinBounds, 0x140)
	NATIVE_FIELD(RED4ext::Box, m_activeSkinBounds, 0x160)
	NATIVE_FIELD(RED4ext::TRenderPtr<IRenderSkinningData>, m_skinningBuffer, 0x1b0)
	NATIVE_FIELD(RED4ext::TRenderPtr<>, m_trackBuffer, 0x1b8)
NATIVE_INFO_END()
