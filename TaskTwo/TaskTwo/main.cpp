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
    
    fefu::allocator<int> al;

}