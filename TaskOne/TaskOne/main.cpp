#define CATCH_CONFIG_MAIN

#include <iostream>
#include "catch.hpp"

#include "Base.h"
#include "Vector.h"
#include "Matrix.h"
#include "SparseMatrix.h"

const double eps = 0.00001;

using namespace mat_vec;

//VECTOR TESTS
TEST_CASE("copy & operator=")
{
	mat_vec::Vector v0(3, 4.7);
	mat_vec::Vector v1(3, 6.1);
	mat_vec::Vector v2 = v0;
	mat_vec::Vector v3(v0);
	REQUIRE(v2[1] == v0[1]);
	REQUIRE(v3[0] == v2[0]);
	v3 = v1; 
	REQUIRE(v3[2] == v1[2]);
}

TEST_CASE("size")
{
	mat_vec::Vector v1(3, 1.9);
	REQUIRE(v1.size() == 3);
}

TEST_CASE("operator[]")
{
	mat_vec::Vector v1(4, 5.6);
	REQUIRE((v1[3] - 5.6) < eps);
}

TEST_CASE("operator[] const")
{
	const mat_vec::Vector v1(4, 5.6);
	REQUIRE(v1[3] == 5.6);
}

TEST_CASE("norm")
{
	mat_vec::Vector v(3, 2.0);
	REQUIRE(v.norm() == sqrt(12));
}

TEST_CASE("normalized")
{
	mat_vec::Vector v(4);
	v[0] = 1;
	v[1] = 3;
	v[2] = 0;
	v[3] = -2;
	mat_vec::Vector v1 = v.normalized();
	v.normalize();
	REQUIRE(v[3] == v1[3]);
	REQUIRE(v[1] == (3 / sqrt(14)));
}

TEST_CASE("operator+ & +=")
{
	mat_vec::Vector v1(4, 6.7);
	mat_vec::Vector v2(4, 0.3);
	
	v1 = v1 + v2;  
	REQUIRE((v1[3] - 7.0) < eps);
	v1 += v2;      
	REQUIRE((v1[0] - 7.3) < eps);
}

TEST_CASE("operator- & -=")
{
	mat_vec::Vector v1(4, 8.6);
	mat_vec::Vector v2(4, 1.3);

	v1 = v1 - v2;
	REQUIRE((v1[3] - 7.3) < eps);
	v1 -= v2;
	REQUIRE((v1[0] - 6.0) < eps);
}

TEST_CASE("operator^")
{
	mat_vec::Vector v1(4);
	mat_vec::Vector v2(4);
	
	v1[0] = 8;
	v1[1] = 2.3;
	v1[2] = -4.5;
	v1[3] = 0;
	v2[0] = 5;
	v2[1] = 8;
	v2[2] = 0.76;
	v2[3] = -1;

	mat_vec::Vector v3 = v1 ^ v2;
	v1 ^= v2;
	REQUIRE((v1[0] - 40) < 0.00001);
	REQUIRE(v1[0] == v3[0]);
	REQUIRE(v1[2] == v3[2]);
}

TEST_CASE("a*b")
{
	mat_vec::Vector v1(4);
	mat_vec::Vector v2(4);

	v1[0] = -19;
	v1[1] = 23;
	v1[2] = -45;
	v1[3] = 3;

	v2[0] = 13;
	v2[1] = 8;
	v2[2] = 6;
	v2[3] = -0.1;

	double res = v1 * v2;

	REQUIRE((res - (-333.3)) < eps);
}

TEST_CASE("vectorv * double k && double k * vector")
{
	mat_vec::Vector v2(4);
	v2[0] = 13;
	v2[1] = 8;
	v2[2] = 6;
	v2[3] = -0.1;
	double k = 38.02;

	mat_vec::Vector v1 = v2 * k;
	mat_vec::Vector v3 = k * v2;
	v2 *= k;
	REQUIRE((v1[0] - 494.26) < eps);
	REQUIRE((v1[2] - 228.12) < eps);
	for (int i = 0; i < 4; i++)
	{
		REQUIRE(v1[i] == v2[i]);
		REQUIRE(v1[i] == v3[i]);
	}
}

