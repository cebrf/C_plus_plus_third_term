using namespace std;
#include "SmartPointer.h"
#include <iostream>



int main() {
    std::cout << "suffering & sorrow" << std::endl;
    int* p = new int;
    *p = 15;

    smart_pointer::SmartPointer<int, std::allocator<int>> suf(p);

    smart_pointer::SmartPointer<int, std::allocator<int>> suff(suf);

    if (1)
    {
        smart_pointer::SmartPointer<int, std::allocator<int>> suffi(suf);
    }

    if (1) 
    {
        smart_pointer::SmartPointer<int, std::allocator<int>> suffi(new int);
        *suffi = 19;
        smart_pointer::SmartPointer<int, std::allocator<int>> sufi = suffi;

        suffi = suf;
        suffi = new int;
    }
    return 0;
}

/*#define ENABLE_TESTS
#include "SmartPointer.h"
#include "Test_SmartPointer.hpp"

int main() {
    EXECUTE_CLASS_TEST(SmartPointer__type_t);
    std::cout << 1 << std::endl;
    return 0;
}*/