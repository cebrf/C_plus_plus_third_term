#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <type_traits>
#include <string>
#include <utility>

template <typename T>
struct  is_associative_container {
    template<class V> static std::string
        isAC(const std::set<V>) { return "0s"; }
    template<class V> static std::string
        isAC(const std::multiset<V>) { return { "1s" }; }
    template<class V> static std::string
        isAC(const std::unordered_set<V>) { return { "0s" }; }
    template<class V> static std::string
        isAC(const std::unordered_multiset<V>) { return { "1s" }; }

    template<class  K, class V> static std::string
        isAC(const std::map<K, V>) { return { "0m" }; }
    template<class  K, class V> static std::string
        isAC(const std::multimap<K, V>) { return { "1m" }; }
    template<class  K, class V> static std::string
        isAC(const std::unordered_map<K, V>) { return { "0m" }; }
    template<class  K, class V> static std::string
        isAC(const std::unordered_multimap<K, V>) { return { "1m" }; }

    static int64_t isAC(...) { return 0; }
    static T t;
    enum { value = sizeof(isAC(t)) == sizeof(std::string) };
};


template <typename T1, typename T2>
struct is_same_member_type {
    template<class V1, class V2>
    typename std::enable_if<std::is_same<typename std::remove_cv<V1>::type,
    typename std::remove_cv<V2>::type>::value, char>::type
    static isSMT(const V1, const V2) {}

    template<class K1, class K2, class V1, class V2>
    typename std::enable_if<std::is_same<typename std::remove_cv<K1>::type,
        typename std::remove_cv<K2>::type>::value &&
        std::is_same<typename std::remove_cv<V1>::type,
        typename std::remove_cv<V2>::type>::value, char>::type
        static isSMT(const std::pair<K1, V1>, const std::pair<K2, V2>) {}

    static int64_t isSMT(...) { return 0; }
    static T1 t1;
    static T2 t2;
    enum { value = sizeof(isSMT(t1, t2)) == sizeof(char) };
};

template<typename T1, typename T2, typename C1, typename C2>
typename std::enable_if<is_same_member_type<T1, T2>::value, bool>::type
merge_(C1* c1, const C2& c2) {
    for (auto iter = c2.begin(); iter != c2.end(); iter++) {
        c1->insert(*iter);
    }
    return 0;
}

template<typename T1, typename T2, typename C1, typename C2>
typename std::enable_if<!is_same_member_type<T1, T2>::value, bool>::type
merge_(C1* c1, const C2& c2) {
    return 1;
}

template<typename C1, typename C2>
typename std::enable_if<is_associative_container<C1>::value &&
    is_associative_container<C2>::value, bool>::type
MergeAssociative(C1* c1, const C2& c2) {
    is_associative_container<C1> tOne;
    auto typeOne = tOne.isAC(*c1);
    is_associative_container<C2> tTwo;
    auto typeTwo = tTwo.isAC(c2);

    if ((typeOne[0] == '0' && typeTwo[0] == '1')
        || typeOne[1] != typeTwo[1]) {
        return 1;
    }

    return merge_<typename C1::value_type,
        typename C2::value_type, C1, C2>(c1, c2);
}

template<typename C1, typename C2>
typename std::enable_if<!is_associative_container<C1>::value ||
    !is_associative_container<C2>::value, bool>::type
MergeAssociative(C1* c1, const C2& c2) {
    return 1;
}