TEST_CASE("vectorv / double k")
{
	mat_vec::Vector v2(4);
	v2[0] = 13;
	v2[1] = 8;
	v2[2] = 6;
	v2[3] = -0.1;
	double k = 38.02;

	mat_vec::Vector v1 = v2 / k;
	v2 /= k;
	REQUIRE((v1[0] - 0.34192) < eps);
	REQUIRE((v1[1] - 0.2104155) < eps);
	for (int i = 0; i < 4; i++)
	{
		REQUIRE(v1[i] == v2[i]);
	}
}

TEST_CASE("vector * matrix")
{
	mat_vec::Vector v(4);
	v[0] = 5;
	v[1] = 3;
	v[2] = 16;
	v[3] = -7;
	mat_vec::Matrix m(4, 2, 0);
	m.set(0, 0, 7.5);
	m.set(0, 1, -8.9);
	m.set(1, 0, -1);
	m.set(1, 1, 4);
	m.set(2, 0, 3.8);
	m.set(2, 1, 4.4);
	m.set(3, 0, -7.3);
	m.set(3, 1, 3.0);

	mat_vec::Vector res = v * m;
	v *= m;
	for (int i = 0; i < 2; i++)
	{
		REQUIRE(v[i] == res[i]);
	}
	REQUIRE((res[0] - 146.4) < eps);
	REQUIRE((res[1] - 16.9) < eps);
}

TEST_CASE("operators == & !=")
{
	mat_vec::Vector v1(5, 8.3);
	mat_vec::Vector v2(5, 5.73);
	mat_vec::Vector v3(5, 8.3);
	mat_vec::Vector v4(2, 8.3);
	REQUIRE((v1 == v2) == false);
	REQUIRE((v1 == v3) == true);
	REQUIRE((v3 == v4) == false);
	REQUIRE((v1 != v2) == true);
	REQUIRE((v1 != v3) == false);
	REQUIRE((v3 != v4) == true);
}


//TESTS FOR MATRIX
TEST_CASE("reshape")
{
	mat_vec::Matrix m1(2, 3, 0);
	m1.set(0, 0, 1);
	m1.set(0, 1, 2);
	m1.set(0, 2, 3);
	m1.set(1, 0, 4);
	m1.set(1, 1, 5);
	m1.set(1, 2, 6);

	m1.reshape(3, 2);
	REQUIRE(m1.get(1, 0) == 3);
	REQUIRE(m1.get(1, 1) == 4);
	REQUIRE(m1.get(2, 0) == 5);
	REQUIRE(m1.get(2, 1) == 6);
}

TEST_CASE("shape")
{
	mat_vec::Matrix m1(2, 3, 0);
	REQUIRE(m1.shape().first == 2);
	REQUIRE(m1.shape().second == 3);
}

TEST_CASE("copy & operator =")
{
	mat_vec::Matrix m1(5, 1, 9.2);
	mat_vec::Matrix m2(m1);
	REQUIRE(m1.get(0, 0) == m2.get(0, 0));
	m1.set(0, 0, 0.01);
	m2 = m1;
	REQUIRE(m1.get(0, 0) == m2.get(0, 0));
}

TEST_CASE("eye")
{
	mat_vec::Matrix eye_m = mat_vec::Matrix::eye(2);
	REQUIRE(eye_m.get(0, 0) == 1);
	REQUIRE(eye_m.get(0, 1) == 0);
}

TEST_CASE("operator + && += ")
{
	mat_vec::Matrix m1(3, 2);
	mat_vec::Matrix m2(3, 2);
	
	m1.set(0, 0, 1);
	m1.set(0, 1, 3);
	m1.set(1, 0, -14);
	m1.set(1, 1, 6);
	m1.set(2, 0, -7);
	m1.set(2, 1, -101);

	m2.set(0, 0, -4);
	m2.set(0, 1, 90);
	m2.set(1, 0, 1);
	m2.set(1, 1, 21);
	m2.set(2, 0, -43);
	m2.set(2, 1, 100);

	mat_vec::Matrix m3 = m1 + m2;
	m1 += m2;
	REQUIRE((m1.get(0, 0) -3) < eps);
	REQUIRE((m1.get(1, 1) - 27) < eps);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			REQUIRE(m1.get(i, j) == m3.get(i, j));
}

