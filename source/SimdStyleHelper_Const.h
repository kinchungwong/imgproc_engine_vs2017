#pragma once
#include "SimdStyleHelper_Types.h"

namespace simd_style_helper
{
	V128 VZero();

	V128 VAllSet();

	U8x16 FillBytes_One();

	U8x16 FillBytes(uint8_t fillValue);
}

