#pragma once

#include "Base.h"
#include <tuple>

namespace mat_vec {

	class Matrix {
	public:
		// Конструирует матрицу с размерами size x size, заполненную value
		/*explicit Matrix(int32_t size, double value = 0);*/

		// Возвращает единичную матрицу
		static Matrix eye(int32_t size);

		// Возвращает матрицу с размерами rows x cols, заполненную value
		Matrix(int32_t rows, int32_t cols, double value = 0);

		// Конструктор копирования
		Matrix(const Matrix& src);

		// Оператор присваивания
		Matrix& operator=(const Matrix& rhs);

		// Деструктор
		~Matrix();

        mat_vec::SpareMatrix convert_to_sparse_matr() const;

		// Изменяет ширину и высоту матрицы, не изменяя при этом
		// порядок следования элементов от левого верхнего к правому нижнему:
		//
		// [1 2 3] -> [1 2]
		// [4 5 6] -> [3 4]
		//            [5 6]
		void reshape(int32_t rows, int32_t cols);

		// Возвращает пару {rows, cols} -- количество строк и столбцов матрицы
		std::pair<int32_t, int32_t> shape() const;

		// Возвращает элемент на позиции [row, col]
		double get(int32_t row, int32_t col) const;

		void set(int32_t row, int32_t col, double val);

		// Поэлементное сложение
		Matrix operator+(const Matrix& rhs) const;
		Matrix& operator+=(const Matrix& rhs);

		// Поэлементное вычитание
		Matrix operator-(const Matrix& rhs) const;
		Matrix& operator-=(const Matrix& rhs);

		// Матричное умножение
		Matrix operator*(const Matrix& rhs) const;
		Matrix& operator*=(const Matrix& rhs);

		// Умножение всех элементов матрицы на константу
		Matrix operator*(double k) const;
		Matrix& operator*=(double k);

		// Деление всех элементов матрицы на константу
		Matrix operator/(double k) const;
		Matrix& operator/=(double k);

		// Возвращает новую матрицу, полученную транспонированием текущей (this)
		Matrix transposed() const;

		// Транспонирует текущую матрицу
		void transpose();

		// Определитель
		double det();

		// Обратная матрица
		Matrix inv();

		// УМножение матрицы на вектор
		Vector operator*(const Vector& vec) const;

		// Поэлементное сравнение
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