TEST_CASE("operator - && -= ")
{
	mat_vec::Matrix m1(3, 2);
	mat_vec::Matrix m2(3, 2);

	m1.set(0, 0, 1);
	m1.set(0, 1, 3);
	m1.set(1, 0, -14);
	m1.set(1, 1, 6);
	m1.set(2, 0, -7);
	m1.set(2, 1, -101);

	m2.set(0, 0, -4);
	m2.set(0, 1, 90);
	m2.set(1, 0, 1);
	m2.set(1, 1, 21);
	m2.set(2, 0, -43);
	m2.set(2, 1, 100);

	mat_vec::Matrix m3 = m1 - m2;
	m1 -= m2;
	REQUIRE((m1.get(0, 1) + 87) < eps);
	REQUIRE((m1.get(2, 0) - 36) < eps);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			REQUIRE(m1.get(i, j) == m3.get(i, j));
}

TEST_CASE("m * m")
{
	mat_vec::Matrix m0(1, 4);
	m0.set(0, 0, 5);
	m0.set(0, 1, 3);
	m0.set(0, 2, 16);
	m0.set(0, 3, -7);
	mat_vec::Matrix m(4, 2);
	m.set(0, 0, 7.5);
	m.set(0, 1, -8.9);
	m.set(1, 0, -1);
	m.set(1, 1, 4);
	m.set(2, 0, 3.8);
	m.set(2, 1, 4.4);
	m.set(3, 0, -7.3);
	m.set(3, 1, 3.0);

	mat_vec::Matrix res = m0 * m;
	REQUIRE(res.shape().first == 1);
	REQUIRE(res.shape().second == 2);
	m0 *= m;
	REQUIRE((res.get(0, 0) - 146.4) < eps);
	REQUIRE((res.get(0, 1) - 16.9) < eps);
	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 2; j++)
			REQUIRE(m0.get(i, j) == res.get(i, j));
}

TEST_CASE("m * v")
{
	mat_vec::Matrix m(3, 3);
	m.set(0, 0, 2);
	m.set(0, 1, 4);
	m.set(0, 2, 0);

	m.set(1, 0, -2);
	m.set(1, 1, 1);
	m.set(1, 2, 3);

	m.set(2, 0, -1);
	m.set(2, 1, 0);
	m.set(2, 2, 1);

	mat_vec::Vector v(3);
	v[0] = 1;
	v[1] = 2;
	v[2] = -1;

	mat_vec::Vector res = m * v;
	REQUIRE((res[0] - 10) < eps);
	REQUIRE((res[1] + 3) < eps);
	REQUIRE((res[2] + 2) < eps);

}

TEST_CASE("matrix * double k")
{
	mat_vec::Matrix m1(4, 5, 8);
	double k = 5.2;
	mat_vec::Matrix m2 = m1 * k;
	REQUIRE(m2.get(3, 4) == m1.get(3, 4) * k);
	m1 *= k;
	REQUIRE((m1.get(0, 2) - 41.6) < eps);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 5; j++)
			REQUIRE(m1.get(i, j) == m2.get(i, j));
}

TEST_CASE("matrix / double k")
{
	mat_vec::Matrix m1(4, 5, 8);
	double k = 5.2;
	mat_vec::Matrix m2 = m1 / k;
	REQUIRE(m2.get(3, 4) == m1.get(3, 4) / k);
	m1 /= k;
	REQUIRE((m1.get(0, 0) - 1.5384615) < eps);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 5; j++)
			REQUIRE(m1.get(i, j) == m2.get(i, j));
}

TEST_CASE("TRANS")
{
	mat_vec::Matrix m1(2, 3, 0);
	m1.set(0, 0, 1);
	m1.set(0, 1, 2);
	m1.set(0, 2, 3);
	m1.set(1, 0, 4);
	m1.set(1, 1, 5);
	m1.set(1, 2, 6);

	mat_vec::Matrix m2 = m1.transposed(); 
	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 2; j++)
			REQUIRE(m1.get(i, j) == m2.get(j, i));
	m1.transpose();
	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 2; j++)
			REQUIRE(m1.get(i, j) == m2.get(i, j));
}

