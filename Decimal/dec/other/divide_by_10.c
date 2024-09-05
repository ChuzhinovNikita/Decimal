#include "../decimal.h"

void divide_by_10(decimal *in, unsigned *rest) {
  uint64_t p_rest = 0;
  int div = 10;
  *rest = 0;
  for (int i = 2; i >= 0; i--) {
    p_rest = *rest * 4294967296 + in->bits[i];
    in->bits[i] = p_rest / div;
    *rest = p_rest - div * in->bits[i];
  }
}

int divide_by_10_dec(decimal in) {
  uint64_t p_rest = 0;
  int div = 10;
  int rest = 0;
  for (int i = 2; i >= 0; i--) {
    p_rest = rest * 4294967296 + in.bits[i];
    in.bits[i] = p_rest / div;
    rest = p_rest - div * in.bits[i];
  }
  return rest;
}

void big_divide_by_10(big_decimal *in, unsigned *rest) {
  uint64_t p_rest = 0;
  int div = 10;
  *rest = 0;
  for (int i = 7; i >= 0; i--) {
    p_rest = *rest * 4294967296 + in->b_bits[i];
    in->b_bits[i] = p_rest / div;
    *rest = p_rest - div * in->b_bits[i];
  }
}

int big_divide_by_10_rest(big_decimal in) {
  uint64_t p_rest = 0;
  int div = 10;
  int rest = 0;
  for (int i = 7; i >= 0; i--) {
    p_rest = rest * 4294967296 + in.b_bits[i];
    in.b_bits[i] = p_rest / div;
    rest = p_rest - div * in.b_bits[i];
  }
  return rest;
}