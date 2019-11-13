#define CATCH_CONFIG_MAIN

#include <iostream>
#include <vector>
#include <string>
#include "catch.hpp"
#include "hash_map.hpp"
#include <unordered_map>

const float Eps = 0.0001;

using namespace std;

TEST_CASE("")
{
    cout << "suffering & sorrow" << '\n';

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

TEST_CASE("at")
{
    fefu::hash_map<int, int> hmI(14);
    fefu::hash_map<char, int> hmC(14);
    hmC['a'] = 11;
    REQUIRE(hmC.at('a') == 11);
    REQUIRE_THROWS(hmC.at('r') == 1);

    hmI[hmC.at('a')] = -4;
    REQUIRE(hmI[hmC.at('a')] == -4);
}

TEST_CASE("clear")
{
    fefu::hash_map<int, int> hm(14);
    hm[1] = 15;
    REQUIRE(hm[1] == 15);

    hm.clear();
    REQUIRE_THROWS(hm.at(1) == 0);
    REQUIRE(hm[1] == 0);
}

TEST_CASE("bucket_count")
{
    fefu::hash_map<int, int> hm(14);
    REQUIRE(hm.bucket_count() == 14);
    //cout << hm.bucket(115);
}

TEST_CASE("load_factor")
{
    fefu::hash_map<int, int> hm(12);
    REQUIRE(std::abs(hm.load_factor() - 0) < Eps);

    hm[1] = 1;
    hm[2] = 1;
    hm[3] = 1;
    REQUIRE(hm.size() == 3);
    REQUIRE(std::abs(hm.load_factor() - 3/12.0) < Eps);
    REQUIRE(std::abs(hm.max_load_factor() - 3 / 4.0) < Eps);
}

TEST_CASE("copy constructor")
{
    fefu::hash_map<int, int> hm(12);

    hm[1] = 1;
    hm[2] = 2;
    hm[3] = 3;

    fefu::hash_map<int, int> hme(hm);
    REQUIRE(hm[1] == hme[1]);
    REQUIRE(hme[1] == 1);
    REQUIRE(hm[3] == hme[3]);
    REQUIRE(hme[3] == 3);
    REQUIRE(hme[0] == 0);
}

TEST_CASE("begin")
{
    fefu::hash_map<int, int> hm(12);
    hm[15] = 1;
    auto iter = hm.begin();
    cout << iter->first << " " << iter->second;

    hm.rehash(19);
}

TEST_CASE("rehash")
{
    fefu::hash_map<int, int> hm(12);
    hm[15] = 1;
    hm[4] = 12;
    hm[6] = 0;
    
    hm.rehash(19);

    REQUIRE(hm[15] == 1);
    REQUIRE(hm[4] == 12);
    REQUIRE(hm[6] == 0);
    REQUIRE(hm[0] == 0);
    REQUIRE(hm.bucket_count() == 19);
}

TEST_CASE("insert")
{
    fefu::hash_map<int, int> hm(12);

    hm.insert({ 15, 1 });
    REQUIRE(hm[15] == 1);

    vector<pair<int, int>> a = { { 1, 2 }, {3, 4} };
    hm.insert(a.begin(), a.end());
    REQUIRE(hm[1] == 2);
    REQUIRE(hm[3] == 4);
}

TEST_CASE("operator ==")
{
    fefu::hash_map<int, int> hm(12);
    hm.insert({ 15, 1 });
    auto iter = hm.find(14);
    auto end = hm.end();
    //REQUIRE(hm.end() == end);
    //REQUIRE(hm.find(14) == hm.end());

    REQUIRE((*hm.find(15)).second == 1);
}