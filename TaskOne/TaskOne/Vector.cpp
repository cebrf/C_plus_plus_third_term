#include <algorithm>
#include <iostream>

#include "Base.h"
#include "Vector.h"
#include "Matrix.h"



namespace mat_vec {

	mat_vec::Vector mat_vec::operator*(double k, const mat_vec::Vector& v)
	{
		mat_vec::Vector new_vec(v.size());
		for (int i = 0; i < v.size(); i++)
		{
			new_vec[i] = k * v[i];
		}
		return new_vec;
	}

	mat_vec::Vector::Vector(size_t size, double value) : m_data(new double[size]), m_size(size)
	{
		std::fill_n(this->m_data, size, value);
	}

	mat_vec::Vector::Vector(const mat_vec::Vector& src) : m_data(new double[src.m_size]), m_size(src.m_size)
	{
		std::copy(src.m_data, src.m_data + src.m_size, this->m_data);
	}

	mat_vec::Vector& mat_vec::Vector::operator=(const mat_vec::Vector& rhs)
	{
		delete[] this->m_data;
		this->m_size = rhs.m_size;
		this->m_data = new double[this->m_size];
		std::copy(rhs.m_data, rhs.m_data + rhs.m_size, this->m_data);
		return *this;
	}

	mat_vec::Vector::~Vector()
	{
		delete[] this->m_data;
	}

	size_t mat_vec::Vector::size() const
	{
		return this->m_size;
	}

	double mat_vec::Vector::operator[](size_t n) const
	{
		if (n >= this->m_size)
			throw std::runtime_error("RE");
		return this->m_data[n];
	}

	double& mat_vec::Vector::operator[](size_t n)
	{
		if (n >= this->m_size)
			throw std::runtime_error("RE");
		return this->m_data[n];
	}

	double mat_vec::Vector::norm() const
	{
		double norm_res = 0;
		for (size_t i = 0; i < this->m_size; i++)
			norm_res += pow(this->m_data[i], 2);
		return sqrt(norm_res);
	}

	mat_vec::Vector mat_vec::Vector::normalized() const
	{
		double v_len = 0;
		for (size_t i = 0; i < this->m_size; i++)
			v_len += pow(this->m_data[i], 2);
		v_len = sqrt(v_len);

		mat_vec::Vector new_vec(this->m_size);
		for (int i = 0; i < this->m_size; i++)
			new_vec.m_data[i] = this->m_data[i] / v_len;

		return new_vec;
	}

	void mat_vec::Vector::normalize()
	{
		double v_len = 0;
		for (size_t i = 0; i < this->m_size; i++)
			v_len += pow(this->m_data[i], 2);
		v_len = sqrt(v_len);

		for (int i = 0; i < this->m_size; i++)
			this->m_data[i] = this->m_data[i] / v_len;
	}

	mat_vec::Vector mat_vec::Vector::operator+(const mat_vec::Vector& rhs) const
	{
		if (this->m_size != rhs.m_size)
			throw std::runtime_error("RE");

		mat_vec::Vector new_vec(this->m_size);
		for (int i = 0; i < this->m_size; i++)
		{
			new_vec[i] = this->m_data[i] + rhs.m_data[i];
		}

		return new_vec;
	}

	mat_vec::Vector& mat_vec::Vector::operator+=(const mat_vec::Vector& rhs)
	{
		if (this->m_size != rhs.m_size)
			throw std::runtime_error("RE");

		mat_vec::Vector new_vec(this->m_size);
		for (int i = 0; i < this->m_size; i++)
		{
			new_vec[i] = this->m_data[i] + rhs.m_data[i];
		}

		return new_vec;
	}

	mat_vec::Vector mat_vec::Vector::operator-(const mat_vec::Vector& rhs) const
	{
		if (this->m_size != rhs.m_size)
			throw std::runtime_error("RE");

		mat_vec::Vector new_vec(this->m_size);
		for (int i = 0; i < this->m_size; i++)
		{
			new_vec[i] = this->m_data[i] - rhs.m_data[i];
		}

		return new_vec;
	}

	mat_vec::Vector& mat_vec::Vector::operator-=(const mat_vec::Vector& rhs)
	{
		if (this->m_size != rhs.m_size)
			throw std::runtime_error("RE");

		mat_vec::Vector new_vec(this->m_size);
		for (int i = 0; i < this->m_size; i++)
		{
			new_vec[i] = this->m_data[i] - rhs.m_data[i];
		}

		return new_vec;
	}

