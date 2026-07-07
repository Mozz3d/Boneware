#pragma once

#include <Native/anim/AnimGraph.hpp>
#include <Native/anim/AnimInstanceBuffer.hpp>
#include <Native/anim/AnimDataContext.hpp>
#include <Native/anim/MetaPose.hpp>
#include <Native/anim/Pose.hpp>
#include <Native/anim/Rig.hpp>

#include <RED4ext/Scripting/Natives/Generated/anim/AnimGraphExternalEvent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/AnimatedComponent.hpp>

namespace Native::anim
{
struct AnimatedObjectPartUpdateContext
{
	r4e::QsTransform* deltaTransform;  // 00
	r4e::QsTransform* unk08;           // 08
	r4e::QsTransform* partToParent;    // 10
	r4e::QsTransform* partToRoot;      // 18
	r4e::WorldTransform* partToWorld;  // 20
	const r4e::anim::MetaRig* metaRig; // 28
	const void* unk30;				   // 30
	ntv::anim::MetaPose* metaPose;	   // 38
	void* unkStructPtr40;			   // 40
	uint64_t globalTimeMs;			   // 48
	float unk50;					   // 50
	float unk54;					   // 54
	double globalTimeS;				   // 58
	uint64_t unk60;					   // 60
	void* unk68;					   // 68
	uint8_t unk70;					   // 70
	uint64_t unk78;					   // 78
	uint32_t unk80;					   // 80
	void* animatedObject;			   // 88
	uint64_t unk90;					   // 90
	void* unk98;					   // 98
	uint64_t unkA0;					   // A0
	uint64_t unkA8;					   // A8
	bool shouldSampleGraph;			   // B0
	r4e::ent::Entity* entity;		   // B8
	uint32_t distanceCategory;		   // C0
	float unkC4;					   // C4
	float unkC8;					   // C8
	uint8_t unkCC;					   // CC
	uint64_t unkD0;					   // D0
	uint64_t unkD8;				       // D8
	uint64_t unkE0;					   // E0
	uint32_t* unkE8;				   // E8
	bool* unkF0;					   // F0
	uint8_t unkF8;					   // F8
	uint32_t* unk100;				   // 100
	uint64_t* unk108;				   // 108
	float* unk110;					   // 110
	uint32_t* unk118;			       // 118
	uint8_t* unk120;				   // 120
};
RED4EXT_ASSERT_SIZE(AnimatedObjectPartUpdateContext, 0x128);

struct AnimatedObjectPart
{

	inline bool IsFacial()
	{
		return !m_facialSetupPath.IsEmpty();
	}

	inline bool IsDangle()
	{
		return m_animGraph && NTV_GET(m_animGraph,unkF0);
	}

	inline bool IsDeformation()
	{
		return m_rig && m_rig->turningOffUpdateAndSample && m_animGraph && !NTV_GET(m_animGraph,unkF0);
	}

	uint8_t unk00[0x08 - 0x00];
	AnimatedObjectPart* m_child;									   // 08
	AnimatedObjectPart* m_parent;									   // 10
	bool m_isDirty;													   // 18
	r4e::anim::AnimGraph* m_animGraph;								   // 20
	r4e::UniquePtr<AnimInstanceBuffer> m_instance;					   // 28
	r4e::ResourcePath m_facialSetupPath;							   // 30
	void* unk38;
	r4e::Handle<r4e::anim::Rig> m_rig;								   // 40
	r4e::DynArray<r4e::CName> m_tags;								   // 50
	r4e::DynArray<r4e::CName> m_visualTags;							   // 60
	uint8_t unk70[0xe0 - 0x70];
	uint8_t unkE0;
	uint8_t unkE1[0x2490 - 0xe1];
	r4e::QsTransform localToParent;									   // 2490
	r4e::QsTransform localToRoot;									   // 24c0
	r4e::WorldTransform localToWorld;								   // 24f0
	r4e::QsTransform unkQsTransform2510;							   // 2510
	uint64_t unk2540;
	AnimDataContext m_dataContext;									   // 2548
	uint8_t unk2560[0x2580 - 0x2560];
	r4e::DynArray<r4e::anim::AnimGraphExternalEvent> m_externalEvents; // 2580
	r4e::SharedPtr<void> unkSharedPtr2590;
	uint32_t unk25A0;
	r4e::ent::AnimatedComponent* component;							   // 25a8
	uint8_t unk25b0;
	bool m_updateSkipped;											   // 25b1
	uint8_t unk25b2[0x25b8 - 0x25b2];
	r4e::DynArray<r4e::CName> unk25b8;
	bool forceReferencePose;										   // 25c8
	int16_t metaRigRootBoneIndex;									   // 25ca
};
RED4EXT_ASSERT_SIZE(AnimatedObjectPart, 0x25D0);
}

NATIVE_INFO(ntv::anim::AnimatedObjectPart)
{
	NATIVE_MEMBER_FUNC(
	bool ,IsDeformation,() const,																	3146191250);

	NATIVE_MEMBER_FUNC(
	bool ,IsDangle,() const,																		1517555557);

	NATIVE_MEMBER_FUNC(
	bool ,ShouldSample,(uint32_t) const,															3746632205);

	NATIVE_MEMBER_FUNC(
	bool ,UpdateInputs,(ntv::anim::AnimatedObjectPart&),											2907574611);

	NATIVE_MEMBER_FUNC(
	void ,CopyInputsFrom,(ntv::anim::AnimatedObjectPart&),											1142166387);

	NATIVE_MEMBER_FUNC(
	void ,Update,(ntv::anim::AnimatedObjectPartUpdateContext&),									    1991448876);

	NATIVE_MEMBER_FUNC(
	void ,UpdateMetaPose,(ntv::anim::AnimatedObjectPartUpdateContext&, ntv::anim::Pose&, uint32_t), 2074943978);
};
