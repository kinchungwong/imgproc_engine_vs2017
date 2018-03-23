#pragma once
#include "SimdStyleHelper_Types.h"
#include "SimdStyleHelper_Splice.h"

// 
// Within-register byte alignment, by extracting N bytes from
// one register, and 16-N bytes from the other register.
// 
// Relies on simd_style_helper::Splice, which is responsible 
// for the choice of SSE2 or SSSE3 implementation.
//

namespace simd_style_helper
{
	namespace extract_at_helper
	{
		enum class Strategy
		{
			Invalid,
			NoOp,
			Splice
		};

		constexpr Strategy ChooseStrategy(size_t byteOffset)
		{
			return (byteOffset == 0u) ? Strategy::NoOp
				: ((byteOffset >= 1u) && (byteOffset <= 15u)) ? Strategy::Splice
				: (byteOffset == 16u) ? Strategy::NoOp
				: ((byteOffset >= 17u) && (byteOffset <= 31u)) ? Strategy::Splice
				: (byteOffset == 32u) ? Strategy::NoOp
				: Strategy::Invalid;
		}

		template <size_t byteOffset, Strategy = ChooseStrategy(byteOffset)>
		class ExtractAtHelper;

		template <size_t byteOffset>
		class ExtractAtHelper<byteOffset, Strategy::NoOp>
		{
		public:
			static U8x16 Apply(const U8x48& input)
			{
				return input.v128[byteOffset / 16u];
			}
		};

		template <size_t byteOffset>
		class ExtractAtHelper<byteOffset, Strategy::Splice>
		{
		public:
			static U8x16 Apply(const U8x48& input)
			{
				constexpr size_t lowerIndex = (byteOffset / 16u);
				constexpr size_t upperIndex = (lowerIndex + 1u);
				constexpr size_t spliceOffset = (byteOffset % 16u);
				U8x16 lower = input.v128[lowerIndex];
				U8x16 upper = input.v128[upperIndex];
				return Splice<spliceOffset>(lower, upper);
			}
		};

		template <size_t byteOffset>
		class ExtractAtHelper<byteOffset, Strategy::Invalid>
		{
		public:
			static U8x16 Apply(const U8x48& input)
			{
				static_assert(false, "Byte offset is out of range.");
			}
		};
	}

	template <size_t byteOffset>
	U8x16 ExtractAt(const U8x48& input)
	{
		return extract_at_helper::ExtractAtHelper<byteOffset>::Apply(input);
	}
}
