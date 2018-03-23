#include "stdafx.h"
#include "SimdStyleHelper_Const.h"

namespace simd_style_helper
{
	V128 VZero()
	{
		return _mm_setzero_si128();
	}

	V128 VAllSet()
	{
		__m128i zero = _mm_setzero_si128();
		return _mm_cmpeq_epi8(zero, zero);
	}

	U8x16 FillBytes_One()
	{
		__m128i zero = _mm_setzero_si128();
		__m128i minusOne = _mm_cmpeq_epi8(zero, zero);
		return _mm_subs_epi8(zero, minusOne);
	}

	U8x16 FillBytes(uint8_t fillValue)
	{
		return _mm_set1_epi8((char)fillValue);
	}
}
