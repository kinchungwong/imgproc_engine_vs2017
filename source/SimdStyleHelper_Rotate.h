#pragma once
#include "SimdStyleHelper_Types.h"
#include "SimdStyleHelper_Splice.h"

//
// Rotation of elements (by bytes)
// 
// For rotation of bits within elements, see BitRotate instead.
//

namespace simd_style_helper
{
	namespace rotate_helper
	{
		constexpr size_t Mod48Unsigned(int signedAmount)
		{
			return (signedAmount >= 0) ? (((uint32_t)signedAmount) % 48u)
				: (47u - ((uint32_t)(-(signedAmount + 1)) % 48u));
		}

		template <size_t amountDiv16>
		class V128RotateHelper;

		template <>
		class V128RotateHelper<0u>
		{
		public:
			static U8x48 Apply(const U8x48& input)
			{
				return input;
			}
		};

		template <>
		class V128RotateHelper<1u>
		{
		public:
			static U8x48 Apply(const U8x48& input)
			{
				U8x48 output;
				output.v128[0u] = input.v128[2u];
				output.v128[1u] = input.v128[0u];
				output.v128[2u] = input.v128[1u];
				return output;
			}
		};

		template <>
		class V128RotateHelper<2u>
		{
		public:
			static U8x48 Apply(const U8x48& input)
			{
				U8x48 output;
				output.v128[0u] = input.v128[1u];
				output.v128[1u] = input.v128[2u];
				output.v128[2u] = input.v128[0u];
				return output;
			}
		};

		template <size_t amountMod16>
		class ByteRotateHelper
		{
		public:
			static U8x48 Apply(const U8x48& input)
			{
				U8x48 output;
				output.v128[0u] = Splice<16u - amountMod16>(input.v128[2u], input.v128[0u]);
				output.v128[1u] = Splice<16u - amountMod16>(input.v128[0u], input.v128[1u]);
				output.v128[2u] = Splice<16u - amountMod16>(input.v128[1u], input.v128[2u]);
				return output;
			}
		};

		template <int signedByteAmount>
		class RotateHelper
		{
		public:
			static U8x48 Apply(const U8x48& input)
			{
				constexpr size_t amountMod48 = Mod48Unsigned(signedByteAmount);
				constexpr size_t amountDiv16 = (amountMod48 / 16u);
				constexpr size_t amountMod16 = (amountMod48 % 16u);
				const U8x48 stepOne = V128RotateHelper<amountDiv16>::Apply(input);
				const U8x48 stepTwo = ByteRotateHelper<amountMod16>::Apply(stepOne);
				return stepTwo;
			}
		};
	}

	template <int signedByteAmount>
	U8x48 U8x48_Rotate(const U8x48& input)
	{
		return rotate_helper::RotateHelper<signedByteAmount>::Apply(input);
	}
}
