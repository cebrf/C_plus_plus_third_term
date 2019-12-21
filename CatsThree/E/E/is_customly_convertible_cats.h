struct NoTriviallyConstructible {
 public:
    NoTriviallyConstructible(int smth, float smth_else) { }
    int val = 1;

 private:
    NoTriviallyConstructible() = delete;
};

struct NoCopyConstructible {
 public:
    NoCopyConstructible() = default;
    int val = 1;

 private:
    NoCopyConstructible(const NoCopyConstructible&) = delete;
    void operator=(const NoCopyConstructible&) = delete;
};

template <class A, class B>
struct Convert;

template <>
struct Convert<NoTriviallyConstructible, int> {
    int operator()(const NoTriviallyConstructible& a) {
        return a.val;
    }
};

template <>
struct Convert<NoCopyConstructible, NoTriviallyConstructible> {
    NoTriviallyConstructible operator()(const NoTriviallyConstructible& a) {
        return NoTriviallyConstructible(a.val, 0.1);
    }
};


template <typename L, typename R>
class is_customly_convertible {
    template <typename A, typename B> static char
        test(decltype(&Convert<A, B>::operator()));
    template <typename A, typename B> static int test(...);

 public:
    enum { value = sizeof(test<L, R>(0)) == sizeof(char) };
};
