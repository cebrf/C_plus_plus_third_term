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


// size and capacity:

TEST_CASE("empty")
{
    fefu::hash_map<int, int> hm;
    REQUIRE(hm.empty());
    hm[6] = 15;
    REQUIRE(!hm.empty());
}

TEST_CASE("size")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'} });
    REQUIRE(hm.size() == 3);
    REQUIRE(hm.max_size() == INT32_MAX);
}


// iterators
TEST_CASE("begin")
{
    fefu::hash_map<int, string> hm;
    hm[6] = "las";
    hm[90] = "fir";
    
    auto fir = hm.begin();
    auto cfir = hm.cbegin();

    bool res = (fir == cfir);
    REQUIRE(res);

    
    REQUIRE(fir->first == 90);
    REQUIRE(fir->second == "fir");
    pair<const int, string> e = { 90, "fir" };
    res = (*fir == e);
    REQUIRE(res);


    const fefu::hash_map<int, string> hm1(hm);
    auto const_fir = hm1.begin();
    REQUIRE(const_fir->first == 90);
    REQUIRE(const_fir->second == "fir");

    fir++;
    REQUIRE(fir->first == 6);
    REQUIRE(fir->second == "las");

    const_fir++;
    REQUIRE(const_fir->first == 6);
    REQUIRE(const_fir->second == "las");
}

TEST_CASE("end")
{
    fefu::hash_map<int, char> hm;
    REQUIRE(hm.begin() == hm.end());
    hm[8] = -4;
    REQUIRE(hm.begin() != hm.end());

    bool res = (hm.end() == hm.cend());
    REQUIRE(res);

    auto e = hm.end();
    REQUIRE_THROWS(e++);

    

    const fefu::hash_map<int, char> hm1(hm);
    auto const_las = hm1.end();
    auto clas = hm1.cend();
    res = (clas == const_las);
    REQUIRE(res);

    auto clas_ = hm.cend();
    res = (clas_ == const_las);
    REQUIRE_FALSE(res);
}


// modifiers.
TEST_CASE("emplace(_Args&&... args)")
{
}

TEST_CASE("try_emplace(const key_type& k, _Args&&... args)")
{
    /*fefu::hash_map<int, char> hm(10);
    hm.try_emplace(123, 'a');*/
}

TEST_CASE("try_emplace(key_type&& k, _Args&&... args)")
{

}

TEST_CASE("insert(const value_type& x)")
{

}


TEST_CASE("insert(value_type&& x)")
{

}

TEST_CASE("insert(_InputIterator first, _InputIterator last)")
{

}

TEST_CASE("insert(std::initializer_list<value_type> l)")
{

}

TEST_CASE("insert_or_assign(const key_type& k, _Obj&& obj)")
{

}

TEST_CASE("insert_or_assign(key_type&& k, _Obj&& obj)")
{

}



TEST_CASE("erase(const_iterator position)")
{

}

TEST_CASE("erase(iterator position)")
{

}

TEST_CASE("erase(const key_type& x)")
{

}

TEST_CASE("erase(const_iterator first, const_iterator last)")
{

}



TEST_CASE("clear()")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'} });
    hm.clear();

    REQUIRE(hm.size() == 0);
    REQUIRE_FALSE(hm.contains(1));
    REQUIRE_FALSE(hm.contains(82));
}

TEST_CASE("swap(hash_map& x)")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {2, 'b'}, {3,'c'} });
    fefu::hash_map<int, char> hm1({ {4, 'd'}, {5, 'e'} });

    hm.swap(hm1);

    REQUIRE(hm.size() == 2);
    REQUIRE(hm1.size() == 3);

    REQUIRE_THROWS(hm.at(1) == 'a');
    REQUIRE(hm1[1] == 'a');
    REQUIRE_THROWS(hm1.at(5) == 'e');
    REQUIRE(hm[5] == 'e');

}

TEST_CASE("merge(hash_map<K, T, _H2, _P2, Alloc>& source)")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {2, 'b'}, {3,'c'} });
    fefu::hash_map<int, char> hm1({ {1, 'd'}, {5, 'e'} });

    hm.merge(hm1);

    REQUIRE(hm.size() == 4);
    REQUIRE(hm1.size() == 1);

    REQUIRE(hm1.at(1) == 'd');

    REQUIRE_THROWS(hm1.at(5) == 'e');

    REQUIRE(hm[5] == 'e');
    REQUIRE(hm[1] == 'a');
}

TEST_CASE("merge(hash_map<K, T, _H2, _P2, Alloc>&& source)")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {2, 'b'}, {3,'c'} });
    fefu::hash_map<int, char> hm1({ {1, 'd'}, {5, 'e'} });

    hm.merge(std::move(hm1));

    REQUIRE(hm.size() == 4);
    REQUIRE(hm1.size() == 1);

    REQUIRE(hm1.at(1) == 'd');

    REQUIRE_THROWS(hm1.at(5) == 'e');

    REQUIRE(hm[5] == 'e');
    REQUIRE(hm[1] == 'a');
}



