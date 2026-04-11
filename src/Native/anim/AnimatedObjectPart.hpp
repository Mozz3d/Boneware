#pragma once

namespace Native::anim
{
struct AnimatedObjectPart
{
	uint8_t unk00[0x08 - 0x00];
	AnimatedObjectPart* child;
	AnimatedObjectPart* parent;
	bool isDirty;
	RED4ext::anim::AnimGraph* animGraph;
	void* animInstanceBuff;
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
	uint8_t unk2560[0x2578 - 0x2560];
	uint8_t unk2578[0x25a8 - 0x2578];
	RED4ext::ent::AnimatedComponent* component;
	uint8_t unk25b0[0x25b8 - 0x25b0];
	RED4ext::DynArray<RED4ext::CName> unk25b8;
	bool forceReferencePose;
	int16_t metaRigRootBoneIndex;
};
RED4EXT_ASSERT_SIZE(AnimatedObjectPart, 0x25D0);
}
