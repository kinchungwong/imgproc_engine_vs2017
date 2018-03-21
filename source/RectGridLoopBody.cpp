#include "stdafx.h"
#include "RectGridLoopBody.h"
#include "RectGridInterface.h"

RectGridLoopBody::RectGridLoopBody(const RectGridInterface& refRectGrid)
	: m_refRectGrid(refRectGrid)
	, m_imageSize(m_refRectGrid.ImageSize())
	, m_gridSize(m_refRectGrid.GridSize())
{
}

RectGridLoopBody::~RectGridLoopBody()
{
}

void RectGridLoopBody::ForEach(ForEachFunction func)
{
	// 
	// TODO parallelize
	//
	for (int gridRow = 0; gridRow < m_gridSize.height; ++gridRow)
	{
		for (int gridCol = 0; gridCol < m_gridSize.width; ++gridCol)
		{
			const cv::Point cellIndex(gridCol, gridRow);
			const cv::Rect cellRect = m_refRectGrid.GetCellByIndex(cellIndex);
			func(cellIndex, cellRect);
		}
	}
}
