#include <iostream>
#include <algorithm>

#include "Base.h"
#include "Matrix.h"
#include "Vector.h"


namespace mat_vec
{
	mat_vec::Matrix mat_vec::Matrix::eye(int32_t size)
	{
    if (size <= 0)
      throw std::runtime_error("size <= 0");
		mat_vec::Matrix new_matr(size, size);
		for (int i = 0; i < size; i++)
		{
			new_matr.m_data[i][i] = 1;
		}
		new_matr.m_rows = size;
		new_matr.m_cols = size;

		return new_matr;
	}

	mat_vec::Matrix::Matrix(int32_t rows, int32_t cols, double value) : m_data(new double* [std::max(0, rows)]), m_rows(rows), m_cols(cols)
	{
    if (rows <= 0 || cols <= 0)
      throw std::runtime_error("size < 0");
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
		for (int i = 0; i < this->m_rows; i++)
		{
			delete[] this->m_data[i];
		}
		delete[] this->m_data;

		this->m_rows = rhs.m_rows;
		this->m_cols = rhs.m_cols;
		this->m_data = new double*[rhs.m_rows];
		for (int i = 0; i < rhs.m_rows; i++)
		{
			this->m_data[i] = new double[rhs.m_cols];
			std::copy(rhs.m_data[i], rhs.m_data[i] + rhs.m_cols, this->m_data[i]);
		}

		return *this;
	}

	mat_vec::Matrix::~Matrix()
	{
		for (int i = 0; i < this->m_rows; i++)
		{
			delete[] this->m_data[i];
		}
		delete[] this->m_data;
	}

