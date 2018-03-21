#pragma once
#include "RowCacheBase.h"

template <typename ElemType, typename KeyType>
class RowCache final
	: private RowCacheBase
{
private:
	//static_assert(IsBlittable<ElemType>::value, "Not blittable");

public:
	RowCache(size_t elemsPerRow,
		size_t initialCount,
		size_t reserveCount,
		size_t maxCount);

	~RowCache();

public:
	using RowCacheBase::BytesPerRow;
	using RowCacheBase::Allocated;
	using RowCacheBase::Occupied;
	using RowCacheBase::Unused;

public:
	std::type_index ElemTypeId() const;
	size_t ElemsPerRow() const;

public:
	bool Contains(const KeyType& key) const;
	const ElemType* Read(const KeyType& key) const;
	ElemType* Write(const KeyType& key);
	void Remove(const KeyType& key);

private:
	size_t m_elemCount;
	std::unordered_map<KeyType, size_t> m_keyMapping;
	size_t m_nextUnderlyingKey;
};
