#pragma once

#include <RED4ext/Scripting/Natives/Generated/QsTransform.hpp>

NATIVE_INFO(r4e::QsTransform)
{
	NATIVE_MEMBER_FUNC(
	void ,SetMulInverseMulUnsafe,(r4e::QsTransform const&, r4e::QsTransform const&), 1902711854);

	NATIVE_MEMBER_FUNC(
	void ,SetMulUnsafe,(r4e::QsTransform const&, r4e::QsTransform const&),           2682196004);
};
