#pragma once
#include "RowCacheInternals.h"

//
// This is a base class, therefore all methods only accessible 
// by derived class.
//
// This class is non-template, by design.
//
class RowCacheBase
{
protected:
	RowCacheBase(
		size_t bytesPerRow,
		size_t initialCount,
		size_t reserveCount,
		size_t maxCount = (std::numeric_limits<int>::max)());

	~RowCacheBase();

protected:
	size_t BytesPerRow() const;
	size_t Allocated() const;
	size_t Occupied() const;
	size_t Unused() const;

protected:
	bool Contains(size_t key) const;
	void* Get(size_t key);
	void Remove(size_t key);

protected:
	void EnsureUnusedAtLeast(size_t unusedAtLeast);

protected:
	size_t m_bytesPerRow;
	size_t m_maxCount;
	std::unordered_map<size_t, AlignedRow> m_occupied;
	std::vector<AlignedRow> m_unused;
};
