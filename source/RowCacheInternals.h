#pragma once

//
// Note: this class may be overkill. The only actual requirement
// is to protect the aligned buffer pointer with RAII. It should 
// not be necessary to wrap around "unique_ptr".
//
class AlignedRow
{
public:
	static AlignedRow Allocate(size_t byteCount);
	~AlignedRow();

public:
	AlignedRow(AlignedRow&&) = default;
	AlignedRow& operator= (AlignedRow&&) = default;

public:
	class Deleter
	{
	public:
		void operator()(void* p) const;
	};

public:
	using PtrType = std::unique_ptr<void, Deleter>;
	using DefaultAlignment = std::integral_constant<size_t, 16u>;

public:
	operator PtrType& ()
	{
		return m_ptr;
	}

	operator const PtrType& () const
	{
		return m_ptr;
	}

	void* Get()
	{
		return m_ptr.get();
	}

	const void* Get() const
	{
		return m_ptr.get();
	}

public:
	PtrType m_ptr;

private:
	explicit AlignedRow(PtrType&& ptr);

private:
	AlignedRow(const AlignedRow&) = delete;
	AlignedRow& operator= (const AlignedRow&) = delete;
};
