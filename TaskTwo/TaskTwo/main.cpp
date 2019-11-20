#define CATCH_CONFIG_MAIN

#include <iostream>
#include <vector>
#include <string>
#include "catch.hpp"
#include "hash_map.hpp"
#include <unordered_map>

const float Eps = 0.0001;

using namespace std;

TEST_CASE("allocator")
{
    fefu::allocator<int> alu;
    int* e = alu.allocate();
    *e = 15;
    REQUIRE(*e == 15);
}

TEST_CASE("base constructor")
{
    if (1)
    {
        fefu::hash_map<int, int> hm(8);
        hm[-4] = 7;
        hm[5] = 13;
        REQUIRE(hm[5] == 13);
        REQUIRE(hm[0] == 0);
    }
}

TEST_CASE("copy constructors")
{
    fefu::hash_map<int, int> hm(8);
    hm[-4] = 7;
    hm[5] = 13;
    if (1)
    {
        fefu::hash_map<int, int> hm1(hm);
        REQUIRE(hm1[-4] == 7);
        REQUIRE(hm1[-4] == hm[-4]);
        REQUIRE(hm1[5] == hm[5]);
        REQUIRE(hm1[5] == 13);
        REQUIRE(hm[8] == hm1[8]);
    }
    if (1)
    {
        vector<pair<int, int>> v = { {1, 3}, {92,364}, {-34, 4} };
        fefu::hash_map<int, int> hm1(v.begin(), v.end(), 15);
        REQUIRE(hm1[1] == 3);
        REQUIRE(hm1[92] == 364);
        REQUIRE(hm1[-34] == 4);
    }

    if (1)
    {
        fefu::hash_map<int, int> hm1(hm.get_allocator());
    }

    if (1)
    {
        fefu::hash_map<int, int> hm_(21);
        fefu::hash_map<int, int> hm1(hm, hm_.get_allocator());
        REQUIRE(hm1[-4] == 7);
        REQUIRE(hm1[-4] == hm[-4]);
        REQUIRE(hm1[5] == hm[5]);
        REQUIRE(hm1[5] == 13);
        REQUIRE(hm[8] == hm1[8]);
    }
    
    if (1)
    {
        std::initializer_list<pair<const int, int>> e = { {1, 3}, {92,364}, {-34, 4} };
        fefu::hash_map<int, int> hm1(e, 61);
        REQUIRE(hm1[1] == 3);
        REQUIRE(hm1[92] == 364);
        REQUIRE(hm1[-34] == 4);
    }

    if (1)
    {
        std::initializer_list<pair<const int, int>> e = { {1, 3}, {92,364}, {-34, 4} };
        fefu::hash_map<int, int> hm1 = e;
        REQUIRE(hm1[1] == 3);
        REQUIRE(hm1[92] == 364);
        REQUIRE(hm1[-34] == 4);
    }
}

TEST_CASE("move constructors")
{
    fefu::hash_map<int, int> hm(8);
    hm[74] = -53;
    hm[29] = 68;
    if (1)
    {
        fefu::hash_map<int, int> hm_(hm);
        fefu::hash_map<int, int> hm1(std::move(hm_));
        REQUIRE(hm1[74] == -53);
        REQUIRE(hm1[29] == 68);
    }
    if (1)
    {
        fefu::hash_map<int, int> hm_(hm);
        fefu::hash_map<int, int> hm1(19);
        fefu::hash_map<int, int> hm2(std::move(hm), hm_.get_allocator());
        REQUIRE(hm2[74] == -53);
        REQUIRE(hm2[29] == 68);
    }
}


TEST_CASE("opertator =")
{
    fefu::hash_map<int, int> hm(8);
    hm[14] = 4;
    if (1)
    {
        fefu::hash_map<int, int> hm1;
        hm1 = hm;
        REQUIRE(hm[14] == hm1[14]);
        REQUIRE(hm1[14] == 4);
    }
    if (1)
    {
        fefu::hash_map<int, int> hm_(hm);
        fefu::hash_map<int, int> hm1;
        hm1 = std::move(hm_);
        REQUIRE(hm1[14] == 4);
    }

    if (1)
    {
        std::initializer_list<pair<const int, int>> e = { {1, 3}, {92,364}, {-34, 4} };
        fefu::hash_map<int, int> hm1(hm);
        hm1 = e;
    }
}