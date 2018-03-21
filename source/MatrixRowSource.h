#pragma once
#include "RowSourceInterface.h"
#include "ImgprocEngineExceptions.h"

template <typename ElemType>
class MatrixRowSource final
	: public RowSourceInterface<ElemType>
{
public:
	MatrixRowSource(const cv::Mat_<ElemType>& mat)
		: m_mat(mat)
	{
		static const char* methodName = "MatrixRowSource::MatrixRowSource";
		if (mat.empty() ||
			mat.dims != 2)
		{
			throw MatrixRankException(methodName);
		}
	}

	~MatrixRowSource()
	{
	}

public:
	MatrixRowSource(const MatrixRowSource&) = default;
	MatrixRowSource(MatrixRowSource&&) = default;

public:
	cv::Size ImageSize() const override final
	{
		return m_mat.size();
	}

	const ElemType* Read(int row) override final
	{
		return m_mat.ptr(row);
	}

	void Remove(int /*row*/) override final
	{
		// do nothing, rows aren't removed from matrix.
	}

private:
	MatrixRowSource& operator= (const MatrixRowSource&) = delete;
	MatrixRowSource& operator= (MatrixRowSource&&) = delete;

private:
	cv::Mat_<ElemType> m_mat;
};
