#include "../decimal.h"

void set_bit(decimal *varPtr, int bit, int value) {
  unsigned int mask = 1u << (bit % 32);
  if (bit / 32 < 4 && value) {
    varPtr->bits[bit / 32] |= mask;
  } else if (bit / 32 < 4 && !value) {
    varPtr->bits[bit / 32] &= ~mask;
  }
}

void b_set_bit(big_decimal *varPtr, int bit, int value) {
  unsigned int mask = 1u << (bit % 32);
  if (bit / 32 < 8 && value) {
    varPtr->b_bits[bit / 32] |= mask;
  } else if (bit / 32 < 8 && !value) {
    varPtr->b_bits[bit / 32] &= ~mask;
  }
}