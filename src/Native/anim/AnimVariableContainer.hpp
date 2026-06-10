#pragma once

#include <RED4ext/Scripting/Natives/Generated/anim/AnimVariableContainer.hpp>
#include <Native/anim/AnimInstanceVar.hpp>

NATIVE_INFO(RED4ext::anim::AnimVariableContainer)
{
	using VarIndexMap = RED4ext::HashMap<RED4ext::CName, int16_t>;
	NATIVE_FIELD(VarIndexMap, m_boolVarIndexMap,	   0x98);
	NATIVE_FIELD(VarIndexMap, m_intVarIndexMap,		   0xc8);
	NATIVE_FIELD(VarIndexMap, m_floatVarIndexMap,	   0xf8);
	NATIVE_FIELD(VarIndexMap, m_vectorVarIndexMap,	   0x128);
	NATIVE_FIELD(VarIndexMap, m_quaternionVarIndexMap, 0x158);
	NATIVE_FIELD(VarIndexMap, m_transformVarIndexMap,  0x1e8);
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<bool>,                 m_boolArrayVar,		  0x1b8);
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<int>,                  m_intArrayVar,		  0x1d0);
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<float>,                m_floatArrayVar,	  0x1e8);
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<RED4ext::Vector3>,     m_vectorArrayVar,	  0x200);
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<RED4ext::Quaternion>,  m_quaternionArrayVar, 0x218);
	NATIVE_FIELD(Native::anim::TAnimInstanceArrayVar<RED4ext::QsTransform>, m_transformArrayVar,  0x230);
};

static inline int16_t FindVarIndexFromMap(const RED4ext::HashMap<RED4ext::CName, int16_t>& aMap, RED4ext::CName aName)
{
	if (const auto index = aMap.Get(aName))
	{
		return *index;
	}
	return -1;
}
