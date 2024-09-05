#include "../decimal.h"

void set_sign(decimal *value, int sign) {
  unsigned int mask = 1u << 31;
  if (sign != 0)
    value->bits[3] |= mask;
  else
    value->bits[3] &= ~mask;
}