#include "num.h"
#include <algorithm>

Num::Num(int value, int modulo) :
  value(value % std::max(modulo, 1)), modulo(modulo) {}
Num::Num(const Num& other) :
  value(other.value), modulo(0) {}
