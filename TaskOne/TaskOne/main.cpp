#define CATCH_CONFIG_MAIN

#include <iostream>
#include "catch.hpp"

#include "Base.h"
#include "Vector.h"
#include "Matrix.h"

using namespace mat_vec;

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