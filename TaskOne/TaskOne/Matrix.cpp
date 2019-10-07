#include <iostream>
#include <algorithm>

#include "Base.h"
#include "Matrix.h"
#include "Vector.h"

namespace mat_vec
{
	mat_vec::Matrix::Matrix(size_t size, double value) : m_data(new double* [size]), m_rows(size), m_cols(size)
	{
		for (int i = 0; i < size; i++)
		{
			this->m_data[i] = new double[size];
			std::fill_n(this->m_data[i], size, value);
		}
	}

	mat_vec::Matrix mat_vec::Matrix::eye(size_t size)
	{
		mat_vec::Matrix new_matr(size);
		for (int i = 0; i < size; i++)
		{
			new_matr.m_data[i][i] = 1;
		}
		new_matr.m_rows = size;
		new_matr.m_cols = size;

		return new_matr;
	}

	mat_vec::Matrix::Matrix(size_t rows, size_t cols, double value) : m_data(new double* [rows]), m_rows(rows), m_cols(cols)
	{
		for (int i = 0; i < rows; i++)
		{
			this->m_data[i] = new double[cols];
			std::fill_n(this->m_data[i], cols, value);
		}
	}

	mat_vec::Matrix::Matrix(const mat_vec::Matrix& src) : m_data(new double* [src.m_rows]), m_rows(src.m_rows), m_cols(src.m_cols)
	{
		for (int i = 0; i < src.m_rows; i++)
		{
			this->m_data[i] = new double[src.m_cols];
			std::copy(src.m_data[i], src.m_data[i] + src.m_cols, this->m_data[i]);
		}
	}

	mat_vec::Matrix& mat_vec::Matrix::operator=(const mat_vec::Matrix& rhs)
	{
		Matrix new_matr(rhs.m_rows, rhs.m_cols);
		for (int i = 0; i < rhs.m_rows; i++)
		{
			std::copy(rhs.m_data[i], rhs.m_data[i] + rhs.m_cols, new_matr.m_data[i]);
		}

		return new_matr;
	}

	mat_vec::Matrix::~Matrix()
	{
		for (int i = 0; i < this->m_rows; i++)
		{
			delete[] this->m_data[i];
		}
		delete[] this->m_data;
	}

