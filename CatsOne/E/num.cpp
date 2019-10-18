#include <algorithm>
#include "num.h"
Num::Num(int value, int modulo) :
  value(value% std::max(modulo, 1)), modulo(modulo) {}

Num& Num::operator=(const Num& other) {
  this->value = other.value;
  this->modulo = other.modulo;
  return *this;
}

Num Num::operator+(const Num& other) {
  int new_modulo = std::max(this->modulo, other.modulo);
  int new_value;
  if (this->value > new_modulo - other.value) {
    new_value = this->value - (new_modulo - other.value);
  } else {
    new_value = (this->value + other.value) % new_modulo;
  }
  return Num(new_value, new_modulo);
}
Num Num::operator-(const Num& other) {
  int new_modulo = std::max(this->modulo, other.modulo);
  int new_value = (this->value - other.value) % new_modulo;
  if (new_value < 0) {
    new_value = new_modulo + new_value;
  }
  return Num(new_value, new_modulo);
}
Num Num::operator*(const Num& other) {
  uint64_t new_value = 1;
  if (this->value < 0) {
    new_value = this->modulo - this->value;
  } else {
    new_value = this->value;
  }
  if (other.value < 0) {
    new_value *= (other.modulo - other.value);
  } else {
    new_value *= other.value;
  }
  return Num(new_value % std::max(this->modulo, other.modulo),
    std::max(this->modulo, other.modulo));
}
Num Num::operator+(int num) {
  num %= this->modulo;
  int new_modulo = this->modulo;
  int new_value;
  if (this->value > new_modulo - num) {
    new_value = this->value - (new_modulo - num);
  } else {
    new_value = (this->value + num) % new_modulo;
  }
  return Num(new_value, new_modulo);
}
Num Num::operator-(int num) {
  num %= this->modulo;
  int new_val = (this->value - num) % this->modulo;
  if (new_val < 0) {
    new_val = this->modulo + new_val;
  }
  return Num(new_val, this->modulo);
}
Num Num::operator*(int num) {
  num %= this->modulo;
  uint64_t new_value = 1;
  if (this->value < 0) {
    new_value = this->modulo - this->value;
  } else {
    new_value = this->value;
  }
  if (num < 0) {
    new_value *= (num - this->value);
  } else {
    new_value *= num;
  }
  return Num(new_value % this->modulo, this->modulo);
}
Num& Num::operator+=(const Num& other) {
  this->modulo = std::max(this->modulo, other.modulo);
  if (this->value > this->modulo - other.value) {
    this->value = this->value - (this->modulo - other.value);
  } else {
    this->value = (this->value + other.value) % this->modulo;
  }
  return *this;
}
Num& Num::operator-=(const Num& other) {
  *this = Num((this->value - other.value) %
    std::max(this->modulo, other.modulo),
    std::max(this->modulo, other.modulo));
  if (this->value < 0) {
    this->value = this->modulo + this->value;
  }
  return *this;
}
Num& Num::operator*=(const Num& other) {
  uint64_t new_value = 1;
  this->modulo = std::max(this->modulo, other.modulo);
  if (this->value < 0) {
    new_value = this->modulo - this->value;
  } else {
    new_value = this->value;
  }
  if (other.value < 0) {
    new_value *= (other.modulo - other.value);
  } else {
    new_value *= other.value;
  }
  this->value = new_value % this->modulo;
  return *this;
}
Num& Num::operator+=(int num) {
  num %= this->modulo;
  if (this->value > this->modulo - num) {
    this->value = this->value - (this->modulo - num);
  } else {
    this->value = (this->value + num) % this->modulo;
  }
  return *this;
}
Num& Num::operator-=(int num) {
  num %= this->modulo;
  *this = Num((this->value - num) % this->modulo, this->modulo);
  if (this->value < 0) {
    this->value = this->modulo + this->value;
  }
  return *this;
}
Num& Num::operator*=(int num) {
  num %= this->modulo;
  uint64_t new_value = 1;
  if (this->value < 0) {
    new_value = this->modulo - this->value;
  } else {
    new_value = this->value;
  }
  if (num < 0) {
    new_value *= (num - this->value);
  } else {
    new_value *= num;
  }
  this->value = new_value % this->modulo;
  return *this;
}
