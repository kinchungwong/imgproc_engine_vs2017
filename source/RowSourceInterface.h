#pragma once

//
// Interface for any "image-like" source of pixel data.
// This interface supports reading only.
//
// Except for MatrixRowSource, other concrete implementation
// DO NOT necessarily guarantee any of these:
//
// (1) Contiguousness of rows in memory 
//     Neither gaplessness, nor constant stride (row step).
//
// (2) Availability of all rows
//     Concrete implementation may only keep several rows
//     allocated; attempting to read from unavailable rows
//     will throw exception.
//
// (3) ... TBD ...
//
template <typename ElemType>
class RowSourceInterface
{
public:
	virtual cv::Size ImageSize() const = 0;
	virtual const ElemType* Read(int row) = 0;
	virtual void Remove(int row) = 0;

public:
	virtual ~RowSourceInterface() = 0;

protected:
	RowSourceInterface();
};

// 
// The ctor and dtor below are syntactic only,
// and the inline is also syntactic (not codegen inline)
// therefore DO NOT replace with "force_inline" macro.
//

template <typename ElemType>
inline RowSourceInterface<ElemType>::RowSourceInterface()
{
}

template <typename ElemType>
inline RowSourceInterface<ElemType>::~RowSourceInterface()
{
}
