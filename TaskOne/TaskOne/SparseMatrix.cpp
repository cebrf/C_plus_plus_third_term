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

    mat_vec::SpareMatrix& mat_vec::SpareMatrix::operator=(const SpareMatrix& rhs)
    {
        for (int i = 0; i < this->m_rows; i++)
        {
            delete[] this->m_data[i];
        }
        delete[] this->m_data;
        delete[] this->size_of_row;

        this->m_rows = rhs.m_rows;
        this->m_cols = rhs.m_cols;
        this->m_data = new val_ind* [rhs.m_rows];
        this->size_of_row = new int[rhs.m_rows];
        std::copy(rhs.size_of_row, rhs.size_of_row + rhs.m_rows, this->size_of_row);
        for (int i = 0; i < rhs.m_rows; i++)
        {
            this->m_data[i] = new val_ind[rhs.size_of_row[i]];
            std::copy(rhs.m_data[i], rhs.m_data[i] + rhs.size_of_row[i], this->m_data[i]);
        }

        return *this;
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
        std::copy(m_data[row], m_data[row] + insert, buf);
        buf[insert].ind = col;
        buf[insert].val = val;
        if (size_of_row[row] > insert)
            std::copy(m_data[row] + insert, m_data[row] + size_of_row[row], buf + insert + 1);

        delete[] m_data[row];
        m_data[row] = new val_ind[size_of_row[row] + 1];
        std::copy(buf, buf + size_of_row[row] + 1, m_data[row]);

        /*for (int i = 0; i < size_of_row[row] + 1; i++)
            std::cout << buf[i].ind << " " << buf[i].val << " ";
        std::cout << '\n';*/

        delete[] buf;
        size_of_row[row]++;
    }

    mat_vec::Matrix mat_vec::SpareMatrix::convert_to_matr()
    {
        mat_vec::Matrix new_matr(this->m_rows, this->m_cols);
        for (int i = 0; i < this->m_rows; i++)
        {
            for (int j = 0; j < this->size_of_row[i]; j++)
            {
                new_matr.set(i, this->m_data[i][j].ind, this->m_data[i][j].val);
            }
        }
        return new_matr;
    }

    std::pair<int32_t, int32_t> mat_vec::SpareMatrix::shape() const
    {
        return { this->m_rows, this->m_cols };
    }

    mat_vec::SpareMatrix mat_vec::SpareMatrix::operator*(double k) const
    {
        SpareMatrix new_sp = *this;
        for (int i = 0; i < this->m_rows; i++)
        {
            for (int j = 0; j < size_of_row[i]; j++)
            {
                new_sp.m_data[i][j].val *= k;
            }
        }
        return new_sp;
    }

    mat_vec::SpareMatrix& mat_vec::SpareMatrix::operator*=(double k)
    {
        for (int i = 0; i < this->m_rows; i++)
        {
            for (int j = 0; j < size_of_row[i]; j++)
            {
                this->m_data[i][j].val *= k;
            }
        }
        return *this;
    }

    mat_vec::SpareMatrix mat_vec::SpareMatrix::operator/(double k) const
    {
        if (k == 0)
            throw std::runtime_error("Division by zero");

        SpareMatrix new_sp = *this;
        for (int i = 0; i < this->m_rows; i++)
        {
            for (int j = 0; j < size_of_row[i]; j++)
            {
                new_sp.m_data[i][j].val /= k;
            }
        }
        return new_sp;
    }

    mat_vec::SpareMatrix& mat_vec::SpareMatrix::operator/=(double k)
    {
        if (k == 0)
            throw std::runtime_error("Division by zero");

        for (int i = 0; i < this->m_rows; i++)
        {
            for (int j = 0; j < size_of_row[i]; j++)
            {
                this->m_data[i][j].val /= k;
            }
        }
        return *this;
    }

    mat_vec::SpareMatrix mat_vec::SpareMatrix::operator+(const mat_vec::SpareMatrix& rhs) const
    {
        if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols)
            throw std::runtime_error("Array index out of bounds");

        mat_vec::SpareMatrix new_matr(this->m_rows, this->m_cols);
        for (int i = 0; i < this->m_rows; i++)
        {
            int l = 0, r = 0;
            while (l < this->size_of_row[i] && r < rhs.size_of_row[i])
            {
                if (this->m_data[i][l].ind == rhs.m_data[i][r].ind)
                {
                    new_matr.set(i, this->m_data[i][l].ind, this->m_data[i][l].val + rhs.m_data[i][r].val);
                    l++;
                    r++;
                }
                else if (this->m_data[i][l].ind < rhs.m_data[i][r].ind)
                {
                    new_matr.set(i, this->m_data[i][l].ind, this->m_data[i][l].val);
                    l++;
                }
                else
                {
                    new_matr.set(i, rhs.m_data[i][r].ind, rhs.m_data[i][r].val);
                    r++;
                }
            }
            while (l < this->size_of_row[i])
            {
                new_matr.set(i, this->m_data[i][l].ind, this->m_data[i][l].val);
                l++;
            }
            while (r < rhs.size_of_row[i])
            {
                new_matr.set(i, rhs.m_data[i][r].ind, rhs.m_data[i][r].val);
                r++;
            }
        }
        return new_matr;
    }

    mat_vec::SpareMatrix& mat_vec::SpareMatrix::operator+=(const SpareMatrix& rhs)
    {
        if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols)
            throw std::runtime_error("Array index out of bounds");
        
        for (int i = 0; i < rhs.m_rows; i++)
        {
            for (int j = 0; j < rhs.size_of_row[i]; j++)
            {
                double x = this->get(i, rhs.m_data[i][j].ind) + rhs.m_data[i][j].val;
                this->set(i, rhs.m_data[i][j].ind, x);
            }
        }

    }

    mat_vec::SpareMatrix mat_vec::SpareMatrix::operator-(const mat_vec::SpareMatrix& rhs) const
    {
        if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols)
            throw std::runtime_error("Array index out of bounds");

        mat_vec::SpareMatrix new_matr(this->m_rows, this->m_cols);
        for (int i = 0; i < this->m_rows; i++)
        {
            int l = 0, r = 0;
            while (l < this->size_of_row[i] && r < rhs.size_of_row[i])
            {
                if (this->m_data[i][l].ind == rhs.m_data[i][r].ind)
                {
                    new_matr.set(i, this->m_data[i][l].ind, this->m_data[i][l].val - rhs.m_data[i][r].val);
                    l++;
                    r++;
                }
                else if (this->m_data[i][l].ind < rhs.m_data[i][r].ind)
                {
                    new_matr.set(i, this->m_data[i][l].ind, this->m_data[i][l].val);
                    l++;
                }
                else
                {
                    new_matr.set(i, rhs.m_data[i][r].ind, rhs.m_data[i][r].val);
                    r++;
                }
            }
            while (l < this->size_of_row[i])
            {
                new_matr.set(i, this->m_data[i][l].ind, this->m_data[i][l].val);
                l++;
            }
            while (r < rhs.size_of_row[i])
            {
                new_matr.set(i, rhs.m_data[i][r].ind, rhs.m_data[i][r].val * (-1));
                r++;
            }
        }
        return new_matr;
    }

    mat_vec::SpareMatrix& mat_vec::SpareMatrix::operator-=(const SpareMatrix& rhs)
    {
        if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols)
            throw std::runtime_error("Array index out of bounds");

        for (int i = 0; i < rhs.m_rows; i++)
        {
            for (int j = 0; j < rhs.size_of_row[i]; j++)
            {
                double x = this->get(i, rhs.m_data[i][j].ind) - rhs.m_data[i][j].val;
                this->set(i, rhs.m_data[i][j].ind, x);
            }
        }

    }

    void mat_vec::SpareMatrix::transpose()
    {
        mat_vec::SpareMatrix new_matr(this->m_cols, this->m_rows);
        for (int i = 0; i < this->m_rows; i++)
        {
            for(int j = 0; j < this->size_of_row[i]; j++)
            {
                new_matr.set(this->m_data[i][j].ind, i, this->m_data[i][j].val);
            }
        }

        *this = new_matr;
    }

    mat_vec::SpareMatrix mat_vec::SpareMatrix::transposed() const
    {
        mat_vec::SpareMatrix new_matr(*this);
        new_matr.transpose();
        return new_matr;
    }
}