#include "stdafx.h"
#include "SimdStyleHelper_LoadStore.h"

namespace simd_style_helper
{
	// Unaligned load.
	// There is no aligned load, because all aligned load happens 
	// via the __m128i pseudo-value-type. These pseudo-value-type 
	// end up either in CPU vector registers, or via locally 
	// allocated structs on the stack, which are always aligned.
	// 
	V128 V128Load(const void* ptr)
	{
		return _mm_loadu_si128((const __m128i*)ptr);
	}

	V128 V128Load(const void* ptr, size_t byteOffset)
	{
		const uint8_t* ptr2 = ((const uint8_t*)ptr) + byteOffset;
		return _mm_loadu_si128((const __m128i*)ptr2);
	}

	void V128Store(void* ptr, const V128& value)
	{
		_mm_storeu_si128((__m128i*)ptr, value);
	}

	void V128Store(void* ptr, size_t byteOffset, const V128& value)
	{
		uint8_t* ptr2 = ((uint8_t*)ptr) + byteOffset;
		_mm_storeu_si128((__m128i*)ptr2, value);
	}
}