	mat_vec::Vector mat_vec::Vector::operator^(const mat_vec::Vector& rhs) const
	{
		if (this->m_size != rhs.m_size)
			throw std::runtime_error("RE");

		mat_vec::Vector new_vec(this->m_size);
		for (int i = 0; i < this->m_size; i++)
		{
			new_vec[i] = this->m_data[i] * rhs.m_data[i];
		}

		return new_vec;
	}

	mat_vec::Vector& mat_vec::Vector::operator^=(const mat_vec::Vector& rhs)
	{
		if (this->m_size != rhs.m_size)
			throw std::runtime_error("RE");

		mat_vec::Vector new_vec(this->m_size);
		for (int i = 0; i < this->m_size; i++)
		{
			new_vec[i] = this->m_data[i] * rhs.m_data[i];
		}

		return new_vec;
	}

	double mat_vec::Vector::operator*(const mat_vec::Vector& rhs) const
	{
		if (this->m_size != rhs.m_size)
			throw std::runtime_error("RE");

		double mult_res = 0;
		for (int i = 0; i < this->m_size; i++)
		{
			mult_res += this->m_data[i] * rhs.m_data[i];
		}

		return mult_res;
	}

	mat_vec::Vector mat_vec::Vector::operator*(double k) const
	{
		mat_vec::Vector new_vec(this->m_size);
		for (int i = 0; i < this->m_size; i++)
		{
			new_vec.m_data[i] = this->m_data[i] * k;
		}

		return new_vec;
	}

	mat_vec::Vector& mat_vec::Vector::operator*=(double k)
	{
		mat_vec::Vector new_vec(this->m_size);
		for (int i = 0; i < this->m_size; i++)
		{
			new_vec.m_data[i] = this->m_data[i] * k;
		}

		return new_vec;
	}

	mat_vec::Vector mat_vec::Vector::operator/(double k) const
	{
		mat_vec::Vector new_vec(this->m_size);
		for (int i = 0; i < this->m_size; i++)
		{
			new_vec.m_data[i] = this->m_data[i] / k;
		}

		return new_vec;
	}

	mat_vec::Vector& mat_vec::Vector::operator/=(double k)
	{
		mat_vec::Vector new_vec(this->m_size);
		for (int i = 0; i < this->m_size; i++)
		{
			new_vec.m_data[i] = this->m_data[i] / k;
		}

		return new_vec;
	}

	mat_vec::Vector mat_vec::Vector::operator*(const mat_vec::Matrix& mat) const
	{
		if (this->m_size != mat.shape().first)
		{
			throw std::runtime_error("RE");
		}

		mat_vec::Vector new_vec(mat.shape().second);
		for (int j = 0; j < mat.shape().second; j++)
		{
			for (int k = 0; k < this->m_size; k++)
			{
				new_vec.m_data[j] += this->m_data[k] * mat.get(j, k);
			}
		}

		return new_vec;
	}

	mat_vec::Vector& mat_vec::Vector::operator*=(const mat_vec::Matrix& mat)
	{
		if (this->m_size != mat.shape().first)
		{
			throw std::runtime_error("RE");
		}

		mat_vec::Vector new_vec(mat.shape().second);
		for (int j = 0; j < mat.shape().second; j++)
		{
			for (int k = 0; k < this->m_size; k++)
			{
				new_vec.m_data[j] += this->m_data[k] * mat.get(j, k);
			}
		}

		return new_vec;
	}

	bool mat_vec::Vector::operator==(const mat_vec::Vector& rhs) const
	{
		if (this->m_size != rhs.m_size)
			throw std::runtime_error("RE");

		bool is_equal = 1;
		for (int i = 0; i < this->m_size; i++)
		{
			if (this->m_data[i] != rhs.m_data[i])
			{
				is_equal = 0;
				break;
			}
		}

		return is_equal;
	}

	bool mat_vec::Vector::operator!=(const mat_vec::Vector& rhs) const
	{
		if (this->m_size != rhs.m_size)
			throw std::runtime_error("RE");

		bool is_equal = 1;
		for (int i = 0; i < this->m_size; i++)
		{
			if (this->m_data[i] != rhs.m_data[i])
			{
				is_equal = 0;
				break;
			}
		}

		return !is_equal;
	}
}
