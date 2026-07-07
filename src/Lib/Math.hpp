#pragma once

inline RED4ext::Quaternion& operator*=(RED4ext::Quaternion& lhs, const RED4ext::Quaternion& rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

inline RED4ext::QsTransform QsIdentity()
{
    return { {}, {}, {1.f, 1.f, 1.f, 1.f} };
}
