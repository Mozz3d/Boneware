#pragma once

#include <RED4ext/Scripting/Natives/animAnimatedObject.hpp>

#include <Native/anim/MetaRig.hpp>
#include <Native/anim/MetaPose.hpp>
#include <Native/anim/AnimatedObjectPart.hpp>
#include <Native/anim/AnimStreamingContextEntry.hpp>

#include <RED4ext/Scripting/Natives/entEntity.hpp>

namespace Native::anim
{
struct AnimatedObjectUpdateContext
{
	uint8_t unk00[0x20];				   // 00
	r4e::QsTransform* unk20;			   // 20
	void* unk28;						   // 28
	bool m_rebuiltHierarchy;			   // 30
	uint64_t unk38;						   // 38
	float unk40;						   // 40
	float m_distanceTimeDelta;			   // 44
	double unk48;						   // 48
	r4e::WorldTransform m_localToWorld;	   // 50
	uint64_t unk70;						   // 70
	uint64_t unk78;						   // 78
	ntv::anim::MetaRigBank* m_metaRigBank; // 80
	uint8_t unk88;						   // 88
	uint64_t unk90;						   // 90
	uint32_t unk98;						   // 98
	bool m_shouldSampleGraph;			   // 9C
	bool m_forceUpdate;					   // 9D
	void* m_animatedObject;				   // A0
	r4e::ent::Entity* m_entity;			   // A8
	uint64_t unkB0;						   // B0
	uint64_t unkB8;						   // B8
	uint64_t unkC0;						   // C0
	uint64_t unkC8;						   // C8
	uint32_t unkD0;						   // D0
	bool unkD4;							   // D4
	uint8_t unkD5;						   // D5
	uint64_t unkD8;						   // D8
	float unkE0;						   // E0
	uint32_t unkE4;						   // E4
	int16_t m_metaRigHeadIndex;			   // E8
	bool unkEA;							   // EA
	uint8_t unkEB;						   // EB
	uint8_t unkEC;						   // EC
	bool unkED;							   // ED
	uint8_t unkEE;						   // EE
};
}

NATIVE_INFO(r4e::anim::AnimatedObject)
{
	NATIVE_MEMBER_FUNC(
	bool ,IsHierarchyDirty,() const,                        2843545902);

	NATIVE_MEMBER_FUNC(
	void ,RebuildHierarchy,(ntv::anim::MetaRigBank&),       4293007027);

	NATIVE_MEMBER_FUNC(
	void ,UpdateDistanceCategory,(float),                   569512834);

	NATIVE_MEMBER_FUNC(
	void ,Update,(ntv::anim::AnimatedObjectUpdateContext&), 2251364700);


	NATIVE_DATA_MEMBER(
	ntv::anim::MetaRigReference, m_metaRigRef,                                     0x00);

	NATIVE_DATA_MEMBER(
	r4e::UniquePtr<ntv::anim::MetaPose> ,m_metaPose,                               0x18);

	NATIVE_DATA_MEMBER(
	r4e::QsTransform ,m_unkTransform30,                                            0x30);

	NATIVE_DATA_MEMBER(
	ntv::anim::AnimatedObjectPart* ,m_rootPart,                                    0x60);

	NATIVE_DATA_MEMBER(
	uint32_t ,unk68,															   0x68);

	NATIVE_DATA_MEMBER(
	void* ,unk70,																   0x70);

	NATIVE_DATA_MEMBER(
	r4e::DynArray<ntv::anim::AnimStreamingContextEntry> ,m_streamingContexts,      0x78);

	NATIVE_DATA_MEMBER(
	r4e::DynArray<ntv::anim::AnimStreamingContextEntry> ,m_dirtyStreamingContexts, 0x88);

	NATIVE_DATA_MEMBER(
	bool ,m_hasDirtyStreamingContexts,                                             0x98);

	NATIVE_DATA_MEMBER(
	uint32_t ,m_distanceCategory,												   0x9C);

	NATIVE_DATA_MEMBER(
	float ,unkA0,																   0xA0);

	NATIVE_DATA_MEMBER(
	uint8_t ,unkE0,																   0xE0);

	NATIVE_DATA_MEMBER(
	float ,unkE8,																   0xE8);

	NATIVE_DATA_MEMBER(
	uint32_t ,unkEC,                                                               0xEC);
};