// observers.

TEST_CASE("hash_function() const")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'} });

    auto smth = hm.hash_function();
}

TEST_CASE("key_eq() const")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'} });
    
    auto smth = hm.key_eq();
}







// lookup.

TEST_CASE("find(const key_type& x)")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'}, {173, 'w'}, {-1035, 'q'}, {90457, 'z'} });

    REQUIRE(hm.find(43) == hm.end());

    auto res = hm.find(90457);
    REQUIRE(res->first == 90457);
    REQUIRE(res->second == 'z');

    hm.insert({ 15, 'v' });
    res = hm.find(15);
    REQUIRE(res->first == 15);
    REQUIRE(res->second == 'v');
}

TEST_CASE("find(const key_type& x) const")
{
    const fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'}, {173, 'w'}, {-1035, 'q'}, {90457, 'z'} });

    REQUIRE(hm.find(43) == hm.cend());

    auto res = hm.find(90457);
    REQUIRE(res->first == 90457);
    REQUIRE(res->second == 'z');
}

TEST_CASE("count(const key_type& x) const")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'}, {173, 'w'}, {-1035, 'q'}, {90457, 'z'} });

    REQUIRE(hm.count(90457));
    REQUIRE_FALSE(hm.count(0));

    hm[52] = -27;
    REQUIRE(hm.count(52));
}

TEST_CASE("contains(const key_type& x) const")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'}, {173, 'w'}, {-1035, 'q'}, {90457, 'z'} });

    REQUIRE(hm.contains(90457));
    REQUIRE_FALSE(hm.contains(0));

    hm[52] = -27;
    REQUIRE(hm.contains(52));
}

TEST_CASE("operator[]")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'}, {173, 'w'}, {-1035, 'q'}, {90457, 'z'} });

    REQUIRE(hm[1] == 'a');
    REQUIRE(hm[-1035] == 'q');
    REQUIRE(hm[0] == static_cast<char>(0));
    REQUIRE(hm.at(0) == static_cast<char>(0));
    
    hm[52] = -27;
    REQUIRE(hm[52] == -27);
}

TEST_CASE("at")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'}, {173, 'w'}, {-1035, 'q'}, {90457, 'z'} });

    REQUIRE_FALSE(hm.at(173) == 'f');
    REQUIRE_THROWS(hm.at(25) == 'e');
    REQUIRE(hm.at(82) == 'f');
}






// bucket interface.

TEST_CASE("bucket_count() const noexcept")
{
    fefu::hash_map<int, char> hm(2);
    REQUIRE(hm.bucket_count() == 2);

    hm[4] = 11;
    hm[11] = -4;
    REQUIRE(hm.bucket_count() == 4);
}

TEST_CASE("bucket(const key_type& _K) const")
{
    fefu::hash_map<int, char> hm(32);
    hm[15] = '9';

    size_t i = (hm.hash_function())(15) % hm.bucket_count();
    REQUIRE(hm.bucket(15) == i);
}



// hash policy.

TEST_CASE("load_factor")
{

    fefu::hash_map<int, char> hm(2);
    REQUIRE(hm.bucket_count() == 2);

    hm[4] = 11;
    hm[11] = -4;

    REQUIRE(std::abs(hm.load_factor() - 2.0 / 4) < 0.0001);
}

TEST_CASE("max_load_factor()")
{
    fefu::hash_map<int, char> hm(2);
    REQUIRE(std::abs(hm.max_load_factor() - 0.75) < 0.0001);
}

TEST_CASE("rehash(size_type n)")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'} });
    hm.rehash(15);
    REQUIRE(hm.bucket_count() == 15);

    REQUIRE(hm.at(1) == 'a');
    REQUIRE_THROWS(hm.at(83) == 'e');
}

TEST_CASE("reserve(size_type n)")
{
    fefu::hash_map<int, char> hm;
    hm.reserve(5);
    REQUIRE(hm.bucket_count() == ceil(5 / hm.max_load_factor()));
}

TEST_CASE("operator==")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'} });
    fefu::hash_map<int, char> hm1({ {1, 'a'}, {6, 'e'}, {82,'f'} });

    bool res = (hm == hm1);
    REQUIRE(res);

    auto smth = hm.insert_or_assign(1, 'r');
    REQUIRE(hm.at(1) == 'r');
    res = (hm == hm1);
    REQUIRE_FALSE(res);

    hm1.erase(6);
    res = (hm == hm1);
    REQUIRE_FALSE(res);


    fefu::hash_map<int, char> hm2, hm3;
    res = (hm2 == hm3);
    REQUIRE(res);
}