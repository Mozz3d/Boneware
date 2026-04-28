#pragma once

#include <RED4ext/Scripting/Natives/Generated/anim/AnimVariableContainer.hpp>
#include <Native/anim/AnimInstanceVar.hpp>

NATIVE_INFO(RED4ext::anim::AnimVariableContainer)
{
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<bool>, m_boolArrayVar, 0x1b8)
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<int>, m_intArrayVar, 0x1d0)
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<float>, m_floatArrayVar, 0x1e8)
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<RED4ext::Vector3>, m_vectorArrayVar, 0x200)
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<RED4ext::Quaternion>, m_quaternionArrayVar, 0x218)
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<RED4ext::QsTransform>, m_transformArrayVar, 0x230)
};
