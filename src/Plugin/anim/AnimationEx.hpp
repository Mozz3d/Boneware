#pragma once

#include <Native/anim/Animation.hpp>
#include <RED4ext/Scripting/Natives/animAnimationBufferCompressed.hpp>

NATIVE_INFO_ALIAS(AnimationEx, RED4ext::anim::Animation);

struct AnimationEx : RED4ext::anim::Animation
{
	const RED4ext::Handle<RED4ext::anim::AnimationBufferCompressed>& GetAnimBufferCompressed()
	{
		return Red::Cast<RED4ext::anim::AnimationBufferCompressed>(animBuffer);
	}

	RED4ext::DynArray<RED4ext::QsTransform> SampleTransforms(float aTime)
	{
		RED4ext::DynArray<RED4ext::QsTransform> outTransforms(GetAnimBufferCompressed()->numJoints);
		Native::anim::Pose pose{};
		pose.transforms = outTransforms.Data();
		pose.numTransforms = outTransforms.Size();
		pose.numAllTransforms = outTransforms.Size();
		// for some reason animations care about whether argument should be clamped or not?
		// this is inconvenient the reasons here so we just handle the clamping ourselves regardless
		float clamped = std::floor(aTime * 30.0f + 0.5f) / 30.0f;
		NATIVE_CALL(this,Sample(clamped, pose));
		return outTransforms;
	}

	RED4ext::DynArray<float> SampleTracks(float aTime)
	{
		RED4ext::DynArray<float> outTracks(GetAnimBufferCompressed()->numJoints);
		Native::anim::Pose pose{};
		pose.tracks = outTracks.Data();
		pose.numTracks = outTracks.Size();
		pose.numAllTracks = outTracks.Size();
		float clamped = std::floor(aTime * 30.0f + 0.5f) / 30.0f;
		NATIVE_CALL(this,Sample(clamped, pose));
		return outTracks;
	}
};

RTTI_EXPAND_CLASS(RED4ext::anim::Animation, AnimationEx,
	RTTI_METHOD(SampleTransforms);
	RTTI_METHOD(SampleTracks);
);
