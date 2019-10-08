#pragma once

#include "Base.h"
#include <tuple>

namespace mat_vec {

	class Matrix {
	public:
		// ������������ ������� � ��������� size x size, ����������� value
		/*explicit Matrix(size_t size, double value = 0);*/

		// ���������� ��������� �������
		static Matrix eye(size_t size);

		// ���������� ������� � ��������� rows x cols, ����������� value
		Matrix(size_t rows, size_t cols, double value = 0);

		// ����������� �����������
		Matrix(const Matrix& src);

		// �������� ������������
		Matrix& operator=(const Matrix& rhs);

		// ����������
		~Matrix();

		// �������� ������ � ������ �������, �� ������� ��� ����
		// ������� ���������� ��������� �� ������ �������� � ������� �������:
		//
		// [1 2 3] -> [1 2]
		// [4 5 6] -> [3 4]
		//            [5 6]
		void reshape(size_t rows, size_t cols);

		// ���������� ���� {rows, cols} -- ���������� ����� � �������� �������
		std::pair<size_t, size_t> shape() const;

		// ���������� ������� �� ������� [row, col]
		double get(size_t row, size_t col) const;

		void set(size_t row, size_t col, double val);

		// ������������ ��������
		Matrix operator+(const Matrix& rhs) const;
		Matrix& operator+=(const Matrix& rhs);

		// ������������ ���������
		Matrix operator-(const Matrix& rhs) const;
		Matrix& operator-=(const Matrix& rhs);

		// ��������� ���������
		Matrix operator*(const Matrix& rhs) const;
		Matrix& operator*=(const Matrix& rhs);

		// ��������� ���� ��������� ������� �� ���������
		Matrix operator*(double k) const;
		Matrix& operator*=(double k);

		// ������� ���� ��������� ������� �� ���������
		Matrix operator/(double k) const;
		Matrix& operator/=(double k);

		// ���������� ����� �������, ���������� ����������������� ������� (this)
		Matrix transposed() const;

		// ������������� ������� �������
		void transpose();

		// ������������
		double det();

		// �������� �������
		Matrix inv();

		// ��������� ������� �� ������
		Vector operator*(const Vector& vec) const;

		// ������������ ���������
		bool operator==(const Matrix& rhs) const;
		bool operator!=(const Matrix& rhs) const;

	private:
		double** m_data;
		rsize_t m_rows;
		rsize_t m_cols;

		double deter(double** matr, int n);
		double** cofactor(int i_, int j_, double** matr, int n);
	};

} // namespace mat_vec