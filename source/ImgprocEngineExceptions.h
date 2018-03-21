#pragma once

class InvalidArgument : public std::exception
{
	// see also NullPointerException, NullSharedPointerException
public:
	InvalidArgument(const std::string& msg)
		: std::exception()
	{
	}
};

class InvalidMemoryArrayIndex : public std::exception
{
	// This is only applicable for accessing memory, 
	// or memory-backed arrays.
public:
	InvalidMemoryArrayIndex(const std::string& msg)
		: std::exception()
	{
	}
};

class InvalidCollectionKeyOrIndex : public std::exception
{
	// This is applicable whenever a class method accepts
	// a lookup of anything, regardless of implementation 
	// detail. For example, an invalid lookup with 
	// set, map, unordered_set, unordered_map, vector,
	// can all throw this
public:
	InvalidCollectionKeyOrIndex(const std::string& msg)
		: std::exception()
	{
	}
};

class RowCacheKeyNotFound : public std::exception
{
	// see also InvalidCollectionKeyOrIndex
public:
	RowCacheKeyNotFound(const std::string& msg)
		: std::exception()
	{
	}
};

class InvalidOperation : public std::exception
{
	// see also LiskovViolation
public:
	InvalidOperation(const std::string& msg)
		: std::exception()
	{
	}
};

class NotImplemented : public std::exception
{
public:
	NotImplemented(const std::string& msg)
		: std::exception()
	{
	}
};

class LiskovViolation : public std::exception
{
	// see also InvalidOperation
public:
	LiskovViolation(const std::string& msg)
		: std::exception()
	{
	}
};

class NullPointerException : public std::exception
{
	// see also NullSharedPointerException 
public:
	NullPointerException(const std::string& msg)
		: std::exception()
	{
	}
};

class NullSharedPointerException : public std::exception
{
	// see also NullPointerException 
public:
	NullSharedPointerException(const std::string& msg)
		: std::exception()
	{
	}
};

class NullFunctionException : public std::exception
{
	// see also NullPointerException 
public:
	NullFunctionException(const std::string& msg)
		: std::exception()
	{
	}
};

class RectSizeMismatchException : public std::exception
{
public:
	RectSizeMismatchException(const std::string& msg)
		: std::exception()
	{
	}
};

class MatrixRankException : public std::exception 
{
public:
	MatrixRankException(const std::string& msg)
		: std::exception()
	{
	}
};