	void mat_vec::Matrix::reshape(int32_t rows, int32_t cols)
	{
    if (rows < 0 || cols < 0)
      throw std::runtime_error("size < 0");

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

	std::pair<int32_t, int32_t> mat_vec::Matrix::shape() const
	{
		return { this->m_rows, this->m_cols };
	}

	double mat_vec::Matrix::get(int32_t row, int32_t col) const
	{
		if (this->m_cols <= col || this->m_rows <= row || row < 0 || col < 0)
			throw std::runtime_error("Index out of bounds");

		return this->m_data[row][col];
	}

	void mat_vec::Matrix::set(int32_t row, int32_t col, double val)
	{
		if (row >= this->m_rows || col >= this->m_cols || row < 0 || col < 0)
			throw std::runtime_error("Index out of bounds");
		this->m_data[row][col] = val;
	}

	mat_vec::Matrix mat_vec::Matrix::operator+(const mat_vec::Matrix& rhs) const
	{
		if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols)
			throw std::runtime_error("Array index out of bounds");

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
			throw std::runtime_error("Array index out of bounds");

		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				this->m_data[i][j] += rhs.m_data[i][j];
			}
		}

		return *this;
	}

	mat_vec::Matrix mat_vec::Matrix::operator-(const mat_vec::Matrix& rhs) const
	{
		if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols)
			throw std::runtime_error("Array index out of bounds");

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
			throw std::runtime_error("Array index out of bounds");

		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				this->m_data[i][j] -= rhs.m_data[i][j];
			}
		}

		return *this;
	}

	mat_vec::Matrix mat_vec::Matrix::operator*(const Matrix& rhs) const
	{
		if (this->m_cols != rhs.m_rows)
			throw std::runtime_error("Array index out of bounds");

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
			throw std::runtime_error("Array index out of bounds");

		double** new_data = new double* [this->m_rows];
		for (int i = 0; i < this->m_rows; i++)
		{
			new_data[i] = new double[rhs.m_cols];
			for (int j = 0; j < rhs.m_cols; j++)
			{
				new_data[i][j] = 0;
				for (int k = 0; k < this->m_cols; k++)
				{
					new_data[i][j] += this->m_data[i][k] * rhs.m_data[k][j];
				}
			}
		}

		for (int i = 0; i < this->m_rows; i++)
		{
			delete[] this->m_data[i];
		}
		delete[] this->m_data;
		this->m_cols = rhs.m_cols;
		this->m_data = new double*[this->m_rows];
		for (int i = 0; i < this->m_rows; i++)
		{
			this->m_data[i] = new double[this->m_cols];
			for (int j = 0; j < this->m_cols; j++)
			{
				std::copy(new_data[i], new_data[i] + this->m_cols, this->m_data[i]);
			}
		}
		return *this;
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
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				this->m_data[i][j] *= k;
			}
		}
		return *this;
	}

	mat_vec::Matrix mat_vec::Matrix::operator/(double k) const
	{
    if (k == 0)
      throw std::runtime_error("Division by zero");

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
    if (k == 0)
      throw std::runtime_error("Division by zero");

		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_cols; j++)
			{
				this->m_data[i][j] /= k;
			}
		}
		return *this;
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

		this->m_rows = newMatr.m_rows;
		this->m_cols = newMatr.m_cols;

		this->m_data = new double* [this->m_rows];
		for (int i = 0; i < this->m_rows; i++)
		{
			this->m_data[i] = new double[this->m_cols];
			for (int j = 0; j < this->m_cols; j++)
			{
				std::copy(newMatr.m_data[i], newMatr.m_data[i] + this->m_cols, this->m_data[i]);
			}
		}
	}

	double mat_vec::Matrix::det()
	{
		if (this->m_rows != this->m_cols)
			throw std::runtime_error("This matr is not square. Only square matrix has det");

		return deter(this->m_data, this->m_rows);
	}

	mat_vec::Matrix mat_vec::Matrix::inv()
	{
		if (this->m_rows != this->m_cols)
			throw std::runtime_error("This matr is not square. Only square matrix can be inv");
		
		double de = deter(this->m_data, this->m_rows);
		if (de == 0)
			throw std::runtime_error("Inverse doesn't exist");

		mat_vec::Matrix inver(this->m_rows, this->m_rows);

		for (int i = 0; i < this->m_rows; i++)
		{
			for (int j = 0; j < this->m_rows; j++)
			{
				int sign;
				(i + j) % 2 == 1 ? sign = -1 : sign = 1;
				inver.m_data[j][i] = sign * deter(cofactor( i, j, this->m_data, this->m_rows), this->m_rows - 1) / de;
			}
		}
		return inver;
	}

	mat_vec::Vector mat_vec::Matrix::operator*(const mat_vec::Vector& vec) const
	{
		if (this->m_cols != vec.size())
			throw std::runtime_error("Different sizes");

		mat_vec::Vector new_vec(this->m_rows);
		for (int i = 0; i < this->m_rows; i++)
		{
			for (int k = 0; k < this->m_cols; k++)
			{
				new_vec[i] += this->m_data[i][k] * vec[k];
			}
		}

		return new_vec;
	}

	bool mat_vec::Matrix::operator==(const mat_vec::Matrix& rhs) const
	{
		if (this->m_cols != rhs.m_cols || this->m_rows != rhs.m_rows)
			return false;

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
			return true;

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

	double** mat_vec::Matrix::cofactor(int i_, int j_, double** matr, int n)
	{
		double** buf = new double* [n];
		int row = 0, col = 0;
		for (int i = 0; i < n; i++)
		{
			buf[i] = new double[n];
			if (i == i_)
				continue;
			for (int j = 0; j < n; j++)
			{
				if (j == j_)
					continue;
				buf[row][col++] = matr[i][j];
				if (col == n - 1)
				{
					row++;
					col = 0;
				}
			}
		}
		return buf;
	}
	
	double mat_vec::Matrix::deter(double** matr, int n)
	{
		int de = 0;
		if (n == 1)
			return matr[0][0];
		if (n == 2)
			return matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];

		for (int el = 0; el < n; el++)
		{
			double** matr_ = cofactor(0, el, matr, n);
			de += matr[0][el] * pow(-1, el) * deter(matr_, n - 1);
			for (int i = 0; i < n - 1; i++)
				delete[] matr_[i];
			delete[] matr_;
		}
		return de;
	}
}