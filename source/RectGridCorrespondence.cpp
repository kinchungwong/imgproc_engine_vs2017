#include "stdafx.h"
#include "RectGridCorrespondence.h"
#include "RectGridInterface.h"
#include "ImgprocEngineExceptions.h"

RectGridCorrespondence::RectGridCorrespondence(
	const cv::Size& inputSize, 
	std::shared_ptr<RectGridInterface> outputRectGrid,
	OutputToInputFunction outputInputFunc)
{
	static const char* methodName = "RectGridCorrespondence::RectGridCorrespondence";
	if (!outputRectGrid)
	{
		throw NullSharedPointerException(methodName);
	}
	if (!outputInputFunc)
	{
		throw NullFunctionException(methodName);
	}
	m_inputSize = inputSize;
	m_rectGrid = outputRectGrid;
	m_outputSize = m_rectGrid->ImageSize();
	m_outputInputFunc = outputInputFunc;
}

RectGridCorrespondence::~RectGridCorrespondence()
{
}

cv::Size RectGridCorrespondence::InputImageSize() const
{
	return m_inputSize;
}

cv::Size RectGridCorrespondence::OutputImageSize() const
{
	return m_outputSize;
}

std::shared_ptr<RectGridInterface> RectGridCorrespondence::GetOutputRectGrid() const
{
	return m_rectGrid;
}

cv::Point2d RectGridCorrespondence::ToInputPoint(const cv::Point2d& outputPoint) const
{
	return m_outputInputFunc(outputPoint);
}

cv::Rect RectGridCorrespondence::GetInputBoundingRectForOutputCellIndex(const cv::Point& outputCellIndex) const
{
	static const char* methodName = "RectGridCorrespondence::GetInputBoundingRectForOutputCellIndex";
	// some complicated calculations;
	// need to call "m_outputInputFunc" many times
	// For AFFINE, only need to call four corners
	// cached upon first use 
	throw NotImplemented(methodName);
}
