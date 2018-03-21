#pragma once

class RectGridInterface;

class RectGridLoopBody
{
public:
	//
	// Constructor.
	//
	// This constructor keeps a non-owning reference to an instance of
	// RectGridInterface.
	// 
	// RectGridLoopBody is cheap to construct and configure; therefore 
	// it should only be created in the smallest possible scope.
	//
	// If it is necessary to extend the lifetime of the RectGrid instance,
	// first create the RectGrid with a shared_ptr, then dereference
	// the shared_ptr when calling this constructor. The owner should
	// hold on to the shared_ptr in order to extend the lifetime.
	// 
	// 
	explicit RectGridLoopBody(const RectGridInterface& refRectGrid);
	~RectGridLoopBody();

public:
	using ForEachFunction = std::function<
		void(const cv::Point& cellIndex, 
			const cv::Rect& cellRect)>;

	// Parallelize options are:
	//
	// 0. no parallelization (sequential)
	//
	// 1. by row (each row guaranteed assigned to same thread)
	//
	// 2. by cell (no guarantee, any thread can process any cell)
	//
	// 3. staggered barriered
	//    Basically, guarantees that when one cell is executing,
	//    all eight neighbors (including diagonal neighbors) are not 
	//    being touched. As long as that is upheld, execution of cells
	//    can be parallelized.
	//
	//    example: barrier 0 : (even x, even y)
	//             barrier 1 : (even x, odd y)
	//             barrier 2 : (odd x, even y)
	//             barrier 3 : (odd x, odd y)
	//
	//    For four, configuration is 2x2
	//    For six, configuration is 2x3
	//    For nine, configuration is 3x3
	//
	//
	//void SetParallel();
	//void GetParallel() const;

	void ForEach(ForEachFunction func);

private:
	const RectGridInterface& m_refRectGrid;
	cv::Size m_imageSize;
	cv::Size m_gridSize;
};
