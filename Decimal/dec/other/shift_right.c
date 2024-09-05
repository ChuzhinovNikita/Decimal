#include "../decimal.h"

void shift_right(decimal *num, int shift) {
  for (int i = 0; i < 3; i++) {
    num->bits[i] = (num->bits[i] >> shift) | (num->bits[i + 1] << (32 - shift));
  }
  num->bits[3] = num->bits[3] >> shift;
}

void b_shift_right(big_decimal *num, int shift) {

  for (int i = 0; i < 7; i++) {
    num->b_bits[i] =
        (num->b_bits[i] >> shift) | (num->b_bits[i + 1] << (32 - shift));
  }
  num->b_bits[7] = num->b_bits[7] >> shift;
}
