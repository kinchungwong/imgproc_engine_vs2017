#pragma once

//
// Performs basic arithmetic checks, such as overflows, underflows, 
// out-of-range conversion, and divisions-by-zero.
//
// This is a mock. Currently the class doesn't do any checks yet.
// In the future, this will be replaced by a real checked arithmetic 
// library.
//
class SafeArith
{
public:
	static size_t Add(size_t first, size_t second);
	static size_t Multiply(size_t first, size_t second);
	static size_t Divide(size_t first, size_t second);
	static size_t Modulo(size_t first, size_t second);
	static size_t ToSizeT_Positive(int value);

private:
	// Static class. Not instantiable.
	SafeArith() = delete;
	~SafeArith() = delete;
};
