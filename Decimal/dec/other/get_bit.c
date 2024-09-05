#include "../decimal.h"

int get_bit(const decimal value, int bit) {
  int result = 0;
  if (bit / 32 < 4) {
    unsigned int mask = 1u << (bit % 32);
    result = value.bits[bit / 32] & mask;
  }
  return !!result;
}

int b_get_bit(const big_decimal value, int bit) {
  int result = 0;
  if (bit / 32 < 9) {
    unsigned int mask = 1u << (bit % 32);
    result = value.b_bits[bit / 32] & mask;
  }
  return !!result;
}