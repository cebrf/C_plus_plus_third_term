#include <algorithm>

template <typename Val, typename Iter>
Iter find(const Val& val, Iter first, Iter last,
    std::random_access_iterator_tag) {
    Iter res = last;
    last--;
    while (first < last) {
        Iter middle = first + (last - first) / 2;

        if (*middle < val) {
            first = middle + 1;
        } else {
            last = middle;
        }
    }
    if (*first == val) {
        res = first;
    }
    return res;
}

template <typename Val, typename Iter>
Iter find(const Val& val, Iter first, Iter last,
    std::bidirectional_iterator_tag) {
    while (first != last) {
        if (*first == val)
            break;
        first++;
    }
    return first;
}

template <typename Val, typename Iter>
Iter find(const Val& val, Iter first, Iter last,
    std::forward_iterator_tag) {
    while (first != last) {
        if (*first == val)
            break;
        first++;
    }
    return first;
}

template <typename Val, typename Iter>
Iter Find(const Val& val, Iter first, Iter last) {
    return find(val, first, last,
        typename std::iterator_traits<Iter>::iterator_category());
}
