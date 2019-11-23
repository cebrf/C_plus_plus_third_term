#define ENABLE_TESTS
#include "SmartPointer.hpp"
#include "Test_SmartPointer.hpp"

#include <iostream>
using namespace std;

int main() {
    //cout << "sorrow";

    /*int* e = new int;
    *e = 17;
    smart_pointer::SmartPointer<int, std::allocator<int>> sm(e);

    cout << *sm << " ";

    smart_pointer::SmartPointer<pair<int, int>, std::allocator<pair<int, int>>> sm1 = new pair<int, int>;
    sm1->first = 11;
    sm1->second == 17;
    cout << (*sm1).first << " ";*/

    EXECUTE_CLASS_TEST(SmartPointer__type_t);
    std::cout << 1 << std::endl;
    return 0;
}