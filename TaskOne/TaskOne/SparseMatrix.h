#pragma once
#include "Base.h"
#include <cstdint>

namespace mat_vec
{
  class SpareMatrix
  {
  public:
    SpareMatrix(int32_t rows, int32_t cols);
    ~SpareMatrix();
    double get(int32_t row, int32_t col) const;
    void set(int32_t row, int32_t col, double val);

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