	void mat_vec::Matrix::reshape(size_t rows, size_t cols)
	{
		mat_vec::Vector buf(this->m_rows * this->m_cols);
		int k = 0;
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				buf[k++] = this->m_data[i][j];
			}
		}

		for (int i = 0; i < this->m_rows; i++)
		{
			delete[] this->m_data[i];
		}
		delete[] this->m_data;

		this->m_data = new double* [rows];
		k = 0;
		for (int i = 0; i < rows; i++)
		{
			this->m_data[i] = new double[cols];
			for (int j = 0; j < cols && k < buf.size(); j++)
			{
				this->m_data[i][j] = buf[k++];
			}
		}
		this->m_rows = rows;
		this->m_cols = cols;
	}

	std::pair<size_t, size_t> mat_vec::Matrix::shape() const
	{
		return { this->m_rows, this->m_cols };
	}

	double mat_vec::Matrix::get(size_t row, size_t col) const
	{
		if (this->m_cols <= col || this->m_rows <= row)
			throw std::runtime_error("RE");

		return this->m_data[row][col];
	}

	mat_vec::Matrix mat_vec::Matrix::operator+(const mat_vec::Matrix& rhs) const
	{
		if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols)
			throw std::runtime_error("RE");

		mat_vec::Matrix new_matr(rhs.m_rows, rhs.m_cols);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				new_matr.m_data[i][j] = this->m_data[i][j] + rhs.m_data[i][j];
			}
		}

		return new_matr;
	}

	mat_vec::Matrix& mat_vec::Matrix::operator+=(const mat_vec::Matrix& rhs)
	{
		if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols)
			throw std::runtime_error("RE");

		mat_vec::Matrix new_matr(rhs.m_rows, rhs.m_cols);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				new_matr.m_data[i][j] = this->m_data[i][j] + rhs.m_data[i][j];
			}
		}

		return new_matr;
	}

	mat_vec::Matrix mat_vec::Matrix::operator-(const mat_vec::Matrix& rhs) const
	{
		if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols)
			throw std::runtime_error("RE");

		mat_vec::Matrix new_matr(rhs.m_rows, rhs.m_cols);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				new_matr.m_data[i][j] = this->m_data[i][j] - rhs.m_data[i][j];
			}
		}

		return new_matr;
	}

	mat_vec::Matrix& mat_vec::Matrix::operator-=(const mat_vec::Matrix& rhs)
	{
		if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols)
			throw std::runtime_error("RE");

		mat_vec::Matrix new_matr(rhs.m_rows, rhs.m_cols);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				new_matr.m_data[i][j] = this->m_data[i][j] - rhs.m_data[i][j];
			}
		}

		return new_matr;
	}

	mat_vec::Matrix mat_vec::Matrix::operator*(const Matrix& rhs) const
	{
		if (this->m_cols != rhs.m_rows)
			throw std::runtime_error("RE");

		mat_vec::Matrix new_matr(this->m_rows, rhs.m_cols);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < rhs.m_cols; j++)
			{
				for (int k = 0; k < this->m_cols; k++)
				{
					new_matr.m_data[i][j] += this->m_data[i][k] * rhs.m_data[k][j];
				}
			}
		}

		return new_matr;
	}

	mat_vec::Matrix& mat_vec::Matrix::operator*=(const Matrix& rhs)
	{
		if (this->m_cols != rhs.m_rows)
			throw std::runtime_error("RE");

		mat_vec::Matrix new_matr(this->m_rows, rhs.m_cols);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < rhs.m_cols; j++)
			{
				for (int k = 0; k < this->m_cols; k++)
				{
					new_matr.m_data[i][j] += this->m_data[i][k] * rhs.m_data[k][j];
				}
			}
		}

		return new_matr;
	}

	mat_vec::Matrix mat_vec::Matrix::operator*(double k) const
	{
		Matrix new_matr(this->m_rows, this->m_cols);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				new_matr.m_data[i][j] = this->m_data[i][j] * k;
			}
		}
		return new_matr;
	}

	mat_vec::Matrix& mat_vec::Matrix::operator*=(double k)
	{
		Matrix new_matr(this->m_rows, this->m_cols);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				new_matr.m_data[i][j] = this->m_data[i][j] * k;
			}
		}
		return new_matr;
	}

	mat_vec::Matrix mat_vec::Matrix::operator/(double k) const
	{
		Matrix new_matr(this->m_rows, this->m_cols);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				new_matr.m_data[i][j] = this->m_data[i][j] / k;
			}
		}
		return new_matr;
	}

	mat_vec::Matrix& mat_vec::Matrix::operator/=(double k)
	{
		Matrix new_matr(this->m_rows, this->m_cols);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				new_matr.m_data[i][j] = this->m_data[i][j] / k;
			}
		}
		return new_matr;
	}

	mat_vec::Matrix mat_vec::Matrix::transposed() const
	{
		Matrix new_matr(this->m_cols, this->m_rows);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				new_matr.m_data[j][i] = this->m_data[i][j];
			}
		}
		return new_matr;
	}
	
	void mat_vec::Matrix::transpose()
	{
		Matrix newMatr(this->m_cols, this->m_rows);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				newMatr.m_data[j][i] = this->m_data[i][j];
			}
		}

		for (int i = 0; i < this->m_rows; i++)
		{
			delete[] this->m_data[i];
		}
		delete[] this->m_data;

		this->m_data = newMatr.m_data;
		this->m_rows = newMatr.m_rows;
		this->m_cols = newMatr.m_cols;
	}

	//

	//

	mat_vec::Vector mat_vec::Matrix::operator*(const mat_vec::Vector& vec) const
	{
		if (this->m_cols != vec.size())
			throw std::runtime_error("RE");

		mat_vec::Vector new_vec(this->m_rows);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int k = 0; k < this->m_cols; k++)
			{
				new_vec[k] += this->m_data[i][k] * vec[k];
			}
		}

		return new_vec;
	}

	bool mat_vec::Matrix::operator==(const mat_vec::Matrix& rhs) const
	{
		if (this->m_cols != rhs.m_cols || this->m_rows != rhs.m_rows)
			throw std::runtime_error("RE");

		bool is_equal = 1;
		for (int i = 0; i < this->m_rows && is_equal; i++)
		{
			for (int j = 0; j < this->m_cols && is_equal; j++)
			{
				if (this->m_data[i][j] != rhs.m_data[i][j])
					is_equal = 0;
			}
		}

		return is_equal;
	}

	bool mat_vec::Matrix::operator!=(const mat_vec::Matrix& rhs) const
	{
		if (this->m_cols != rhs.m_cols || this->m_rows != rhs.m_rows)
			throw std::runtime_error("RE");

		bool is_equal = 1;
		for (int i = 0; i < this->m_rows && is_equal; i++)
		{
			for (int j = 0; j < this->m_cols && is_equal; j++)
			{
				if (this->m_data[i][j] != rhs.m_data[i][j])
					is_equal = 0;
			}
		}

		return !is_equal;
	}
}