TEST_CASE("deter")
{
	Matrix m1(3, 3, 0);
	m1.set(0, 0, 3);
	m1.set(0, 1, 3);
	m1.set(0, 2, -1);

	m1.set(1, 0, 4);
	m1.set(1, 1, 1);
	m1.set(1, 2, 3);

	m1.set(2, 0, 1);
	m1.set(2, 1, -2);
	m1.set(2, 2, -2);

	REQUIRE((m1.det() - 54.0) < eps);
}

TEST_CASE("inver")
{
	Matrix m2(4, 4, 0);
	m2.set(0, 0, 5);
	m2.set(0, 1, -2);
	m2.set(0, 2, 2);
	m2.set(0, 3, 7);

	m2.set(1, 0, 1);
	m2.set(1, 1, 0);
	m2.set(1, 2, 0);
	m2.set(1, 3, 3);

	m2.set(2, 0, -3);
	m2.set(2, 1, 1);
	m2.set(2, 2, 5);
	m2.set(2, 3, 0);

	m2.set(3, 0, 3);
	m2.set(3, 1, 1);
	m2.set(3, 2, -9);
	m2.set(3, 3, 4);

	Matrix m = m2.inv();
	REQUIRE((m.get(1, 1) - 74285) < eps);
}

TEST_CASE("operator == & != ")
{
	mat_vec::Matrix m1(3, 3, 0);
	m1.set(0, 0, 3);
	m1.set(0, 1, 3);
	m1.set(0, 2, -1);

	m1.set(1, 0, 4);
	m1.set(1, 1, 1);
	m1.set(1, 2, 3);

	m1.set(2, 0, 1);
	m1.set(2, 1, -2);
	m1.set(2, 2, -2);

	mat_vec::Matrix m2 = m1;
	REQUIRE(m1 == m2);
	REQUIRE(!(m1 != m2));
	mat_vec::Matrix m3(1, 1);
	REQUIRE(!(m1 == m3));
	REQUIRE(m1 != m3);
	m2.set(0, 0, 0);
	REQUIRE(!(m1 == m2));
	REQUIRE(m1 != m2);

}


//EXCEPTIONS FOR VECTOR

TEST_CASE("size of vec < 0")
{
  mat_vec::Vector v(2, 4);
  REQUIRE_THROWS(v = Vector(-3, 1.0));
}

TEST_CASE("Array index out of bounds")
{
  mat_vec::Vector v1(2, 3.0);
  REQUIRE_THROWS(v1[0] = v1[6]);
  REQUIRE_THROWS(v1[3] = 1.3);
  const mat_vec::Vector v2(2, 4.6);
  REQUIRE_THROWS(v2[3] == 1.3);
}

TEST_CASE("operator v1 +,-,^,* v2  Different sizes of arrays")
{
  mat_vec::Vector v1(2, 5.7), v2(8, 6.2);
  REQUIRE_THROWS(v1 + v2);
  REQUIRE_THROWS(v1 += v2);

  REQUIRE_THROWS(v1 - v2);
  REQUIRE_THROWS(v1 -= v2);

  REQUIRE_THROWS(v1 ^ v2);
  REQUIRE_THROWS(v1 ^= v2);

  REQUIRE_THROWS(v1 * v2);
}

TEST_CASE("Division by zero")
{
  mat_vec::Vector v(3, 4.7);
  REQUIRE_THROWS(v / 0);
  REQUIRE_THROWS(v /= 0);
}

TEST_CASE("vec * matr Different sizes of arrays")
{
  mat_vec::Matrix m(2, 4, 9.3);
  mat_vec::Vector v(6, 0.2);
  REQUIRE_THROWS(v * m);
  REQUIRE_THROWS(v *= m);
}

//EXCEPTIONS FOR MATRIX

TEST_CASE("size of eye matr < 0")
{
  REQUIRE_THROWS(mat_vec::Matrix::eye(-10));
}

TEST_CASE("size of matr < 0")
{
  mat_vec::Matrix m(1, 2);
  REQUIRE_THROWS(m = mat_vec::Matrix(-10, 2));
  REQUIRE_THROWS(m = mat_vec::Matrix(10, -2));
}

TEST_CASE("reshape size < 0")
{

  mat_vec::Matrix m(1, 2);
  REQUIRE_THROWS(m.reshape(-1, 9));
}

