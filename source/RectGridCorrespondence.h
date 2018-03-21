#pragma once

class RectGridInterface;

//
// Given a coordinate transform from one image to another,
// this class divides the output image's area into tiles,
// and computes the input bounding rectangle for each output 
// tile.
//
// This class can be used with RectGridCorrespondenceLoopBody
// to loop over the execution of a function that process those 
// tiles.
//
// Class name is subject to change.
//
class RectGridCorrespondence
{
public:
	using OutputToInputFunction = std::function<
		cv::Point2d(const cv::Point2d&) >;

public:
	RectGridCorrespondence(
		const cv::Size& inputSize, 
		std::shared_ptr<RectGridInterface> outputRectGrid,
		OutputToInputFunction outputInputFunc);

	~RectGridCorrespondence();

public:
	cv::Size InputImageSize() const;
	cv::Size OutputImageSize() const;
	std::shared_ptr<RectGridInterface> GetOutputRectGrid() const;

public:
	cv::Point2d ToInputPoint(const cv::Point2d& outputPoint) const;

public:
	cv::Rect GetInputBoundingRectForOutputCellIndex(const cv::Point& outputCellIndex) const;

private:
	cv::Size m_inputSize;
	cv::Size m_outputSize;
	std::shared_ptr<RectGridInterface> m_rectGrid;
	OutputToInputFunction  m_outputInputFunc;
};
