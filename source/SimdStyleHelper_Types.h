#pragma once

namespace simd_style_helper
{
	//
	// IMPORTANT TODO:
	//
	// Need to add compiler-vendor-specific directives to keep
	// all structs aligned, when allocated locally (on the stack).
	// 
	// Need to make sure these can't be dynamically allocated,
	// because dynamically allocated objects don't meet the 
	// alignment assumption.
	//
	// Alignment for these structs is important because it enables
	// store-to-load forwarding of SIMD intermediate results that 
	// spilled over to memory. This effectively extends the number 
	// of CPU SIMD registers to hundreds, at lower access speed.
	//

	using U8 = uint8_t;
	using V128 = __m128i;
	using U8x16 = V128;

	struct U8x48
	{
		union
		{
			U8 u8[48u];
			V128 v128[3u];
			struct
			{
				// for those insisting on nice names
				U8x16 leftVec;
				U8x16 centerVec;
				U8x16 rightVec;
			};
		};
	};
	static_assert(sizeof(U8x48) == 48u, "SIMD union type failure");

	struct U8x48x3
	{
		union
		{
			U8 u8[48u * 3u];
			V128 v128[9u];
			U8x48 rows[3u];
			struct
			{
				// for those insisting on nice names
				U8x48 topRow;
				U8x48 midRow;
				U8x48 botRow;
			};
		};
	};
	static_assert(sizeof(U8x48x3) == (48u * 3u), "SIMD union type failure");
}
