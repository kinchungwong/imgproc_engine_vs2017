#pragma once

// 
// Requires SSSE3 for PALIGNR
//
// An SSE2 fallback is based on three instructions: 
// PSLLDQ, PSRLDQ, POR. However, this partially negates the 
// performance advantage over unaligned load from memory.
//

namespace simd_style_helper
{
	namespace splice_helper
	{
		enum class Strategy
		{
			Invalid,
			Left,
			Right,
			SSE2,
			SSSE3
		};

		constexpr Strategy ChooseStrategy(size_t byteOffset)
		{
			return (byteOffset == 0u) ? Strategy::Left
				: ((byteOffset >= 1u) && (byteOffset <= 15u)) ? Strategy::SSSE3
				: (byteOffset == 16u) ? Strategy::Right
				: Strategy::Invalid;
		}

		template <size_t byteOffset, Strategy = ChooseStrategy(byteOffset)>
		class SpliceHelper;

		template <size_t byteOffset>
		class SpliceHelper<byteOffset, Strategy::Left>
		{
		public:
			static U8x16 Apply(const U8x16& left, const U8x16& right)
			{
				return left;
			}
		};

		template <size_t byteOffset>
		class SpliceHelper<byteOffset, Strategy::Right>
		{
		public:
			static U8x16 Apply(const U8x16& left, const U8x16& right)
			{
				return right;
			}
		};

		template <size_t byteOffset>
		class SpliceHelper<byteOffset, Strategy::SSSE3>
		{
		public:
			static U8x16 Apply(const U8x16& left, const U8x16& right)
			{
				return _mm_alignr_epi8(right, left, byteOffset);
			}
		};

		template <size_t byteOffset>
		class SpliceHelper<byteOffset, Strategy::SSE2>
		{
		public:
			static U8x16 Apply(const U8x16& left, const U8x16& right)
			{
				return _mm_or_si128(
					_mm_srli_si128(left, byteOffset),
					_mm_slli_si128(right, 16u - byteOffset));
			}
		};


		template <size_t byteOffset>
		class SpliceHelper<byteOffset, Strategy::Invalid>
		{
		public:
			static U8x16 Apply(const U8x16& left, const U8x16& right)
			{
				static_assert(false, "Byte offset is out of range.");
			}
		};
	}

	template <size_t byteOffset>
	U8x16 Splice(const U8x16& left, const U8x16& right)
	{
		return splice_helper::SpliceHelper<byteOffset>::Apply(left, right);
	}

}
