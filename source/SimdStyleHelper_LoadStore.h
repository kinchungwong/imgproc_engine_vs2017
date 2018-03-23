#pragma once
#include "SimdStyleHelper_Types.h"

namespace simd_style_helper
{
	// Unaligned load.
	// There is no aligned load, because all aligned load happens 
	// via the __m128i pseudo-value-type. These pseudo-value-type 
	// end up either in CPU vector registers, or via locally 
	// allocated structs on the stack, which are always aligned.
	// 
	V128 V128Load(const void* ptr);

	V128 V128Load(const void* ptr, size_t byteOffset);

	void V128Store(void* ptr, const V128& value);

	void V128Store(void* ptr, size_t byteOffset, const V128& value);
}
