#pragma once

inline RED4ext::Quaternion& operator*=(RED4ext::Quaternion& lhs, const RED4ext::Quaternion& rhs)
{
    lhs = lhs * rhs;
    return lhs;
}