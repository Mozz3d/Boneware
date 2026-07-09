#pragma once

#include <Lib/SimdUtils.hpp>

namespace Lib::QsTransform
{
    inline r4e::QsTransform Identity()
    {
        return { {}, {}, {1.f, 1.f, 1.f, 1.f} };
    }

    // ?SetMulUnsafe@QsTransform@simd@@QEAAXAEBV12@0@Z
    inline void SetMulUnsafe(r4e::QsTransform& aTarget, const r4e::QsTransform& a, const r4e::QsTransform& b)
    {
        const __m128 aT = _mm_loadu_ps(&a.Translation.X);
        const __m128 aR = _mm_loadu_ps(&a.Rotation.i);
        const __m128 aS = _mm_loadu_ps(&a.Scale.X);
        const __m128 bT = _mm_loadu_ps(&b.Translation.X);
        const __m128 bR = _mm_loadu_ps(&b.Rotation.i);
        const __m128 bS = _mm_loadu_ps(&b.Scale.X);

        const __m128 scale = _mm_mul_ps(bS, aS);
        const __m128 translation = _mm_add_ps(Lib::simd::RotateUnsafe(aR, _mm_mul_ps(aS, bT)), aT);
        const __m128 rotation = Lib::simd::QuatMulUnsafe(aR, bR);

        _mm_storeu_ps(&aTarget.Scale.X, scale);
        _mm_storeu_ps(&aTarget.Translation.X, translation);
        _mm_storeu_ps(&aTarget.Rotation.i, rotation);
    }

    // ?SetMulInverseMulUnsafe@QsTransform@simd@@QEAAXAEBV12@0@Z
    inline void SetMulInverseMulUnsafe(r4e::QsTransform& aTarget, const r4e::QsTransform& a, const r4e::QsTransform& b)
    {
        const __m128 aT = _mm_loadu_ps(&a.Translation.X);
        const __m128 aR = _mm_loadu_ps(&a.Rotation.i);
        const __m128 aS = _mm_loadu_ps(&a.Scale.X);
        const __m128 bT = _mm_loadu_ps(&b.Translation.X);
        const __m128 bR = _mm_loadu_ps(&b.Rotation.i);
        const __m128 bS = _mm_loadu_ps(&b.Scale.X);

        const __m128 conjA = _mm_xor_ps(aR, _mm_set_ps(0.0f, -0.0f, -0.0f, -0.0f));
        const __m128 invScaleA = _mm_div_ps(_mm_set1_ps(1.0f), aS);

        const __m128 scale = _mm_mul_ps(bS, invScaleA);
        const __m128 translation = Lib::simd::RotateUnsafe(conjA, _mm_sub_ps(_mm_mul_ps(invScaleA, bT), aT));
        const __m128 rotation = Lib::simd::QuatMulUnsafe(conjA, bR);

        _mm_storeu_ps(&aTarget.Scale.X, scale);
        _mm_storeu_ps(&aTarget.Translation.X, translation);
        _mm_storeu_ps(&aTarget.Rotation.i, rotation);
    }
}