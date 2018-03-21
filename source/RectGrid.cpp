#include "stdafx.h"
#include "RectGrid.h"
#include "ImgprocEngineExceptions.h"

RectGrid::RectGrid(const cv::Size& imageSize, const cv::Size& cellSize)
	: m_imageSize(imageSize)
{
	m_horzMarks;
	m_vertMarks;
}

RectGrid::~RectGrid()
{
}

cv::Size RectGrid::ImageSize() const
{
	return m_imageSize;
}

cv::Size RectGrid::GridSize() const
{
	return m_gridSize;
}

cv::Size RectGrid::MinCellSize() const
{
	return m_minCellSize;
}

cv::Size RectGrid::MaxCellSize() const
{
	return m_maxCellSize;
}

cv::Rect RectGrid::GetCellByIndex(const cv::Point& cellIndex) const
{
	ThrowIfCellIndexInvalid(cellIndex);
	int left = m_horzMarks.at(cellIndex.x);
	int right = m_horzMarks.at(cellIndex.x + 1);
	int top = m_horzMarks.at(cellIndex.y);
	int bottom = m_horzMarks.at(cellIndex.y + 1);
	return cv::Rect(left, top, right - left, bottom - top);
}

cv::Rect RectGrid::GetCellByImagePoint(const cv::Point& imagePoint) const
{
	static const char* methodName = "RectGrid::GetCellByImagePoint";
	throw NotImplemented(methodName);
}

void RectGrid::ThrowIfCellIndexInvalid(const cv::Point& cellIndex) const
{
	static const char* methodName = "RectGrid::ThrowIfCellIndexInvalid";
	if ((cellIndex.x < 0) ||
		(cellIndex.x >= m_gridSize.width) ||
		(cellIndex.y < 0) ||
		(cellIndex.y >= m_gridSize.height))
	{
		throw InvalidRectGridCellIndex(methodName);
	}
}
