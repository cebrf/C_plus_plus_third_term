#include <iostream>
#include <algorithm>

#include "Base.h"
#include "Matrix.h"
#include "Vector.h"
#include "SparseMatrix.h"

namespace mat_vec
{
    mat_vec::SpareMatrix::SpareMatrix(int32_t rows, int32_t cols) :
        m_data(new val_ind* [std::max(0, rows)]),
        size_of_row(new int[std::max(0, rows)]),
        m_rows(rows),
        m_cols(cols)
    {
        if (rows <= 0 || cols <= 0)
            throw std::runtime_error("size < 0");
        for (int i = 0; i < rows; i++)
        {
            size_of_row[i] = 0;
            this->m_data[i] = new val_ind[cols];
        }
    }

    mat_vec::SpareMatrix::SpareMatrix(const mat_vec::SpareMatrix& src) : 
        m_data(new val_ind* [src.m_rows]),
        size_of_row(new int[src.m_rows]),
        m_rows(src.m_rows), 
        m_cols(src.m_cols)
    {
        std::copy(src.size_of_row, src.size_of_row + src.m_rows, this->size_of_row);
        for (int i = 0; i < src.m_rows; i++)
        {
            this->m_data[i] = new val_ind[src.m_cols];
            std::copy(src.m_data[i], src.m_data[i] + src.m_cols, this->m_data[i]);
        }
    }
    
    mat_vec::SpareMatrix::~SpareMatrix()
    {
        for (int i = 0; i < this->m_rows; i++)
        {
            delete[] this->m_data[i];
        }
        delete[] this->m_data;
        delete[] this->size_of_row;
    }

    double mat_vec::SpareMatrix::get(int32_t row, int32_t col) const
    {
        double out_val = 0.0;
        if (row >= this->m_rows || col >= this->m_cols || row < 0 || col < 0)
            throw std::runtime_error("Index out of bounds");

        if (size_of_row[row] > 0)
        {
            int r = size_of_row[row] - 1, l = 0;
            while (l <= r) {
                int m = l + (r - l) / 2;
                if (m_data[row][m].ind == col)
                {
                    out_val = m_data[row][m].val;
                    return out_val;
                }
                if (m_data[row][m].ind < col)
                    l = m + 1;
                else
                    r = m - 1;
            }
        }

        return out_val;
    }
    
    void mat_vec::SpareMatrix::set(int32_t row, int32_t col, double val)
    {
        if (row >= this->m_rows || col >= this->m_cols || row < 0 || col < 0)
            throw std::runtime_error("Index out of bounds");

        int insert = 0;
        for (; insert < size_of_row[row]; insert++)
        {
            if (m_data[row][insert].ind == col)
            {
                m_data[row][insert].val = val;
                return;
            }
            if (m_data[row][insert].ind > col)
            {
                break;
            }
        }

        val_ind* buf = new val_ind[size_of_row[row] + 1];
        std::copy(m_data[row], m_data[row] + size_of_row[std::max(0, insert - 1)], buf);
        buf[insert].ind = col;
        buf[insert].val = val;
        if (size_of_row[row] > insert)
            std::copy(m_data[row] + insert, m_data[row] + size_of_row[row] + 1, buf + insert + 1);

        delete[] m_data[row];
        m_data[row] = new val_ind[size_of_row[row] + 1];
        std::copy(buf, buf + size_of_row[row] + 1, m_data[row]);
        
        delete[] buf;
        size_of_row[row]++;
    }
}