#pragma once

#include <RED4ext/Scripting/Natives/Generated/anim/AnimGraph.hpp>
#include <Native/anim/AnimInstanceBuffer.hpp>
#include <Native/anim/Pose.hpp>

namespace Native::anim
{
struct AnimatedObjectPart;

struct AnimGraphSampleContext
{
	AnimInstanceBuffer* instance;
	Pose* pose;
	uint64_t unk10;
	uint64_t unk18;
	uint64_t unk20;
	uint64_t unk28;
	uint64_t unk30;
	RED4ext::QsTransform* localToParent;
	RED4ext::QsTransform* localToRoot;
	RED4ext::WorldTransform* localToWorld;
	AnimatedObjectPart* part;
	uint64_t unk58;
	uint32_t unk60;
	uint64_t unk68;
	uint64_t unk70;
	uint64_t unk78;
	uint64_t unk80;
	uint64_t unk88;
	uint64_t unk90;
	uint64_t unk98;
	uint64_t unkA0;
	uint32_t unkA8;
	float unkAC;
	uint32_t unkB0;
	uint8_t unkB4;
	RED4ext::Vector4 unkB8;
	uint8_t unkC8;
	uint64_t unkD0;
	uint64_t unkD8;
	bool hasFacialSetup;
	uint64_t unkE8;
	uint64_t unkF0;
	uint64_t unkF8;
	uint8_t unk100;
	bool unk101;
	uint8_t unk102;
};

struct SampleOutput
{
	Pose* pose;
	RED4ext::QsTransform* unkTransform08;
	RED4ext::QsTransform* unkTransform10;
};
}

NATIVE_INFO(RED4ext::anim::AnimGraph)
{
	NATIVE_MEMBER_FN(void, Sample,(Native::anim::AnimGraphSampleContext&) const, 2331448661);
	NATIVE_MEMBER_FN(void, ResetFeatures,(Native::anim::AnimInstanceBuffer&, bool), 248715065);
	NATIVE_MEMBER_FN(bool, SetInstanceBoolVar,(Native::anim::AnimInstanceBuffer&, RED4ext::CName, bool), 564992717);
	NATIVE_MEMBER_FN(bool, SetInstanceIntVar,(Native::anim::AnimInstanceBuffer&, RED4ext::CName, int), 110697064);
	NATIVE_MEMBER_FN(bool, SetInstanceFloatVar,(Native::anim::AnimInstanceBuffer&, RED4ext::CName, float), 111680109);

	NATIVE_FIELD(uint32_t, m_nextNodeID, 0x118);
};
