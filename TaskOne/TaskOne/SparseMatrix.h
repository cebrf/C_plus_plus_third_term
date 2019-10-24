#pragma once
#include "Base.h"
#include <cstdint>

namespace mat_vec
{
  class SpareMatrix
  {
  public:
    SpareMatrix(int32_t rows, int32_t cols);

    // ����������� �����������
    SpareMatrix(const SpareMatrix& src);

    ~SpareMatrix();

    // �������� ������������
    SpareMatrix& operator=(const SpareMatrix& rhs);
    
    double get(int32_t row, int32_t col) const;
    
    void set(int32_t row, int32_t col, double val);

    void reshape(int32_t rows, int32_t cols);

    mat_vec::Matrix convert_to_matr();

    std::pair<int32_t, int32_t> shape() const;

    // ������������ ��������
    SpareMatrix operator+(const SpareMatrix& rhs) const;
    SpareMatrix& operator+=(const SpareMatrix& rhs);

    // ������������ ���������
    SpareMatrix operator-(const SpareMatrix& rhs) const;
    SpareMatrix& operator-=(const SpareMatrix& rhs);

    // ��������� ���������
    SpareMatrix operator*(const SpareMatrix& rhs) const;
    SpareMatrix& operator*=(const SpareMatrix& rhs);

    // ��������� ���� ��������� ������� �� ���������
    SpareMatrix operator*(double k) const;
    SpareMatrix& operator*=(double k);

    // ������� ���� ��������� ������� �� ���������
    SpareMatrix operator/(double k) const;
    SpareMatrix& operator/=(double k);

    // ���������� ����� �������, ���������� ����������������� ������� (this)
    SpareMatrix transposed() const;

    // ������������� ������� �������
    void transpose();

    // ������������
    double det();

    // �������� �������
    SpareMatrix inv();

    // ������������ ���������
    bool operator==(const SpareMatrix& rhs) const;
    bool operator!=(const SpareMatrix& rhs) const;

  private:
    struct val_ind
    {
      int32_t ind;
      double val;
    };
    val_ind** m_data;
    int32_t* size_of_row;
    int32_t m_rows;
    int32_t m_cols;
  };
}