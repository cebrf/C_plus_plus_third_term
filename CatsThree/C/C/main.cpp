
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <iostream>

#include <type_traits>
#include "merge_associative.h"

using namespace std;


template<class C1, class C2>
bool merge(C1&& c1, C2&& c2) { return MergeAssociative(&c1, c2); }

void fail() { cout << -1 << endl; exit(0); }

/*int main() 
{
    if (1)
    {
        bool a = merge(std::set<int>(), std::set<int>());
        bool b = merge(std::set<int>(), 58);
        bool c = merge(23, 66);
        bool d = merge(std::unordered_map<int, const int>(), std::map<int, int>());
        cout << "a = " << a << '\n';
        cout << "b = " << b << '\n';
        cout << "c = " << c << '\n';
    }
}*/



int main()
{
    srand(1);

    {
        bool a =
            merge(std::map<int, int>(), std::map<int, int>()) ||
            merge(std::map<char, char>(), std::map<char, char>()) ||
            merge(std::map<int, double>(), std::map<int, double>()) ||
            merge(std::map<int, int>(), std::unordered_map<int, int>()) ||
            merge(std::map<char, char>(), std::unordered_map<char, char>()) ||
            merge(std::map<int, double>(), std::unordered_map<int, double>()) ||
            merge(std::unordered_map<int, int>(), std::map<int, int>()) ||
            merge(std::unordered_map<char, char>(), std::map<char, char>()) ||
            merge(std::unordered_map<int, double>(), std::map<int, double>()) ||
            merge(std::unordered_map<int, int>(), std::unordered_map<int, int>()) ||
            merge(std::unordered_map<char, char>(), std::unordered_map<char, char>()) ||
            merge(std::unordered_map<int, double>(), std::unordered_map<int, double>());
        if (a)
            fail();
    }

    {
        bool a =
            merge(std::map<int, int>(), std::map<int, double>()) &&
            merge(std::map<char, char>(), std::map<char, double>()) &&
            merge(std::map<int, double>(), std::map<int, int>()) &&
            merge(std::map<int, int>(), std::unordered_map<int, char>()) &&
            merge(std::map<char, char>(), std::unordered_map<char, double>()) &&
            merge(std::map<int, double>(), std::unordered_map<int, char>()) &&
            merge(std::unordered_map<int, int>(), std::map<int, float>()) &&
            merge(std::unordered_map<char, char>(), std::map<char, int>()) &&
            merge(std::unordered_map<int, double>(), std::map<int, int>()) &&
            merge(std::unordered_map<int, int>(), std::unordered_map<int, char>()) &&
            merge(std::unordered_map<char, char>(), std::unordered_map<char, int>()) &&
            merge(std::unordered_map<int, double>(), std::unordered_map<int, float>());
        if (!a)
            fail();
    }

    {
        bool a =
            merge(std::set<int>(), std::set<int>()) ||
            merge(std::set<double>(), std::set<double>()) ||
            merge(std::set<char>(), std::set<char>()) ||
            merge(std::set<int>(), std::unordered_set<int>()) ||
            merge(std::set<double>(), std::unordered_set<double>()) ||
            merge(std::set<char>(), std::unordered_set<char>()) ||
            merge(std::unordered_set<int>(), std::set<int>()) ||
            merge(std::unordered_set<double>(), std::set<double>()) ||
            merge(std::unordered_set<char>(), std::set<char>()) ||
            merge(std::unordered_set<int>(), std::unordered_set<int>()) ||
            merge(std::unordered_set<double>(), std::unordered_set<double>()) ||
            merge(std::unordered_set<char>(), std::unordered_set<char>());
        if (a)
            fail();
    }

    {
        bool a =
            merge(std::set<int>(), std::set<double>()) &&
            merge(std::set<double>(), std::set<int>()) &&
            merge(std::set<char>(), std::set<int>()) &&
            merge(std::set<int>(), std::unordered_set<char>()) &&
            merge(std::set<double>(), std::unordered_set<float>()) &&
            merge(std::set<char>(), std::unordered_set<int>()) &&
            merge(std::unordered_set<int>(), std::set<char>()) &&
            merge(std::unordered_set<double>(), std::set<int>()) &&
            merge(std::unordered_set<char>(), std::set<double>()) &&
            merge(std::unordered_set<int>(), std::unordered_set<float>()) &&
            merge(std::unordered_set<double>(), std::unordered_set<char>()) &&
            merge(std::unordered_set<char>(), std::unordered_set<int>());
        if (!a)
            fail();
    }

    {
        bool a =
            merge(std::multiset<int>(), std::set<int>()) ||
            merge(std::multiset<int>(), std::multiset<int>()) ||
            merge(std::unordered_multiset<int>(), std::set<int>()) ||
            merge(std::unordered_multiset<int>(), std::unordered_multiset<int>()) ||
            merge(std::multiset<int>(), std::unordered_multiset<int>()) ||
            merge(std::unordered_multiset<int>(), std::multiset<int>());
        if (a)
            fail();
    }

    {
        bool a =
            merge(std::multimap<int, int>(), std::map<int, int>()) ||
            merge(std::multimap<int, int>(), std::multimap<int, int>()) ||
            merge(std::unordered_multimap<int, int>(), std::map<int, int>()) ||
            merge(std::unordered_multimap<int, int>(), std::unordered_multimap<int, int>()) ||
            merge(std::multimap<int, int>(), std::unordered_multimap<int, int>()) ||
            merge(std::unordered_multimap<int, int>(), std::multimap<int, int>());
        if (a)
            fail();
    }

    {
        bool a =
            merge(std::multimap<int, double>(), std::map<int, int>()) &&
            merge(std::multimap<int, double>(), std::multimap<int, int>()) &&
            merge(std::unordered_multimap<int, double>(), std::map<int, int>()) &&
            merge(std::unordered_multimap<int, double>(), std::unordered_multimap<int, int>()) &&
            merge(std::multimap<int, double>(), std::unordered_multimap<int, int>()) &&
            merge(std::unordered_multimap<int, double>(), std::multimap<int, int>());
        if (!a)
            fail();
    }

    {
        bool a =
            merge(std::set<int>(), std::multiset<int>()) &&
            merge(std::unordered_set<int>(), std::multiset<int>()) &&
            merge(std::set<int>(), std::unordered_multiset<int>()) &&
            merge(std::unordered_set<int>(), std::unordered_multiset<int>());
        if (!a)
            fail();
    }

    {
        bool a =
            merge(std::map<int, int>(), std::multimap<int, int>()) &&
            merge(std::unordered_map<int, int>(), std::multimap<int, int>()) &&
            merge(std::map<int, int>(), std::unordered_multimap<int, int>()) &&
            merge(std::unordered_map<int, int>(), std::unordered_multimap<int, int>());
        if (!a)
            fail();
    }

    {
        bool a =
            merge(std::set<int>(), 42) &&
            merge(42, std::set<int>()) &&
            merge(std::unordered_set<char>(), std::vector<double>()) &&
            merge(std::vector<double>(), std::unordered_set<char>()) &&
            merge(std::set<double>(), std::unordered_map<int, double>()) &&
            merge(std::set<char>(), std::map<int, char>()) &&
            merge(std::unordered_map<int, double>(), std::set<char>()) &&
            merge(std::unordered_set<double>(), std::set<float>()) &&
            merge(6, 66) &&
            merge(std::vector<int>{4, 2}, std::vector<int>{879});
        if (!a)
            fail();
    }

    {
        bool a =
            merge(std::map<int, const int>(), std::map<int, int>()) ||
            merge(std::map<int, int>(), std::map<int, const int>()) ||
            merge(std::multimap<int, volatile int>(), std::unordered_map<int, int>()) ||
            merge(std::multimap<int, int>(), std::unordered_map<int, volatile int>()) ||
            merge(std::multimap<int, const int>(), std::unordered_map<int, volatile int>()) ||
            merge(std::multimap<int, const int>(), std::unordered_map<int, const int>()) ||
            merge(std::multimap<int, volatile int>(), std::unordered_map<int, volatile int>()) ||
            merge(std::multimap<int, const int>(), std::unordered_map<int, const volatile int>()) ||
            merge(std::multimap<int, const volatile int>(), std::unordered_map<int, const int>()) ||
            merge(std::multimap<int, const volatile int>(), std::unordered_map<int, const volatile int>());
        if (a)
            fail();
    }

    {
        for (int j = 0; j < 15; ++j)
        {
            std::multimap<int, int> m1;
            std::unordered_multimap<int, int> m2;
            for (int i = 0; i < 1000; ++i)
            {
                m1.insert(pair<int, int>{rand() % 1000, rand()});
                m2.insert(pair<int, int>{rand() % 1000, rand()});
            }
            std::multimap<int, int> ans;
            for (const auto& p : m1)
                ans.insert(p);
            for (const auto& p : m2)
                ans.insert(p);
            MergeAssociative(&m1, m2);
            if (m1 != ans)
                fail();
        }
    }

    {
        for (int j = 0; j < 15; ++j)
        {
            std::multiset<int> s1;
            std::unordered_multiset<int> s2;
            for (int i = 0; i < 1000; ++i)
            {
                s1.insert(rand() % 1000);
                s2.insert(rand() % 1000);
            }
            std::multiset<int> ans;
            for (const auto& e : s1)
                ans.insert(e);
            for (const auto& e : s2)
                ans.insert(e);
            MergeAssociative(&s1, s2);
            if (s1 != ans)
                fail();
        }
    }

    cout << 0 << endl;
    return 0;
}