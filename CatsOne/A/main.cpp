#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
#include <functional>
#include <set>
#include <queue>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include <cassert>

int current_pos;

class PrimeNumberGenerator {
public:
  explicit PrimeNumberGenerator(int start) {
    current_pos = start;
    if (current_pos == 1) {
      current_pos++;
    }
  }
  int GetNextPrime() {
    bool is_prime = 0;
    while (!is_prime) {
      is_prime = 1;
      for (int divider = 2; divider <= sqrt(current_pos)
        && is_prime; divider++) {
          if (current_pos % divider == 0) {
            is_prime = 0;
          }
      }
      if (is_prime) {
        current_pos++;
        return current_pos - 1;
      }
      current_pos++;
    }
  }
};

int main() {
    int start, num;
    while (1) {
		std::cin >> start >> num;
		PrimeNumberGenerator gen(start);
		for (int i = 0; i < num; ++i) {
			std::cout << gen.GetNextPrime() << " ";
		}
	}
}