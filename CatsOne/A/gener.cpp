#include "gener.h"
#include <algorithm>

int current_pos;

PrimeNumberGenerator::PrimeNumberGenerator(int start) {
  current_pos = start;
  if (current_pos == 1) {
    current_pos++;
  }
}
int PrimeNumberGenerator::GetNextPrime() {
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