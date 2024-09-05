#include "../decimal.h"

int get_sign(const decimal *value) {
  unsigned int mask = 1u << 31;
  return !!(value->bits[3] & mask);
}