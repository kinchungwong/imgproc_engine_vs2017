#pragma once
#include "RectGridInterface.h"

class InvalidRectGridCellIndex : public std::exception
{
public:
	InvalidRectGridCellIndex(const std::string& msg)
		: std::exception()
	{
	}
};

class RectGrid final
	: public RectGridInterface
{
public:
	RectGrid(const cv::Size& imageSize, const cv::Size& cellSize);
	~RectGrid();

public:
	cv::Size ImageSize() const override final;
	cv::Size GridSize() const override final;
	cv::Size MinCellSize() const override final;
	cv::Size MaxCellSize() const override final;
	cv::Rect GetCellByIndex(const cv::Point& cellIndex) const override final;
	cv::Rect GetCellByImagePoint(const cv::Point& imagePoint) const override final;

private:
	void ThrowIfCellIndexInvalid(const cv::Point& cellIndex) const;

private:
	RectGrid& operator=(const RectGrid&) = delete;
	RectGrid& operator=(RectGrid&&) = delete;

private:
	const cv::Size m_imageSize;
	cv::Size m_gridSize;
	cv::Size m_minCellSize;
	cv::Size m_maxCellSize;
	std::vector<int> m_horzMarks;
	std::vector<int> m_vertMarks;
};
