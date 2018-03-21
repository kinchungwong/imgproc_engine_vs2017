#pragma once

class RectGridInterface
{
public:
	virtual cv::Size ImageSize() const = 0;
	virtual cv::Size GridSize() const = 0;
	virtual cv::Size MinCellSize() const = 0;
	virtual cv::Size MaxCellSize() const = 0;
	virtual cv::Rect GetCellByIndex(const cv::Point& cellIndex) const = 0;
	virtual cv::Rect GetCellByImagePoint(const cv::Point& imagePoint) const = 0;

public:
	virtual ~RectGridInterface() = 0;

protected:
	RectGridInterface();
};
