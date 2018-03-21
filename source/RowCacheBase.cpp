#include "stdafx.h"
#include "RowCacheBase.h"
#include "ImgprocEngineExceptions.h"
#include "SafeArith.h"

RowCacheBase::RowCacheBase(
	size_t bytesPerRow,
	size_t initialCount,
	size_t reserveCount,
	size_t maxCount)
	: m_bytesPerRow(bytesPerRow)
	, m_maxCount(maxCount)
{
	static const char* methodName = "RowCacheBase::RowCacheBase";
	reserveCount = std::max<size_t>(initialCount, reserveCount);
	if (reserveCount > m_maxCount)
	{
		throw InvalidArgument(methodName);
	}
	m_occupied.reserve(reserveCount);
	m_unused.reserve(reserveCount);
	EnsureUnusedAtLeast(initialCount);
}

RowCacheBase::~RowCacheBase()
{
}

size_t RowCacheBase::BytesPerRow() const
{
	return m_bytesPerRow;
}

size_t RowCacheBase::Allocated() const
{
	// SafeArith not needed, based on the following assessment:
	// to have reached the point where these two numbers might overflow,
	// it must have already allocated a huge amount of memory 
	// at a prior time, which is impossible.
	return (Occupied() + Unused());
}

size_t RowCacheBase::Occupied() const
{
	return m_occupied.size();
}

size_t RowCacheBase::Unused() const
{
	return m_unused.size();
}

bool RowCacheBase::Contains(size_t key) const
{
	auto iter = m_occupied.find(key);
	return (iter != m_occupied.end());
}

void* RowCacheBase::Get(size_t key)
{
	auto iter = m_occupied.find(key);
	if (iter == m_occupied.end())
	{
		EnsureUnusedAtLeast(1u);
		auto buffer = std::move(m_unused.back());
		m_unused.pop_back();
		iter = m_occupied.emplace(key, std::move(buffer)).first;
	}
	return iter->second.Get();
}

void RowCacheBase::Remove(size_t key)
{
	static const char* methodName = "RowCacheBase::Remove";
	auto iter = m_occupied.find(key);
	if (iter == m_occupied.end())
	{
#if 0
		// optionally, throw exception (in strict mode)
		throw InvalidCollectionKeyOrIndex(methodName);
#else
		return;
#endif
	}
	auto buffer = std::move(iter->second);
	m_occupied.erase(iter);
	m_unused.push_back(std::move(buffer));
}

void RowCacheBase::EnsureUnusedAtLeast(size_t unusedAtLeast)
{
	static const char* methodName = "RowCacheBase::EnsureUnusedAtLeast";
	if (m_unused.size() >= unusedAtLeast)
	{
		return;
	}
	if (unusedAtLeast + m_occupied.size() > m_maxCount)
	{
		throw InvalidOperation(methodName);
	}
	m_unused.reserve(unusedAtLeast);
	while (m_unused.size() < unusedAtLeast)
	{
		m_unused.push_back(AlignedRow::Allocate(m_bytesPerRow));
	}
}
