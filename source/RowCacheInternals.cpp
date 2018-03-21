#include "stdafx.h"
#include "RowCacheInternals.h"

AlignedRow::AlignedRow(PtrType&& ptr)
	: m_ptr(std::move(ptr))
{
}

AlignedRow AlignedRow::Allocate(size_t byteCount)
{
	return AlignedRow(PtrType(_aligned_malloc(byteCount, DefaultAlignment::value)));
}

AlignedRow::~AlignedRow()
{
}

void AlignedRow::Deleter::operator()(void* p) const
{
	_aligned_free(p);
}
