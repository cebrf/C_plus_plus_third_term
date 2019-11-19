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
    }
}

TEST_CASE("copy constructors")
{
    fefu::hash_map<int, int> hm(8);
    if (1)
    {
        fefu::hash_map<int, int> hm1(hm);
    }
    /*if (1)  //first make insert [fir, las)
    {
        vector<int> v = { 1, 3, 5, 76756 };
        fefu::hash_map<int, int> hm1(v.begin(), v.end(), 15);
    }*/

    if (1)
    {
        fefu::hash_map<int, int> hm1(hm.get_allocator());
    }

    if (1)
    {
        fefu::hash_map<int, int> hm1(21);
        fefu::hash_map<int, int> hm2(hm, hm1.get_allocator());
    }
    
    /*if (1)
    {
        std::initializer_list<pair<const int, int>> e = { {1, 3}, {92,364}, {-34, 4} };
        fefu::hash_map<int, int> hm1(e, 61);
    }*/

    /*if (1)
    {
        std::initializer_list<pair<const int, int>> e = { {1, 3}, {92,364}, {-34, 4} };
        fefu::hash_map<int, int> hm1 = e;
    }*/
}

TEST_CASE("move constructors")
{
    fefu::hash_map<int, int> hm(8);
    if (1)
    {
        fefu::hash_map<int, int> hm1(std::move(hm));
    }
    if (1)
    {
        fefu::hash_map<int, int> hm1(19);
        fefu::hash_map<int, int> hm2(std::move(hm), hm1.get_allocator());
    }
}


TEST_CASE("opertator =")
{
    fefu::hash_map<int, int> hm(8);
    if (1)
    {
        fefu::hash_map<int, int> hm1;
        hm1 = hm;
    }
    if (1)
    {
        fefu::hash_map<int, int> hm1;
        hm1 = std::move(hm);
    }
}