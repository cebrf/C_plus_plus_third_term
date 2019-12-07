#include <vector>

template<typename Val, typename Size>
auto initialize_vector(Val val, Size n) {
    return std::vector<decltype(val)>(n, val);
}

template<typename Val, typename Size, typename ... Args>
auto initialize_vector(Val val, Size n, Args ... args) {
    auto ve = initialize_vector(val, args ...);
    return std::vector<decltype(ve)>(n, ve);
}
