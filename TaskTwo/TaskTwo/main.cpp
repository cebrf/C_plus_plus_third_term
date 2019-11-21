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
        std::initializer_list<pair<const int, int>> e = { {1, 3}, {92,364}, {-34, 4}, {1, 25} };
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

    if (1)
    {
        fefu::hash_map<int, int> hm1 = { {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5} };
        REQUIRE(hm1.size() == 1);
        REQUIRE(hm1.at(1) == 1);
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
    hm[162] = "las";
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
    REQUIRE(fir->first == 162);
    REQUIRE(fir->second == "las");

    const_fir++;
    REQUIRE(const_fir->first == 162);
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

TEST_CASE("iterator operator++")
{
    fefu::hash_map<int, char> hm = { {1, '2'} };
    auto fir = hm.begin();
    auto las = hm.end();
    REQUIRE(fir != las);

    fir++;
    REQUIRE(fir == las);

    REQUIRE_THROWS(las++);

    auto cfir = hm.cbegin();
    auto clas = hm.cend();
    REQUIRE(cfir != clas);

    cfir++;
    REQUIRE(cfir == clas);

    REQUIRE_THROWS(clas++);
}

TEST_CASE("iterator operator*")
{
    pair<int, char> el = { 1, '2' };
    fefu::hash_map<int, char> hm = { el };
    auto fir = hm.begin();
    REQUIRE((*fir).first == el.first);
    REQUIRE((*fir).second == el.second);

    auto cfir = hm.cbegin();
    REQUIRE((*cfir).first == el.first);
    REQUIRE((*cfir).second == el.second);
}

TEST_CASE("iterator operator->")
{
    pair<int, char> el = { 1, '2' };
    fefu::hash_map<int, char> hm = { el };
    auto fir = hm.begin();
    REQUIRE(fir->first == el.first);
    REQUIRE(fir->second == el.second);

    auto cfir = hm.cbegin();
    REQUIRE(cfir->first == el.first);
    REQUIRE(cfir->second == el.second);
}

// modifiers.
TEST_CASE("emplace(_Args&&... args)")
{
    fefu::hash_map<int, int> hm(10);

    auto res_ = hm.emplace(15, 6);
    REQUIRE(res_.first->first == 15);
    REQUIRE(res_.first->second == 6);
    REQUIRE(res_.second);

    auto res = hm.emplace(15, 8);
    REQUIRE(res.first->first == 15);
    REQUIRE(res.first->second != 8);
    REQUIRE(!res.second);
}

TEST_CASE("try_emplace(const key_type& k, _Args&&... args)")
{
    fefu::hash_map<int, tuple<int, char, string>> hm(10);
    tuple<int, char, string> tu = { 119, 'd', "fear" };
    auto res = hm.try_emplace(123, tu);


    REQUIRE(hm.at(123) == tu);
    REQUIRE(res.first->first == 123);

    res = hm.try_emplace(124, 157, 's', "vf");
    REQUIRE(res.first->first == 124);
    REQUIRE(res.second == true);

    int el_ind = 123;
    res = hm.try_emplace(el_ind, 157, 's', ":(");
    REQUIRE(res.first->first == 123);
    REQUIRE(res.first->second == tu);
    REQUIRE(res.second == false);
}

TEST_CASE("insert(const value_type& x)")
{
    fefu::hash_map<int, char> hm = { {18, 't'}, {38, 'i'}, {28, 'l'}, {-936, 'n'}, {0, 'y'} };

    auto res = hm.insert({ 18, 'a' });
    REQUIRE(res.first->first == 18);
    REQUIRE(res.first->second == 't');
    REQUIRE(res.second == false);


    pair<int, char> el = { -18, 'a' };
    res = hm.insert(el);
    REQUIRE(res.first->first == el.first);
    REQUIRE(res.first->second == el.second);
    REQUIRE(res.second == true);
}

TEST_CASE("insert(_InputIterator first, _InputIterator last)")
{
    fefu::hash_map<int, char> hm = { {18, 't'}, {38, 'i'} };
    vector<pair<int, char>> els = { {18, 'a'}, {38, 'a'}, {28, 'l'}, {-936, 'n'}, {0, 'y'} };

    hm.insert(els.begin(), els.end());

    REQUIRE(hm[18] == 't');
    REQUIRE(hm[38] == 'i');
    REQUIRE(hm[28] == 'l');
    REQUIRE(hm[-936] == 'n');
    REQUIRE(hm[0] == 'y');
}

TEST_CASE("insert(std::initializer_list<value_type> l)")
{
    fefu::hash_map<int, char> hm = { {18, 't'}, {38, 'i'} };
    initializer_list<pair<int, char>> els = { {18, 'a'}, {38, 'a'}, {28, 'l'}, {-936, 'n'}, {0, 'y'} };

    hm.insert(els.begin(), els.end());

    REQUIRE(hm[18] == 't');
    REQUIRE(hm[38] == 'i');
    REQUIRE(hm[28] == 'l');
    REQUIRE(hm[-936] == 'n');
    REQUIRE(hm[0] == 'y');
}

TEST_CASE("insert_or_assign(const key_type& k, _Obj&& obj)")
{
    fefu::hash_map<int, char> hm = { {18, 't'}, {38, 'i'} };

    auto res = hm.insert_or_assign(19, 'e' );
    REQUIRE(res.first->first == 19);
    REQUIRE(res.first->second == 'e');
    REQUIRE(res.second == true);

    int el_ind = 38;
    char el_val = 'j';
    res = hm.insert_or_assign(el_ind, el_val);
    REQUIRE(res.first->first == el_ind);
    REQUIRE(res.first->second == el_val);
    REQUIRE(res.second == true);
}



TEST_CASE("erase(const_iterator position)")
{
    fefu::hash_map<int, char> hm = { {18, 't'}, {38, 'i'} };

    auto cfir = hm.cbegin();
    auto res = hm.erase(cfir);
    REQUIRE(!hm.contains(cfir->first));

    res = hm.erase(hm.cend());
    REQUIRE(res == hm.cend());
}

TEST_CASE("erase(iterator position)")
{
    fefu::hash_map<int, char> hm = { {18, 't'}, {38, 'i'} };

    auto fir = hm.begin();
    auto res = hm.erase(fir);
    REQUIRE(!hm.contains(fir->first));
    REQUIRE(hm.size() == 1);

    fir = hm.begin();
    res = hm.erase(fir);
    REQUIRE(!hm.contains(fir->first));
    REQUIRE(hm.size() == 0);

    res = hm.erase(hm.end());
    REQUIRE(res == hm.end());
}

TEST_CASE("erase(const key_type& x)")
{
    fefu::hash_map<int, char> hm = { {18, 't'}, {38, 'i'}, {26, 'f'} };

    const int ind = 26;
    auto res = hm.erase(ind);
    REQUIRE(res == 1);
    REQUIRE(!hm.contains(26));


    res = hm.erase(ind);
    REQUIRE(res == 0);
}

TEST_CASE("erase(const_iterator first, const_iterator last)")
{
    fefu::hash_map<int, char> hm = { {18, 'a'}, {38, 'a'}, {28, 'l'}, {-936, 'n'}, {0, 'y'} };

    auto fir = hm.cbegin();
    fir++;
    fir++;

    auto res = hm.erase(hm.cbegin(), fir);
    REQUIRE(res == hm.begin());
    REQUIRE(hm.size() == 3);

    res = hm.erase(hm.cbegin(), hm.cend());
    REQUIRE(hm.size() == 0);
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

    REQUIRE(hm.bucket(115) == -1);
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

TEST_CASE("max_load_factor(float z)")
{
    fefu::hash_map<int, char> hm(4);
    hm.insert({ 1, 'a' });
    hm.insert({ 2, 'b' });
    hm.max_load_factor(0.5);
}

TEST_CASE("rehash(size_type n)")
{
    fefu::hash_map<int, char> hm({ {1, 'a'}, {6, 'e'}, {82,'f'} });
    hm.rehash(15);
    REQUIRE(hm.bucket_count() == 16);

    REQUIRE(hm.at(1) == 'a');
    REQUIRE_THROWS(hm.at(83) == 'e');
}

TEST_CASE("reserve(size_type n)")
{
    fefu::hash_map<int, char> hm;
    hm.reserve(7);
    REQUIRE(hm.bucket_count() == 16);
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





//_________________________STRESS_TEST________________________________________________________________________________________________________
#include <stdio.h>
#include <time.h>

/*clock_t start = clock();
  getchar(); 
  clock_t end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("The time: %f seconds\n", seconds);
 */

TEST_CASE("ST_1")
{
    vector<pair<const int, uint32_t>> els;
    for (int i = 0; i < 1000000; i++)
        els.push_back({ i, 100 * i });


    clock_t insert_start_local_hm = clock();
    fefu::hash_map<int, uint32_t> hm(els.begin(), els.end(), 8000000);
    clock_t insert_end_local_hm = clock();
    cout << "construct with insert local hash map: " << (double)(insert_end_local_hm - insert_start_local_hm) / CLOCKS_PER_SEC << '\n';


    clock_t insert_start_base_hm = clock();
    unordered_map<int, uint32_t> check(els.begin(), els.end(), 8000000);
    clock_t insert_end_base_hm = clock();
    cout << "construct with insert base hash map: " << (double)(insert_end_base_hm - insert_start_base_hm) / CLOCKS_PER_SEC << "\n\n";




    clock_t find_start_local_hm = clock();
    for (int i = 0; i < 1000000; i++)
    {
        auto res = hm.find(i);
        REQUIRE(res->first == i);
        REQUIRE(res->second == els[i].second);
    }
    clock_t find_end_local_hm = clock();
    cout << "find with find local hash map: " << (double)(find_end_local_hm - find_start_local_hm) / CLOCKS_PER_SEC << '\n';


    clock_t find_start_base_hm = clock();
    for (int i = 0; i < 1000000; i++)
    {
        auto res = check.find(i);
        REQUIRE(res->first == i);
        REQUIRE(res->second == els[i].second);
    }
    clock_t find_end_base_hm = clock();
    cout << "find with insert base hash map: " << (double)(find_end_base_hm - find_start_base_hm) / CLOCKS_PER_SEC << "\n\n";





    clock_t erase_start_local_hm = clock();
    for (int i = 0; i < 1000000; i++)
    {
        auto res = hm.erase(i);
    }
    clock_t erase_end_local_hm = clock();
    cout << "erase with find local hash map: " << (double)(erase_end_local_hm - erase_start_local_hm) / CLOCKS_PER_SEC << '\n';

    clock_t erase_start_base_hm = clock();
    for (int i = 0; i < 1000000; i++)
    {
        auto res = check.erase(i);
    }
    clock_t erase_end_base_hm = clock();
    cout << "erase base hash map: " << (double)(erase_end_base_hm - erase_start_base_hm) / CLOCKS_PER_SEC << "\n\n";
}