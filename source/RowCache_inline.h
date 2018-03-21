#pragma once
#include "RowCache.h"
#include "SafeArith.h"
#include "ImgprocEngineExceptions.h"

template <typename ElemType, typename KeyType>
RowCache<ElemType, KeyType>::RowCache(size_t elemsPerRow,
	size_t initialCount,
	size_t reserveCount,
	size_t maxCount)
	: RowCacheBase(
		SafeArith::Multiply(elemsPerRow, sizeof(ElemType)),
		initialCount, reserveCount, maxCount)
	, m_elemCount(elemsPerRow)
	, m_keyMapping()
	, m_nextUnderlyingKey()
{
}

template <typename ElemType, typename KeyType>
RowCache<ElemType, KeyType>::~RowCache()
{
}

template <typename ElemType, typename KeyType>
std::type_index RowCache<ElemType, KeyType>::ElemTypeId() const
{
	return std::type_index(typeid(ElemType));
}

template <typename ElemType, typename KeyType>
size_t RowCache<ElemType, KeyType>::ElemsPerRow() const
{
	return m_elemCount;
}

template <typename ElemType, typename KeyType>
bool RowCache<ElemType, KeyType>::Contains(const KeyType& key) const
{
	return (m_keyMapping.find(key) != m_keyMapping.end());
}

template <typename ElemType, typename KeyType>
const ElemType* RowCache<ElemType, KeyType>::Read(const KeyType& key) const
{
	static const char* methodName = "RowCache::Read";
	auto iter = m_keyMapping.find(key);
	if (iter == m_keyMapping.end())
	{
		throw RowCacheKeyNotFound(methodName);
	}
	const size_t underlyingKey = iter->second;
	return static_cast<const ElemType*>(RowCacheBase::Get(underlyingKey));
}

template <typename ElemType, typename KeyType>
ElemType* RowCache<ElemType, KeyType>::Write(const KeyType& key)
{
	auto iter = m_keyMapping.find(key);
	if (iter == m_keyMapping.end())
	{
		const size_t underlyingKey = (m_nextUnderlyingKey++);
		void* ptr = RowCacheBase::Get(underlyingKey);
		//
		// If we reached this line, the allocation is successful,
		// therefore it can be added. Otherwise, "m_keyMapping"
		// should not be modified.
		//
		m_keyMapping.emplace(key, underlyingKey);
		return static_cast<ElemType*>(ptr);
	}
	else
	{
		const size_t underlyingKey = iter->second;
		void* ptr = RowCacheBase::Get(underlyingKey);
		return static_cast<ElemType*>(ptr);
	}
}

template <typename ElemType, typename KeyType>
void RowCache<ElemType, KeyType>::Remove(const KeyType& key)
{
	auto iter = m_keyMapping.find(key);
	if (iter == m_keyMapping.end())
	{
		// or throw exception if in strict mode
		return;
	}
	const size_t underlyingKey = iter->second;
	m_keyMapping.erase(iter);
	RowCacheBase::Remove(underlyingKey);
}
