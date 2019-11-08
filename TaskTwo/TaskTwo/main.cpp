#define CATCH_CONFIG_MAIN

#include <iostream>
#include <vector>
#include <string>
#include "catch.hpp"
#include "hash_map.hpp"

using namespace std;

TEST_CASE("HELL")
{
    string hell = "hell";
    REQUIRE(hell == "hell");
    cout << hell << '\n';

    fefu::allocator<int> alucard;
    int* e = alucard.allocate();
    *e = 15;
    REQUIRE(*e == 15);
}

TEST_CASE("constructor & destructor")
{
    if (1)
    {
        fefu::hash_map<int, int> hm(8);
    }
}

TEST_CASE("operator[]")
{
    fefu::hash_map<int, string> hm(14);
    int i = 5;
    hm[i] = "bebe";
    REQUIRE(hm[i] == "bebe");
    i--;
    REQUIRE(hm[i] == "");
    hm[0] = ":)";
    REQUIRE(hm[0] == ":)");
    REQUIRE(hm[1] == "");
}