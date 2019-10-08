#define CATCH_CONFIG_MAIN

#include <iostream>
#include "catch.hpp"

#include "Base.h"
#include "Vector.h"
#include "Matrix.h"

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
	REQUIRE(v1[3] == 5.6);
	//REQUIRE(v1[4] == 5.6);
}

TEST_CASE("operator[] const")
{
	const mat_vec::Vector v1(4, 5.6);
	REQUIRE(v1[3] == 5.6);
	//REQUIRE(v1[4] == 5.6);
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
	REQUIRE(v1[3] == 7.0);
	v1 += v2;      
	REQUIRE(v1[0] == 7.3);
}

TEST_CASE("operator- & -=")
{
	mat_vec::Vector v1(4, 8.6);
	mat_vec::Vector v2(4, 1.3);

	v1 = v1 - v2;
	REQUIRE(v1[3] == 7.3);
	v1 -= v2;
	REQUIRE(v1[0] == 6.0);
}

TEST_CASE("operator^")
{
	mat_vec::Vector v1(4);
	mat_vec::Vector v2(4);
	
	v1[0] = -1.9;
	v1[1] = 2.3;
	v1[2] = -4.5;
	v1[3] = 0;
	v2[0] = 0.1;
	v2[1] = 8;
	v2[2] = 0.76;
	v2[3] = -1;

	mat_vec::Vector v3 = v1 ^ v2;
	v1 ^= v2;

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

	REQUIRE(res == -333.3);
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
	REQUIRE((int)(res[0] * 10) == 1464);
	REQUIRE((int)(res[1] * 10) == 169);
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





/*
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

	REQUIRE(m1.det() == 5.0);
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
	REQUIRE(m.get(1, 1) == 208);
}
*/