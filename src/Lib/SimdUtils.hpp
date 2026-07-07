#pragma once

namespace Lib::simd
{
    inline __m128 QuatMulUnsafe(__m128 aQuatA, __m128 aQuatB)
    {
        const __m128 aRev = _mm_shuffle_ps(aQuatA, aQuatA, 0x1B);
        const __m128 bYXYX = _mm_shuffle_ps(aQuatB, aQuatB, 0x11);
        const __m128 bWZWZ = _mm_shuffle_ps(aQuatB, aQuatB, 0xBB);

        const __m128 hs = _mm_hsub_ps(_mm_mul_ps(bYXYX, aQuatA), _mm_mul_ps(bWZWZ, aRev));
        const __m128 ha = _mm_hadd_ps(_mm_mul_ps(bWZWZ, aQuatA), _mm_mul_ps(bYXYX, aRev));

        const __m128 r = _mm_addsub_ps(_mm_shuffle_ps(ha, hs, 0xE4), _mm_shuffle_ps(hs, ha, 0xB1));
        return _mm_shuffle_ps(r, r, 0x9C);
    }

    inline __m128 RotateUnsafe(__m128 aQuat, __m128 aVector)
    {
        const __m128 qYZX = _mm_shuffle_ps(aQuat, aQuat, 0xC9);

        __m128 t = _mm_sub_ps(
            _mm_mul_ps(_mm_shuffle_ps(aVector, aVector, 0xC9), aQuat),
            _mm_mul_ps(qYZX, aVector));
        t = _mm_shuffle_ps(t, t, 0xC9);
        t = _mm_add_ps(t, t);

        __m128 c = _mm_sub_ps(
            _mm_mul_ps(_mm_shuffle_ps(t, t, 0xC9), aQuat),
            _mm_mul_ps(qYZX, t));
        c = _mm_shuffle_ps(c, c, 0xC9);

        const __m128 wt = _mm_mul_ps(_mm_shuffle_ps(aQuat, aQuat, 0xFF), t);
        return _mm_add_ps(_mm_add_ps(wt, c), aVector);
    }

    // ?Normalize4@QuadHelper@simd@@YAPEAU__m128@@PEAU2@@Z
    inline __m128 Normalize4(__m128 aQuad)
    {
        const __m128 dot = _mm_dp_ps(aQuad, aQuad, 0xFF);
        return _mm_andnot_ps(_mm_cmpeq_ps(dot, _mm_setzero_ps()), _mm_div_ps(aQuad, _mm_sqrt_ps(dot)));
    }
}