TEST_CASE("index out of bounds")
{
  mat_vec::Matrix m(2, 3, 4.0);
  REQUIRE_THROWS(m.get(0, 10) == 1);
  REQUIRE_THROWS(m.get(10, 0) == 1);

  REQUIRE_THROWS(m.set(0, 10, 4));
  REQUIRE_THROWS(m.set(10, 0, 7));
}

TEST_CASE("operator v1 +,-,^,* v2  Different sizes of matr")
{
  mat_vec::Matrix m1(2, 3, 5.7), m2(8, 5, 6.2);
  REQUIRE_THROWS(m1 + m2);
  REQUIRE_THROWS(m1 += m2);

  REQUIRE_THROWS(m1 - m2);
  REQUIRE_THROWS(m1 -= m2);

  REQUIRE_THROWS(m1 * m2);
  REQUIRE_THROWS(m1 *= m2);
}

TEST_CASE("Division by zero in matr")
{
  mat_vec::Matrix m(3, 5, 4.7);
  REQUIRE_THROWS(m / 0);
  REQUIRE_THROWS(m /= 0);
}

TEST_CASE("This matr is not square. Only square matrix has det")
{
  mat_vec::Matrix m(2, 3);
  REQUIRE_THROWS(m.det());
}

TEST_CASE("This matr is not square. Only square matrix can be inv")
{
  mat_vec::Matrix m(2, 3);
  REQUIRE_THROWS(m.inv());
}

TEST_CASE("This matr has det == 0. Only matrix that has det != 0 can be inv")
{
  mat_vec::Matrix m(2, 2, 0);
  REQUIRE_THROWS(m.inv());
}

TEST_CASE("matr * vec. Different sizes")
{
  mat_vec::Matrix m(2, 4, 8.6);
  mat_vec::Vector v(1, 0.1);
  REQUIRE_THROWS(m * v);
}




//_______________________________________
//Sparse matrix tests
TEST_CASE("get and set")
{
    mat_vec::SpareMatrix sp(1, 2);
    sp.set(0, 1, 6.0);
    REQUIRE(std::abs(sp.get(0, 1) - 6.0) < eps);
    sp.set(0, 0, 7.2);
    REQUIRE(std::abs(sp.get(0, 0) - 7.2) < eps);
    REQUIRE((sp.get(0, 1) - 6.0) < eps);
    sp.set(0, 0, 9.9);
    REQUIRE((sp.get(0, 0) - 9.9) < eps);
}

TEST_CASE("copy constractor")
{
    mat_vec::SpareMatrix sp(1, 2);

    sp.set(0, 1, 6.0);
    sp.set(0, 0, 7.2);
    
    mat_vec::SpareMatrix sp2 = sp;
    REQUIRE(std::abs(sp.get(0, 0) - sp2.get(0, 0)) < eps);
    REQUIRE(std::abs(sp.get(0, 1) - sp2.get(0, 1)) < eps);
}

TEST_CASE("shape ")
{
    mat_vec::SpareMatrix sp(1, 2);
    REQUIRE(sp.shape().first == 1);
    REQUIRE(sp.shape().second == 2);
}

TEST_CASE(" * double k")
{
    mat_vec::SpareMatrix sp1(4, 5);
    double k = 2;

    sp1.set(2, 4, 6);
    sp1.set(0, 0, 3);
    mat_vec::SpareMatrix sp2 = sp1 * k;
    sp1 *= k;

    REQUIRE(std::abs(sp1.get(2, 4) - 12) < eps);
    REQUIRE(std::abs(sp2.get(0, 0) - 6) < eps);
}

TEST_CASE(" / double k")
{
    mat_vec::SpareMatrix sp1(4, 5);
    double k = 3;

    sp1.set(2, 4, 18);
    sp1.set(0, 0, 27.3);
    mat_vec::SpareMatrix sp2(1, 1);
    sp2 = sp1 / k;
    sp1 /= k;

    REQUIRE(std::abs(sp1.get(2, 4) - 6) < eps);
    REQUIRE(std::abs(sp2.get(0, 0) - 9.1) < eps);
    REQUIRE_THROWS(sp2 = sp1 / 0);
    REQUIRE_THROWS(sp2 /= 0);
}