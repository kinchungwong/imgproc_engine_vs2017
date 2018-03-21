#pragma once

class RectGridCorrespondence;

//
// An execution engine that process from input to output by 
// looping over output tiles.
//
class RectGridCorrespondenceLoopBody
{
public:
	RectGridCorrespondenceLoopBody(std::shared_ptr<RectGridCorrespondence> corresp);

public:
	void SetParallel(bool useParallel);
	bool GetParallel() const;

public:
	using ForEachFunction = std::function<void(
		const cv::Point& outputCellIndex,
		const cv::Rect& inputBoundingRect,
		const cv::Rect& outputCellRect)>;

	void ForEach(ForEachFunction correspFunc) const;

private:
	std::shared_ptr<RectGridCorrespondence> m_corresp;
	cv::Size m_outputGridSize;
};
