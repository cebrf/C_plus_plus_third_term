#pragma once

#include "Base.h"
#include <tuple>

namespace mat_vec {

	class Matrix {
	public:
		// ������������ ������� � ��������� size x size, ����������� value
		/*explicit Matrix(int32_t size, double value = 0);*/

		// ���������� ��������� �������
		static Matrix eye(int32_t size);

		// ���������� ������� � ��������� rows x cols, ����������� value
		Matrix(int32_t rows, int32_t cols, double value = 0);

		// ����������� �����������
		Matrix(const Matrix& src);

		// �������� ������������
		Matrix& operator=(const Matrix& rhs);

		// ����������
		~Matrix();

        mat_vec::SpareMatrix convert_to_sparse_matr() const;

		// �������� ������ � ������ �������, �� ������� ��� ����
		// ������� ���������� ��������� �� ������ �������� � ������� �������:
		//
		// [1 2 3] -> [1 2]
		// [4 5 6] -> [3 4]
		//            [5 6]
		void reshape(int32_t rows, int32_t cols);

		// ���������� ���� {rows, cols} -- ���������� ����� � �������� �������
		std::pair<int32_t, int32_t> shape() const;

		// ���������� ������� �� ������� [row, col]
		double get(int32_t row, int32_t col) const;

		void set(int32_t row, int32_t col, double val);

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
		int32_t m_rows;
		int32_t m_cols;

		double deter(double** matr, int n);
		double** cofactor(int i_, int j_, double** matr, int n);
	};

} // namespace mat_vec