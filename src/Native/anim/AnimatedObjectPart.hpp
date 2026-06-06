#pragma once

#include <Native/anim/AnimInstanceBuffer.hpp>
#include <Native/anim/Pose.hpp>
#include <Native/anim/MetaPose.hpp>

#include <RED4ext/Scripting/Natives/Generated/anim/AnimGraph.hpp>
#include <RED4ext/Scripting/Natives/Generated/anim/AnimGraphExternalEvent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/AnimatedComponent.hpp>

#include <RED4ext/Scripting/Natives/animMetaRig.hpp>

namespace Native::anim
{
struct AnimatedObjectPartUpdateContext
{
	RED4ext::QsTransform* unk00;
	RED4ext::QsTransform* unk08;
	RED4ext::QsTransform* unk10;
	RED4ext::QsTransform* unk18;
	RED4ext::WorldTransform* unk20;
	RED4ext::anim::MetaRig* metaRig;
	void* unk30;
	Native::anim::MetaPose* metaPose;
};

struct AnimatedObjectPart
{
	uint8_t unk00[0x08 - 0x00];
	AnimatedObjectPart* child;
	AnimatedObjectPart* parent;
	bool isDirty;
	RED4ext::anim::AnimGraph* animGraph;
	RED4ext::UniquePtr<AnimInstanceBuffer> instance;
	RED4ext::ResourcePath facialSetupPath;
	void* unk38;
	RED4ext::Handle<RED4ext::anim::Rig> rig;
	RED4ext::DynArray<RED4ext::CName> tags;
	RED4ext::DynArray<RED4ext::CName> visualTags;
	uint8_t unk70[0x2490 - 0x70];
	RED4ext::QsTransform localToParent;
	RED4ext::QsTransform localToRoot;
	RED4ext::WorldTransform localToWorld;
	uint8_t unk2510[0x2548 - 0x2510];
	uint8_t unk2548[0x2560 - 0x2548];
	uint8_t unk2560[0x2580 - 0x2560];
	RED4ext::DynArray<RED4ext::anim::AnimGraphExternalEvent> m_externalEvents;
	uint8_t unk2590[0x25a8 - 0x2590];
	RED4ext::ent::AnimatedComponent* component;
	uint8_t unk25b0[0x25b8 - 0x25b0];
	RED4ext::DynArray<RED4ext::CName> unk25b8;
	bool forceReferencePose;
	int16_t metaRigRootBoneIndex;
};
RED4EXT_ASSERT_SIZE(AnimatedObjectPart, 0x25D0);
}

NATIVE_INFO(Native::anim::AnimatedObjectPart)
{
	NATIVE_MEMBER_FN(
		void, UpdateMetaPose,(Native::anim::AnimatedObjectPartUpdateContext&, Native::anim::Pose&, uint32_t), 
		2074943978
	);
};
