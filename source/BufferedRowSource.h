#pragma once
#include "RowSourceInterface.h"
#include "RowCache.h"
#include "ImgprocEngineExceptions.h"
#include "SafeArith.h"

template <typename ElemType>
class BufferedRowSource final
	: public RowSourceInterface<ElemType>
{
public:
	using RowCacheType = RowCache<ElemType, int>;
	using RowCachePtr = std::shared_ptr<RowCacheType>;

public:
	explicit BufferedRowSource(const cv::Size& imageSize)
		: m_imageSize(CtorValidateImageSizeElseThrow(imageSize))
		, m_rowCache()
	{
		const size_t elemsPerRow = SafeArith::ToSizeT_Positive(imageSize.width);
		const size_t initialCount = 0u;
		const size_t reserveCount = 0u;
		const size_t maxCount = SafeArith::ToSizeT_Positive(imageSize.height);
		m_rowCache = std::make_shared<RowCacheType>(
			elemsPerRow, initialCount, reserveCount, maxCount);
	}

	explicit BufferedRowSource(const cv::Size& imageSize, RowCachePtr rowCache)
		: m_imageSize(CtorValidateImageSizeElseThrow(imageSize))
		, m_rowCache(rowCache)
	{
		static const char* methodName = "BufferedRowSource::BufferedRowSource";
		if (!rowCache)
		{
			throw NullSharedPointerException(methodName);
		}
		const size_t elemsPerRowFromImageSize = SafeArith::ToSizeT_Positive(imageSize.width);
		const size_t elemsPerRowFromCache = m_rowCache->ElemsPerRow();
		if (elemsPerRowFromImageSize != elemsPerRowFromCache)
		{
			throw RectSizeMismatchException(methodName);
		}
	}

	~BufferedRowSource()
	{
	}

public:
	// 
	// Access the underlying row cache, which gives ability to:
	//
	// (1) Check if a certain row has been populated.
	//     (This is useful for error-checking, but don't do it 
	//     proactively - it may encourage bad programming habits)
	//
	// (2) Write the the row cache. Only the algorithm class which
	//     "owns" this BufferedRowSource should ever do this.
	// 
	RowCachePtr GetRowCache() const
	{
		return m_rowCache;
	}

public:
	cv::Size ImageSize() const override final
	{
		return m_imageSize;
	}

	const ElemType* Read(int row) override final
	{
		return m_rowCache->Read(row);
	}

	void Remove(int row) override final
	{
		m_rowCache->Remove(row);
	}

private:
	static cv::Size CtorValidateImageSizeElseThrow(cv::Size imageSize)
	{
		static const char* methodName = "BufferedRowSource::CtorValidateImageSizeElseThrow";
		if ((imageSize.width <= 0) ||
			(imageSize.height <= 0))
		{
			throw InvalidArgument(methodName);
		}
		//
		// TODO: 
		// for existing versions of OpenCV, also need to check that 
		// "area" (width multiply height) doesn't cause arithmetic overflow.
		//
		// Since this might change in the future, this TODO check 
		// isn't added to SafeArith.
		//
		return imageSize;
	}

private:
	cv::Size m_imageSize;
	RowCachePtr m_rowCache;
};
