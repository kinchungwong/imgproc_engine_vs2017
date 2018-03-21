#include "stdafx.h"
#include "SafeArith.h"

size_t SafeArith::Add(size_t first, size_t second)
{
	// TODO check overflow
	return (first + second);
}

size_t SafeArith::Multiply(size_t first, size_t second)
{
	// TODO check overflow
	return (first * second);
}

size_t SafeArith::Divide(size_t first, size_t second)
{
	// TODO check division by zero
	return (first / second);
}

size_t SafeArith::Modulo(size_t first, size_t second)
{
	// TODO check divisor overflow, also modulo (division) by zero
	return (first % second);
}

size_t SafeArith::ToSizeT_Positive(int value)
{
	// TODO
	return (size_t)value;
}
