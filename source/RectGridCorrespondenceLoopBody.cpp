#include "stdafx.h"
#include "RectGridCorrespondenceLoopBody.h"
#include "RectGridInterface.h"
#include "RectGridCorrespondence.h"
#include "RectGridLoopBody.h"

RectGridCorrespondenceLoopBody::RectGridCorrespondenceLoopBody(
	std::shared_ptr<RectGridCorrespondence> corresp)
	: m_corresp(corresp)
{
	auto outputGrid = m_corresp->GetOutputRectGrid();
	m_outputGridSize = outputGrid->GridSize();
}

void RectGridCorrespondenceLoopBody::SetParallel(bool useParallel)
{
}

bool RectGridCorrespondenceLoopBody::GetParallel() const
{
}

void RectGridCorrespondenceLoopBody::ForEach(ForEachFunction correspFunc) const
{
	auto outputGrid = m_corresp->GetOutputRectGrid();
	RectGridLoopBody outputLoopBody(*outputGrid);
	auto outputCellFunc = [&](const cv::Point& outputCellIndex, const cv::Rect& outputRect)
	{
		const cv::Rect inputBoundingRect = 
			this->m_corresp->GetInputBoundingRectForOutputCellIndex(outputCellIndex);
		correspFunc(outputCellIndex, inputBoundingRect, outputRect);
	};
	outputLoopBody.ForEach(outputCellFunc);
}
